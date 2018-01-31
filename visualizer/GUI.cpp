#include "GUI.hpp"
#include "Client.hpp"

real GUI::TextSeparation = 30;
real GUI::TextSize = 25;
real GUI::CheckboxRadius = 10;

void GUI::HandleKeyPress(const sf::Keyboard::Key& key)
{
    for (auto DV : m_VFDr)
    {
        if (key == DV.increaseKey)
            (*DV.var) += DV.stepsize;
        if (key == DV.decreaseKey)
            (*DV.var) -= DV.stepsize;
    }

    for (auto DV : m_VFDi)
    {
        if (key == DV.increaseKey)
            (*DV.var) += DV.stepsize;
        if (key == DV.decreaseKey)
            (*DV.var) -= DV.stepsize;
    }

    for (auto DV : m_VFDb)
    {
        if (key == DV.increaseKey)
            (*DV.var) = !(*DV.var);
    }
    
    for (auto& btn : m_buttons)
	{
		if (key == btn->Shortcut())
		{
			btn->Activate();
		}
	}
    
}



void GUI::AddSlider(	real& var,
														const string& name,
														real stepsize,
														sf::Keyboard::Key decrKey,
														sf::Keyboard::Key incrKey,
														const sf::Color& color
													)
{
	m_VFDr.emplace_back(var, incrKey, decrKey, stepsize, name, color);
}

void GUI::AddSlider(	int& var,
														const string& name,
														int stepsize,
														sf::Keyboard::Key decrKey,
														sf::Keyboard::Key incrKey,
														const sf::Color& color
													)
{
	m_VFDi.emplace_back(var, incrKey, decrKey, stepsize, name, color);
}

void GUI::AddCheckbox(	bool& var,
														const string& name,
														sf::Keyboard::Key key,
														const sf::Color& color
													)
{
	m_VFDb.emplace_back(var, key, key, 1, name, color);
}

void GUI::Watch(real var, const string& name, sf::Color color)
{
	WatchingVariable hola(var,name,color);
	if (m_iLastWatchedVarThisRound >= m_WatchedVars.size())
	{
		m_WatchedVars.emplace_back(hola);
	} else
	{
		m_WatchedVars[m_iLastWatchedVarThisRound] = hola;
	}
	++m_iLastWatchedVarThisRound;
}

void GUI::Watch(const string& name, sf::Color color)
{
	WatchingString hola(name,color);
	if (m_iLastWatchedStringThisRound >= m_WatchedStrings.size())
	{
		m_WatchedStrings.emplace_back(hola);
	} else
	{
		m_WatchedStrings[m_iLastWatchedStringThisRound] = hola;
	}
	++m_iLastWatchedStringThisRound;
}
