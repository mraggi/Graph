#pragma once

#include "Geometry/AllConvex.hpp"
#include "MessageBox.hpp"
#include "Utility.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <unordered_map>

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

	template <class Client>
	void OnStart(Client* parent)
	{
		if (start.message != "")
		{
			parent->GUI.AddMessage(start);
		}
		m_time = 0;
	}

	template <class Client>
	void OnFinish(Client* parent)
	{
		if (finish.message != "")
		{
			parent->GUI.AddMessage(finish);
		}
		m_time = 0;
	}

	void SetStartMessage(const std::string& msg, const sf::Color& color = sf::Color::White)
	{
		start = Message(msg, color, m_duration);
	}

	void SetFinishMessage(const std::string& msg, const sf::Color& color = sf::Color::White)
	{
		finish = Message(msg, color, m_duration);
	}

protected:
	virtual void ChildUpdate() = 0;

private:
	real m_time{0};
	real m_duration;

	Message start{std::string(""), sf::Color::White, 5.0};
	Message finish{std::string(""), sf::Color::White, 5.0};
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

	virtual ~InterpolatorScene() {}

private:
	T* m_val;
	T  m_start;
	T  m_end;
};

template <class Client>
class Animation
{
public:
	Animation(Client* parent, bool pause_after_every_scene = false)
		: pause_after_scene(pause_after_every_scene), m_parent(parent)
	{
		current_scene = scenes.begin();
		if (pause_after_every_scene)
			Pause();
	}

	void Reset()
	{
		current_scene			  = scenes.begin();
		current_scene_has_started = false;
	}

	void Update(real time)
	{
		if (current_scene == scenes.end())
		{
			if (InALoop())
				Reset();
			return;
		}

		if (Paused())
			return;

		if ((*current_scene)->Finished())
		{
			(*current_scene)->OnFinish(m_parent);
			++current_scene;
			current_scene_has_started = false;

			if (pause_after_scene)
				Pause();
			return;
		}

		if (!current_scene_has_started)
		{
			(*current_scene)->OnStart(m_parent);
			current_scene_has_started = true;
		}

		(*current_scene)->Update(time);
	}

	template <class T>
	Scene* AddScene(T& val, const T& end, real duration)
	{
		scenes.emplace_back(new InterpolatorScene<T>(val, end, duration));
		Reset();
		return scenes.back().get();
	}

	template <class T>
	Scene* AddScene(T& val, const T& start, const T& end, real duration)
	{
		scenes.emplace_back(new InterpolatorScene<T>(val, start, end, duration));
		Reset();
		return scenes.back().get();
	}

	bool Paused() const { return paused; }
	void Pause() { paused = true; }
	void Play() { paused = false; }
	void PauseAfterEveryScene(bool paes) { pause_after_scene = paes; }

	void SetLoop(bool in_loop = true) { loop = in_loop; }
	bool InALoop() const { return loop; }

private:
	Animation(const Animation& A) = delete;
	void operator=(const Animation& A) = delete;
	using scene_container			   = std::vector<std::unique_ptr<Scene>>;
	using scene_iterator			   = scene_container::iterator;
	scene_container scenes;
	scene_iterator  current_scene;
	bool			paused{false};
	bool			pause_after_scene{false};

	bool current_scene_has_started{false};

	bool loop{false};

	Client* m_parent;
};
