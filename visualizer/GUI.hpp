#pragma once

#define PA (*GUI::Instance())

#include "Button.hpp"
#include "Geometry/AllConvex.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

template <class T>
struct DebuggingVariable
{
public:
    T*                var;
    sf::Keyboard::Key increaseKey;
    sf::Keyboard::Key decreaseKey;
    T                 stepsize;
    std::string       name;
    sf::Color         color;
    DebuggingVariable(T&                 newvar,
                      sf::Keyboard::Key  newincreaseKey,
                      sf::Keyboard::Key  newdecreaseKey,
                      T                  newstepsize,
                      const std::string& newname,
                      const sf::Color&   col = sf::Color::White)
        : var(&newvar)
        , increaseKey(newincreaseKey)
        , decreaseKey(newdecreaseKey)
        , stepsize(newstepsize)
        , name(newname)
        , color(col)
    {}
};

struct WatchingVariable
{
public:
    real        var;
    std::string name;
    sf::Color   color;
    WatchingVariable(real               newvar,
                     const std::string& newname,
                     const sf::Color&   newcolor = sf::Color::Yellow)
        : var(newvar), name(newname), color(newcolor)
    {}
};

struct WatchingString
{
public:
    std::string name;
    sf::Color   color;
    WatchingString(const std::string& newname, const sf::Color& newcolor = sf::Color::Red)
        : name(newname), color(newcolor)
    {}
};

class GUI
{
public:
    void AddSlider(real&              var,
                   const std::string& name,
                   real               stepsize,
                   sf::Keyboard::Key  decrKey,
                   sf::Keyboard::Key  incrKey,
                   const sf::Color&   color = sf::Color::Magenta);

    void AddSlider(int&               var,
                   const std::string& name,
                   int                stepsize,
                   sf::Keyboard::Key  decrKey,
                   sf::Keyboard::Key  incrKey,
                   const sf::Color&   color = sf::Color::Cyan);

    void AddCheckbox(bool&              var,
                     const std::string& name,
                     sf::Keyboard::Key  key,
                     const sf::Color&   color = sf::Color::White);

    template <class Func>
    void AddButton(const std::string& name, sf::Keyboard::Key shortcut, Func f);

    void HandleKeyPress(const sf::Keyboard::Key& key);

    void Watch(real var, const std::string& name, sf::Color col = sf::Color(100, 100, 255));

    void Watch(const std::string& var, sf::Color col = sf::Color(100, 255, 10));

public:
    static GUI* Instance()
    {
        static GUI instance;
        return &instance;
    }

    static real TextSeparation;
    static real TextSize;
    static real CheckboxRadius;

private:
    GUI()
    {
        // 		AddElement(CheckboxRadius, "Check box radius", 1,
        // sf::Keyboard::K, sf::Keyboard::L); 		AddElement(TextSize,
        // "TextSize", 1, sf::Keyboard::Z, sf::Keyboard::X);
        // 		AddElement(TextSeparation, "TextSeparation", 1, sf::Keyboard::C,
        // sf::Keyboard::V);
    }

public:
    std::vector<DebuggingVariable<real>>     m_VFDr{}; // variables for debugging
    std::vector<DebuggingVariable<int>>      m_VFDi{}; // variables for debugging
    std::vector<DebuggingVariable<bool>>     m_VFDb{}; // variables for debugging
    std::vector<std::unique_ptr<ButtonBase>> m_buttons;

    std::vector<WatchingVariable> m_WatchedVars{};
    std::vector<WatchingString>   m_WatchedStrings{};
    size_t                        m_iLastWatchedShapeThisRound{0};
    size_t                        m_iLastWatchedVarThisRound{0};
    size_t                        m_iLastWatchedStringThisRound{0};
};

template <class Func>
void GUI::AddButton(const std::string& name, sf::Keyboard::Key shortcut, Func f)
{
    m_buttons.emplace_back(new Button<Func>(name, f, shortcut));
}
