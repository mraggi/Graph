#include "GUIPanel.hpp"
#include "Client.hpp"

void GUIPanel::HandleKeyPress(const sf::Keyboard::Key& key)
{
	auto it = shortcuts.find(key);
	if (it == shortcuts.end())
		return;
	for (auto& t : it->second)
	{
		t->HandleKeyPress(key);
	}
}

Circle GUIPanel::GetCircle(int num)
{
	double r = CheckboxRadius;

	double height = (0.5 + num) * TextSeparation;

	Point O(2 + r, height);

	return Circle(O, r);
}

Box GUIPanel::GetBox(int num)
{
	double r	  = CheckboxRadius;
	double height = (0.5 + num) * TextSeparation;

	Point O(2 + r, height);

	return Box(O, r, r);
}

void GUIPanel::AddCheckbox(bool&			 var,
						   const string&	 name,
						   sf::Keyboard::Key key,
						   const sf::Color&  color)
{
	gui_elements.emplace_back(new Checkbox(var, name, key, color));
	shortcuts[key].emplace_back(gui_elements.back().get());
}

void GUIPanel::HandleMousePress(const Point& position, const sf::Mouse::Button& btn)
{
	int num = 0;
	for (auto& e : gui_elements)
	{
		if (e->Shape() == ShapeType::CircleShape)
		{
			if (GetCircle(num).Intersects(position))
			{
				e->Activate();
			}
		}
		else if (e->Shape() == ShapeType::BoxShape)
		{
			if (GetBox(num).Intersects(position))
			{
				e->Activate();
			}
		}
		++num;
	}
}

void GUIPanel::AddText(const std::string& name, const sf::Color& color)
{
	gui_elements.emplace_back(new StringWatcher(name, color));
}

std::string GUIPanel::AvailableShortcuts() const
{
	int A = static_cast<int>(sf::Keyboard::A);
	int Z = static_cast<int>(sf::Keyboard::Z);

	std::stringstream s;
	for (int key = A; key <= Z; ++key)
	{
		auto Key = static_cast<sf::Keyboard::Key>(key);
		if (shortcuts.find(Key) == shortcuts.end())
			s << Key;
	}

	return s.str();
}

//
// void GUIPanel::Watch(real var, const string& name, sf::Color color)
// {
// 	VarWatcher hola(var, name, color);
// 	if (m_iLastWatchedVarThisRound >= m_WatchedVars.size())
// 	{
// 		m_WatchedVars.emplace_back(hola);
// 	}
// 	else
// 	{
// 		m_WatchedVars[m_iLastWatchedVarThisRound] = hola;
// 	}
// 	++m_iLastWatchedVarThisRound;
// }
//
// void GUIPanel::Watch(const string& name, sf::Color color)
// {
// 	StringWatcher hola(name, color);
// 	if (m_iLastWatchedStringThisRound >= m_WatchedStrings.size())
// 	{
// 		m_WatchedStrings.emplace_back(hola);
// 	}
// 	else
// 	{
// 		m_WatchedStrings[m_iLastWatchedStringThisRound] = hola;
// 	}
// 	++m_iLastWatchedStringThisRound;
// }
