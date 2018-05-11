#pragma once

#include "Utility.hpp"
#include <SFML/Graphics.hpp>
#include <queue>
#include <sstream>
#include <utility>

struct Message
{
    Message(std::string msg, const sf::Color& color, real time = 5.0)
        : message(std::move(msg)), start_color(color), duration(time)
    {}

    void Update(real time) { time_since_start += time; }

    bool IsDone() const { return time_since_start > 2*duration; }

    sf::Color GetColor()
    {
        real t = 0.0;
        if (time_since_start > duration)
        {
            t = (time_since_start - duration)/duration;
        }

        if (t > 1.0)
            t = 1.0;

        auto transparent = start_color;
        transparent.a = 0;

        return interpolate(t, start_color, transparent);
    }

    int NumLines() const
    {
        return 1 + std::count(message.begin(), message.end(), '\n');
    }

    std::string message;

private:
    sf::Color start_color;
    real time_since_start{0.0};
    real duration{2.0};
};

class MessageBox
{
public:
    const int max_num_messages = 10;

    void AddMessage(const std::string& message,
                    const sf::Color& color,
                    real duration = 5.0)
    {
        messages.emplace_front(message, color, duration);
    }

    void AddMessage(const Message& M) { messages.emplace_front(M); }

    void Update(real time)
    {
        for (auto& m : messages)
            m.Update(time);
    }

    template <class C>
    void Render(C& client);

private:
    std::deque<Message> messages{};
};

template <class C>
void MessageBox::Render(C& client)
{
    auto ts = client.GUI.TextSize();
    auto sep = client.GUI.TextSeparation();

    auto w = client.WindowWidth();
    auto h = client.WindowHeight();

    Point P(w/3.0, h - sep);

    for (auto& m : messages)
    {
        P.y -= sep*m.NumLines();
        client.Render(m.message, P, m.GetColor(), ts);
    }

    while (!messages.empty() && messages.back().IsDone())
        messages.pop_back();
}
