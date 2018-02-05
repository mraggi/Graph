#pragma once

#include "Geometry/AllConvex.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <unordered_map>

template <class T>
T interpolate(real t, const T& from, const T& to)
{
	return t * to + (1 - t) * from;
}

inline sf::Color interpolate(real t, const sf::Color& from, const sf::Color& to)
{
	real ra = from.r;
	real ga = from.g;
	real ba = from.b;
	real rb = to.r;
	real gb = to.g;
	real bb = to.b;

	real r = interpolate(t, ra, rb);
	real g = interpolate(t, ga, gb);
	real b = interpolate(t, ba, bb);

	return sf::Color(r, g, b);
}

class Scene
{
public:
	virtual ~Scene() {}

	Scene(real duration) : m_duration(duration) {}

	void Update(real t)
	{
		m_time += t;
		ChildUpdate();
	}

	real ElapsedTime() const { return m_time; }

	real ElapsedPercentage() const { return m_time / m_duration; }

	real RemainingTime() const { return m_duration - m_time; }

	bool Finished() const { return m_time > m_duration; }

protected:
	virtual void ChildUpdate() = 0;

private:
	real m_time{0};
	real m_duration;
};

template <class T>
class InterpolatorScene : public Scene
{
public:
	InterpolatorScene(T& val, const T& end, real duration)
		: Scene(duration), m_val(&val), m_start(val), m_end(end)
	{}

	InterpolatorScene(T& val, const T& start, const T& end, real duration)
		: Scene(duration), m_val(&val), m_start(start), m_end(end)
	{}

	virtual void ChildUpdate() override
	{
		real t = ElapsedPercentage();
		*m_val = interpolate(t, m_start, m_end);
	}

private:
	T* m_val;
	T  m_start;
	T  m_end;
};

class Animation
{
public:
	Animation() {}

	void Reset() { current_scene = scenes.begin(); }

	void Update(real time)
	{
		if (current_scene == scenes.end())
			return;

		(*current_scene)->Update(time);

		if ((*current_scene)->Finished())
		{
			++current_scene;
			// 			if (current_scene != scenes.end())
			// 				current_scene->Start();
		}
	}

	template <class T>
	void AddScene(T& val, const T& end, real duration)
	{
		scenes.emplace_back(new InterpolatorScene<T>(val, end, duration));
		Reset();
	}

	template <class T>
	void AddScene(T& val, const T& start, const T& end, real duration)
	{
		scenes.emplace_back(new InterpolatorScene<T>(val, start, end, duration));
		Reset();
	}

private:
	Animation(const Animation& A) = delete;
	void operator=(const Animation& A) = delete;
	using scene_container			   = std::vector<std::unique_ptr<Scene>>;
	using scene_iterator			   = scene_container::iterator;
	scene_container scenes;
	scene_iterator  current_scene;
};
