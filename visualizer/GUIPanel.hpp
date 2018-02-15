#pragma once

#include "Geometry/AllConvex.hpp"
#include "MessageBox.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <unordered_map>

inline std::ostream& operator<<(std::ostream& os, const sf::Keyboard::Key& key);

enum class ShapeType
{
	NoShape,
	CircleShape,
	BoxShape
};

struct GuiElement
{
	GuiElement(const string& name_, const sf::Color& color_) : name(name_), color(color_) {}
	std::string name;
	sf::Color   color;

	virtual std::string GetString() const { return name; }

	virtual void HandleKeyPress(const sf::Keyboard::Key key){};

	virtual void Activate() {}

	virtual sf::Color GetFillColor() const { return color; }

	virtual ShapeType Shape() const { return ShapeType::NoShape; };

	virtual ~GuiElement() = default;
};

struct Spacer : public GuiElement
{
	Spacer() : GuiElement("", sf::Color::Black) {}
};

template <class T>
struct VarController : public GuiElement
{
public:
	T*				  var;
	sf::Keyboard::Key increaseKey;
	sf::Keyboard::Key decreaseKey;
	T				  stepsize;
	VarController(T&				 var_,
				  sf::Keyboard::Key  increaseKey_,
				  sf::Keyboard::Key  decreaseKey_,
				  T					 stepsize_,
				  const std::string& name,
				  const sf::Color&   color = sf::Color::White)
		: GuiElement(name, color)
		, var(&var_)
		, increaseKey(increaseKey_)
		, decreaseKey(decreaseKey_)
		, stepsize(stepsize_)
	{}

	void HandleKeyPress(sf::Keyboard::Key key)
	{
		if (key == increaseKey)
		{
			*var += stepsize;
		}
		else if (key == decreaseKey)
		{
			*var -= stepsize;
		}
	}

	std::string GetString() const
	{
		std::stringstream out;
		out << name << " [" << decreaseKey << "/" << increaseKey << "]: " << *var;
		return out.str();
	}
};

struct Checkbox : GuiElement
{
	bool*			  var;
	sf::Keyboard::Key shortcut;
	Checkbox(bool&				var_,
			 const std::string& name,
			 sf::Keyboard::Key  key,
			 const sf::Color&   color = sf::Color::White)
		: GuiElement(name, color), var(&var_), shortcut(key)
	{}

	virtual sf::Color GetFillColor() const
	{
		if (*var)
			return sf::Color(16, 200, 64);
		else
			return sf::Color::Black;
	}

	std::string GetString() const
	{
		std::stringstream out;
		out << name << " [" << shortcut << "]";
		return out.str();
	}
	void Activate() { *var = !(*var); }

	void HandleKeyPress(sf::Keyboard::Key key)
	{
		if (key == shortcut)
			Activate();
	}

	ShapeType Shape() const { return ShapeType::CircleShape; };
};

template <class T>
struct VarWatcher : public GuiElement
{
public:
	T* var;
	VarWatcher(T& var_, const std::string& name, const sf::Color& color = sf::Color::Cyan)
		: GuiElement(name, color), var(&var_)
	{}

	std::string GetString() const
	{
		std::stringstream out;
		out << name << ": " << *var;
		return out.str();
	}
};

using StringWatcher = GuiElement;

template <class Func>
class Action : public GuiElement
{
public:
	sf::Keyboard::Key shortcut;

	Action(const std::string& name_, sf::Keyboard::Key shortcut_, Func f_, const sf::Color& color)
		: GuiElement(name_, color), shortcut(shortcut_), f(f_)
	{}

	void Activate() { f(); }

	ShapeType Shape() const { return ShapeType::BoxShape; };

	void HandleKeyPress(sf::Keyboard::Key key)
	{
		if (key == shortcut)
		{
			Activate();
		}
	}

	std::string GetString() const
	{
		std::stringstream out;
		out << name << " [" << shortcut << ']';
		return out.str();
	}

private:
	Func f;
};

class GUIPanel
{
public:
	GUIPanel()
	{
		//      AddElement(CheckboxRadius, "Check box radius", 1,
		// sf::Keyboard::K, sf::Keyboard::L);       AddElement(TextSize,
		// "TextSize", 1, sf::Keyboard::Z, sf::Keyboard::X);
		//      AddElement(TextSeparation, "TextSeparation", 1, sf::Keyboard::C,
		// sf::Keyboard::V);
	}

	template <class T>
	void AddController(T&				  var,
					   const std::string& name,
					   T				  stepsize,
					   sf::Keyboard::Key  decrKey,
					   sf::Keyboard::Key  incrKey,
					   const sf::Color&   color = sf::Color::Magenta);

	void AddCheckbox(bool&				var,
					 const std::string& name,
					 sf::Keyboard::Key  shortcut,
					 const sf::Color&   color = sf::Color::White);

	template <class Func>
	void AddAction(const std::string& name,
				   sf::Keyboard::Key  shortcut,
				   Func				  f,
				   const sf::Color&   color = sf::Color::Yellow);

	void AddSpacer() { gui_elements.emplace_back(new Spacer()); }

	template <class T>
	void AddWatcher(T& var, const std::string& name, const sf::Color& color = sf::Color::Green);

	void AddText(const std::string& name, const sf::Color& color = sf::Color::Cyan);

	void HandleKeyPress(const sf::Keyboard::Key& key);
	void HandleMousePress(const Point& position, const sf::Mouse::Button& btn);

	template <class C>
	void Render(C& client);
	//  void Watch(real var, const std::string& name, sf::Color col = sf::Color(100, 100, 255));

	//  void Watch(const std::string& var, sf::Color col = sf::Color(100, 255, 10));

	real text_size{16};

	real TextSize() const { return text_size; }
	real TextSeparation() const { return text_size * 1.2; }
	real CheckboxRadius() const { return text_size / 2.5; }

	std::string AvailableShortcuts() const;

	void Update(real time) { m_message_box.Update(time); }

	void
	AddMessage(const string& s = "", const sf::Color& c = sf::Color::White, real duration = 5.0)
	{
		m_message_box.AddMessage(s, c, duration);
	}

	void AddMessage(const Message& M) { m_message_box.AddMessage(M); }

private:
	std::vector<std::unique_ptr<GuiElement>> gui_elements;

	// The following is only required on older compilers.
	struct key_hash
	{
		size_t operator()(const sf::Keyboard::Key& key) const { return static_cast<size_t>(key); }
	};

	std::unordered_map<sf::Keyboard::Key, std::vector<GuiElement*>, key_hash> shortcuts;

	MessageBox m_message_box;

	Circle GetCircle(int num);
	Box	GetBox(int num);
};

template <class Func>
void GUIPanel::AddAction(const std::string& name,
						 sf::Keyboard::Key  shortcut,
						 Func				f,
						 const sf::Color&   color)
{
	gui_elements.emplace_back(new Action<Func>(name, shortcut, f, color));
	shortcuts[shortcut].emplace_back(gui_elements.back().get());
}

template <class T>
void GUIPanel::AddController(T&					var,
							 const std::string& name,
							 T					stepsize,
							 sf::Keyboard::Key  decrKey,
							 sf::Keyboard::Key  incrKey,
							 const sf::Color&   color)
{
	gui_elements.emplace_back(new VarController<T>(var, incrKey, decrKey, stepsize, name, color));
	shortcuts[incrKey].emplace_back(gui_elements.back().get());
	shortcuts[decrKey].emplace_back(gui_elements.back().get());
}

template <class T>
void GUIPanel::AddWatcher(T& var, const std::string& name, const sf::Color& color)
{
	gui_elements.emplace_back(new VarWatcher<T>(var, name, color));
}

template <class C>
void GUIPanel::Render(C& client)
{
	int num = 0;

	for (auto& element : gui_elements)
	{
		Point P(2, num * TextSeparation() - 1);

		auto shape = element->Shape();

		if (shape != ShapeType::NoShape)
		{
			P.x += 2 * CheckboxRadius() + 10;
		}

		if (shape == ShapeType::CircleShape)
		{
			sf::Color color = element->color;

			if (GetCircle(num).Intersects(client.MousePositionScreen()))
			{
				color.r /= 2;
				color.b /= 2;
				color.g /= 2;

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					color.b = 0;
					color.g = 0;
					color.r = 128;
				}
			}

			client.Render(GetCircle(num), element->GetFillColor(), color, 2);
		}
		else if (shape == ShapeType::BoxShape)
		{
			sf::Color color = element->color;

			if (GetBox(num).Intersects(client.MousePositionScreen()))
			{
				color.r /= 2;
				color.b /= 2;
				color.g /= 2;

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					color.b = 0;
					color.g = 0;
					color.r = 128;
				}
			}

			client.Render(GetBox(num), color, color);
		}

		client.Render(element->GetString(), P, element->color, TextSize());
		++num;
	}
	m_message_box.Render(client);
}

inline std::ostream& operator<<(std::ostream& os, const sf::Keyboard::Key& key)
{
	// Handle special cases
	switch (key)
	{
	case sf::Keyboard::Return:
		os << "Enter";
		break;

	case sf::Keyboard::Space:
		os << "Space";
		break;

	case sf::Keyboard::Comma:
		os << ",";
		break;

	case sf::Keyboard::Period:
		os << ".";
		break;

	case sf::Keyboard::LBracket:
		os << '{';
		break;

	case sf::Keyboard::RBracket:
		os << '}';
		break;

	case sf::Keyboard::Tab:
		os << "Tab";
		break;

	case sf::Keyboard::Add:
		os << '+';
		break;

	case sf::Keyboard::Subtract:
		os << '-';
		break;

	case sf::Keyboard::Dash:
		os << '-';
		break;

	default:
		break;
	}

	// Handle all letters
	if (sf::Keyboard::A <= key && key <= sf::Keyboard::Z)
	{
		os << static_cast<char>('A' + static_cast<char>(key));
		return os;
	}

	// Handle F-keys
	if (sf::Keyboard::F1 <= key && key <= sf::Keyboard::F15)
	{
		os << 'F' << 1 + key - sf::Keyboard::F1;
		return os;
	}

	if (sf::Keyboard::Num0 <= key && key <= sf::Keyboard::Num9)
	{
		os << key - sf::Keyboard::Num0;
		return os;
	}

	if (sf::Keyboard::Numpad0 <= key && key <= sf::Keyboard::Numpad0)
	{
		os << "Numpad" << key - sf::Keyboard::Numpad0;
		return os;
	}

	return os;
}
