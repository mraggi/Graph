#pragma once
#include <SFML/Window.hpp>
#include <string>

class ButtonBase
{
public:
    ButtonBase(const std::string& name, sf::Keyboard::Key shortcut)
        : m_name(name), m_shortcut(shortcut)
    {}
    virtual ~ButtonBase()   = default;
    virtual void Activate() = 0;

    const std::string& Name() const { return m_name; }
    void               SetName(const std::string& newname) { m_name = newname; }
    sf::Keyboard::Key  Shortcut() const { return m_shortcut; }

private:
    std::string       m_name;
    sf::Keyboard::Key m_shortcut;
};

template <class Func>
class Button : public ButtonBase
{
public:
    Button(const std::string& name_, Func f_, sf::Keyboard::Key shortcut)
        : ButtonBase(name_, shortcut), f(f_)
    {}
    void Activate() { f(); }

private:
    Func f;
};
