#pragma once

#include "Animator.hpp"
#include "GUIPanel.hpp"
#include "Geometry/AllConvex.hpp"
#include "TimeHelpers.hpp"
#include "sfLine.hpp"
#include <SFML/Graphics.hpp>

class GUIPanel;

constexpr real CameraMoveSpeed = 0.25;
constexpr real CameraZoomSpeed = 0.12;

constexpr int ColorDepth = 24;
constexpr int AntiAliasing = 8;
constexpr int Stencil = 8;

template <class Derived>
class Client
{
private:
    friend Derived;
    explicit Client(
      const std::string& Name = "Window"); // Standard way to do CRTP

public:
    Client(const Client& rhs) = delete;
    Client& operator=(const Client& rhs) = delete;
    Client(Client&& rhs) = delete;
    Client& operator=(Client&& rhs) = delete;
    ~Client() = default;

    using animation = Animation<Client<Derived>>;

    GUIPanel GUI{};

    sf::View* View() { return &m_View; }

    void Run();

    Point MousePosition() const { return m_vMousePosition; }
    Point MousePositionScreen() const
    {
        return m_Window.mapCoordsToPixel(m_vMousePosition, m_View);
    }

    bool ShouldClose() const { return m_bShouldClose; }
    void Close() { m_bShouldClose = true; }
    void Kill() { Close(); }

    ///********Start Geometry rendering
    void Render(const Point& origin,
                const sf::Color& color = sf::Color::Blue,
                real thickness = 5);

    void RenderSegment(const Point& A,
                       const Point& B,
                       const sf::Color& color = sf::Color::Green,
                       real thickness = 1,
                       bool directed = false);

    void Render(const Segment& A,
                const sf::Color& color = sf::Color::Green,
                real thickness = 1,
                bool directed = false);

    void Render(const Circle& circle,
                const sf::Color& color = sf::Color::Red,
                real thickness = 2);

    void Render(const Circle& circle,
                const sf::Color& fill,
                const sf::Color& outline,
                int thickness = 2);

    void Render(const VP& polygon,
                const sf::Color& color = sf::Color::Magenta,
                real thickness = 1);

    void Render(const Polygon& polygon,
                const sf::Color& color = sf::Color::Magenta,
                real thickness = 1);

    void Render(const Line& line,
                const sf::Color& color = sf::Color::Green,
                real thickness = 1);

    void Render(const Ray& ray,
                const sf::Color& color = sf::Color::Yellow,
                real thickness = 1);

    void Render(const Box& box,
                const sf::Color& color = sf::Color::Cyan,
                real thickness = 1);
    void Render(const Box& box,
                const sf::Color& fillcolor,
                const sf::Color& outlinecolor,
                int thickness = 0);

    void Render(const Convex& conv,
                const sf::Color& color = sf::Color::White,
                real thickness = 1);

    // 	void Render(const string& filename, const FConvex& conv, real angle =
    // 0);

    void Render(const std::string& txt,
                const Point& point,
                const sf::Color& color,
                int size);

    animation& CreateAnimation()
    {
        m_animations.emplace_back(new animation(this));

        return (*m_animations.back());
    }

    void ClearAnimations() { m_animations.clear(); }

    ///******** End Geometry rendering
private:
    void Update(real time) { underlying().Update(time); }

    void RenderWorld() { underlying().RenderWorld(); }
    void RenderGUIPanel() { underlying().RenderGUIPanel(); }

    void ClientRenderGUIPanel();

    //******EVENT HANDLING

    void ClientUpdate(real time);
    void ClientRender();
    void ClientOnEvent(const sf::Event& event);
    void ClientOnKeyPress(sf::Keyboard::Key key);
    void ClientOnKeyRelease(sf::Keyboard::Key key);
    void ClientOnMouseButtonRelease(sf::Mouse::Button btn);
    void ClientOnMouseButtonPress(sf::Mouse::Button btn);
    void ClientOnMouseWheelMoved(int delta);
    void ClientOnMouseMoved();

    void OnEvent(const sf::Event& evt) { underlying().OnEvent(evt); }
    void OnKeyPress(sf::Keyboard::Key key) { underlying().OnKeyPress(key); }
    void OnKeyRelease(sf::Keyboard::Key key) { underlying().OnKeyRelease(key); }
    void OnMouseButtonRelease(sf::Mouse::Button btn)
    {
        underlying().OnMouseButtonRelease(btn);
    }
    void OnMouseButtonPress(sf::Mouse::Button btn)
    {
        underlying().OnMouseButtonPress(btn);
    }
    void OnMouseWheelMoved(int delta) { underlying().OnMouseWheelMoved(delta); }
    void OnMouseMoved() { underlying().OnMouseMoved(); }

    void Resize(real w, real h);

    void FixAspectRatio()
    {
        real r = WindowWidth()/WindowHeight();
        if (m_Camera.Width()/m_Camera.Height() > r)
        {
            m_Camera.SetHeight(m_Camera.Width()/r);
        }
        else
        {
            m_Camera.SetWidth(r*m_Camera.Height());
        }
    }

public:
    void ClearScreen() { m_Window.clear(); }
    void DisplayScreen() { m_Window.display(); }

    void SetGuiView()
    {
        sf::View GUIPanelView(
          sf::FloatRect(0.0, 0.0, WindowWidth(), WindowHeight()));
        m_Window.setView(GUIPanelView);
    }

    void SetWorldView() { m_Window.setView(m_View); }

    void SynchronizeCameraWithView();

    Point WindowSize() const { return m_Window.getSize(); }
    real WindowWidth() const { return m_Window.getSize().x; }
    real WindowHeight() const { return m_Window.getSize().y; }

    Point GlobalToLocalScreen(const Point& P)
    {
        return P.GlobalToLocal(
          Point(0, 0), Point(WindowWidth(), 0), Point(0, WindowHeight()));
    }

    Point LocalToGlobalScreen(const Point& P)
    {
        return P.LocalToGlobal(
          Point(0, 0), Point(WindowWidth(), 0), Point(0, WindowHeight()));
    }

private:
    void ToggleFullScreen();

    Point m_vMousePosition{0, 0};

    sf::RenderWindow m_Window{};
    sf::View m_View{};
    Box m_Camera{};

    sf::Font m_Font{};
    bool m_bShouldClose{false};

    Derived& underlying() { return static_cast<Derived&>(*this); }
    Derived const& underlying() const
    {
        return static_cast<Derived const&>(*this);
    }

    std::string m_title{};

    real fps{60.0};

    real time_dilation{1.0};

    std::vector<std::unique_ptr<animation>> m_animations{};

    void NextFont();

}; // class client definition

// inline std::ostream& operator<<(std::ostream& os, const sf::Keyboard::Key&
// key);

template <class Derived>
Client<Derived>::Client(const std::string& Name)
    : m_vMousePosition(0, 0)
    , m_Window(sf::VideoMode::getDesktopMode(),
               Name,
               sf::Style::Close | sf::Style::Resize |
                 sf::Style::Titlebar, // NOLINT
               sf::ContextSettings(ColorDepth, Stencil, AntiAliasing))
    , m_Camera(Point(0, 0), Point(800, 600))
    , m_title(Name)
{
    m_animations.reserve(100);

    if (!m_Font.loadFromFile("font.ttf"))
        std::cerr << "Fatal error; Could not load font!" << std::endl;

    m_Window.setVerticalSyncEnabled(true);

    m_Window.setKeyRepeatEnabled(true);

    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;

    Resize(width, height);

    SynchronizeCameraWithView();

    SetWorldView();
    m_Camera.Translate({-double(width)/8, -double(height)/4});
    m_Camera.Scale(1.8);

    SynchronizeCameraWithView();

    sf::Color orange(255, 150, 0);

    m_vMousePosition =
      m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window), m_View);
    GUI.AddWatcher(fps, "FPS", orange);

    GUI.AddController(time_dilation,
                      "Time scale",
                      0.1,
                      sf::Keyboard::Comma,
                      sf::Keyboard::Period,
                      orange);
    GUI.AddAction(
      "Toggle Fullscreen",
      sf::Keyboard::F,
      [this]() { ToggleFullScreen(); },
      orange);
    GUI.AddController(GUI.text_size,
                      "Text size",
                      0.5,
                      sf::Keyboard::N,
                      sf::Keyboard::M,
                      orange);
    GUI.AddAction(
      "Change font", sf::Keyboard::F1, [this]() { NextFont(); }, orange);
    GUI.AddAction(
      "Animation step",
      sf::Keyboard::Space,
      [this]() {
          for (auto& a : m_animations)
          {
              a->Play();
          }
      },
      orange);
    GUI.AddSpacer();
}

template <class Derived>
void Client<Derived>::Run()
{
    std::cout << "Starting client" << std::endl;

    sf::ContextSettings settings = m_Window.getSettings();

    std::cout << "depth bits:" << settings.depthBits << std::endl;
    std::cout << "stencil bits:" << settings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings.antialiasingLevel
              << std::endl;
    std::cout << "version:" << settings.majorVersion << "."
              << settings.minorVersion << std::endl;

    std::cout << "Finished loading!" << std::endl;

    Chronometer main_clock;
    Chronometer fps_clock;
    Chronometer render_clock;

    std::int64_t numframes = 0;

    // 	const int fps_numframes_before_reset = 30;

    while (!ShouldClose())
    {
        if (fps_clock.Peek() > 0.5)
        {
            fps = numframes/fps_clock.Reset();
            numframes = 0;
        }

        double frame_time = main_clock.Reset();
        ClientUpdate(frame_time*time_dilation);

        if (render_clock.Peek() > 1.0/60.0)
        {
            ClientRender();
            render_clock.Reset();
        }

        ++numframes;
    }
}

template <class Derived>
void Client<Derived>::ClientUpdate(real time)
{
    m_vMousePosition =
      m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window), m_View);

    // Handle Events
    sf::Event event{};

    while (m_Window.pollEvent(event))
    {
        ClientOnEvent(event);
    }

    real power = CameraMoveSpeed*m_Camera.Perimeter()*time;
    Point X(power, 0);
    Point Y(0, power);

    Point velocity(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity -= X;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity += X;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        velocity -= Y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        velocity += Y;

    m_Camera.Translate(velocity);

    Update(time);
    GUI.Update(time);

    for (auto& A : m_animations)
        A->Update(time);

} // end update

template <class Derived>
void Client<Derived>::ClientRender()
{
    ClearScreen();

    SetWorldView();
    SynchronizeCameraWithView();

    RenderWorld();

    SetGuiView();

    RenderGUIPanel();
    ClientRenderGUIPanel();

    DisplayScreen();
}

template <class Derived>
void Client<Derived>::SynchronizeCameraWithView()
{
    m_View.setCenter(m_Camera.Position());
    m_View.setSize(m_Camera.Width(), m_Camera.Height());
}

/*******************START KEY EVENTS*/
template <class Derived>
void Client<Derived>::ClientOnKeyPress(sf::Keyboard::Key key)
{
    GUI.HandleKeyPress(key);
    OnKeyPress(key);
}

template <class Derived>
void Client<Derived>::ToggleFullScreen()
{
    static bool fullscreen = false;

    real w = sf::VideoMode::getDesktopMode().width;
    real h = sf::VideoMode::getDesktopMode().height;

    Resize(w, h);

    std::cout << "Done resizing" << std::endl;

    m_Window.close();

    if (!fullscreen)
    {
        std::cout << "Creating window..." << std::endl;
        std::cout << "Title: " << m_title << std::endl;
        m_Window.create(sf::VideoMode::getFullscreenModes()[0],
                        m_title,
                        sf::Style::Fullscreen,
                        sf::ContextSettings(ColorDepth, Stencil, AntiAliasing));
        std::cout << "Done!" << std::endl;
        fullscreen = true;
    }
    else
    {
        m_Window.create(sf::VideoMode::getDesktopMode(),
                        m_title,
                        sf::Style::Close | sf::Style::Resize |
                          sf::Style::Titlebar, // NOLINT
                        sf::ContextSettings(ColorDepth, Stencil, AntiAliasing));
        fullscreen = false;
    }
}

template <class Derived>
void Client<Derived>::ClientOnKeyRelease(sf::Keyboard::Key key)
{
    switch (key)
    {
    // Exit
    case sf::Keyboard::Escape: {
        Kill();
        return;
    }
    break;

    default:
        break;
    }

    OnKeyRelease(key);
}

/********************** START MOUSE EVENTS*/
template <class Derived>
void Client<Derived>::ClientOnMouseButtonRelease(sf::Mouse::Button btn)
{
    OnMouseButtonRelease(btn);
}

template <class Derived>
void Client<Derived>::ClientOnMouseButtonPress(sf::Mouse::Button btn)
{
    GUI.HandleMousePress(MousePositionScreen(), btn);

    OnMouseButtonPress(btn);
}

template <class Derived>
void Client<Derived>::ClientOnMouseMoved()
{
    OnMouseMoved();
}

template <class Derived>
void Client<Derived>::ClientOnMouseWheelMoved(int delta)
{
    real scale = 1.0 - CameraZoomSpeed*delta;
    m_Camera.Scale(scale);
    m_Camera.Translate((m_vMousePosition - m_Camera.Position())*(1 - scale));
    OnMouseWheelMoved(delta);
}

template <class Derived>
void Client<Derived>::ClientOnEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        m_bShouldClose = true;
        break;

    case (sf::Event::KeyPressed):
        ClientOnKeyPress(event.key.code);
        break;

    case (sf::Event::KeyReleased):
        ClientOnKeyRelease(event.key.code);
        break;

    case (sf::Event::MouseButtonPressed):
        ClientOnMouseButtonPress(event.mouseButton.button);
        break;

    case (sf::Event::MouseButtonReleased):
        ClientOnMouseButtonRelease(event.mouseButton.button);
        break;

    case (sf::Event::MouseMoved):
        ClientOnMouseMoved();
        break;

    case (sf::Event::MouseWheelMoved):
        ClientOnMouseWheelMoved(event.mouseWheel.delta);
        break;

    case (sf::Event::Resized):
        Resize(event.size.width, event.size.height);
        break;

    default:
        OnEvent(event); // let derived handle all other events
        break;
    }
}

template <class Derived>
void Client<Derived>::Resize(real w, real h)
{
    // Save oldpos because SetWH changes the centre. Maybe fix that?
    Point oldpos = m_Camera.Position();

    real scale = sqrt(m_Camera.Area()/(w*h));
    m_Camera.SetWH(w*scale, h*scale);
    m_Camera.SetPosition(oldpos);
}

///////////// START GEOMETRY RENDERING
template <class Derived>
void Client<Derived>::Render(const Point& origin,
                             const sf::Color& color,
                             real thickness)
{
    real radius = thickness;
    sf::CircleShape circle(radius, 48);

    circle.setPosition(origin.x - radius, origin.y - radius);

    circle.setFillColor(color);

    m_Window.draw(circle);
}

template <class Derived>
void Client<Derived>::RenderSegment(const Point& A,
                                    const Point& B,
                                    const sf::Color& color,
                                    real thickness,
                                    bool directed)
{
    sfLine S(A, B, color, thickness);
    m_Window.draw(S);

    if (directed)
    {
        auto T = sf::ConvexShape(3);
        Point dir = (B - A).Normalized();
        Point D = (A + B)/2 + dir*6;
        T.setPoint(0, D - dir.Rotated(pi/2)*2.5*thickness);
        T.setPoint(1, D - dir.Rotated(-pi/2)*2.5*thickness);
        T.setPoint(2, D + dir*9*thickness);
        T.setFillColor(interpolate(0.5, color, sf::Color::White));
        // 		T.setOutlineColor(sf::Color::Red);
        T.setOutlineThickness(0);
        m_Window.draw(T);
    }
}

template <class Derived>
void Client<Derived>::Render(const Segment& A,
                             const sf::Color& color,
                             real thickness,
                             bool directed)
{
    RenderSegment(A.Origin(), A.End(), color, thickness, directed);
}

template <class Derived>
void Client<Derived>::Render(const Circle& circle,
                             const sf::Color& fill,
                             const sf::Color& outline,
                             int thickness)
{
    real r = circle.Radius();
    Point O = circle.Position();

    sf::CircleShape circleshape(r, 48);
    circleshape.setPosition(O.x - r, O.y - r);

    circleshape.setFillColor(fill);
    circleshape.setOutlineColor(outline);
    circleshape.setOutlineThickness(thickness);

    m_Window.draw(circleshape);
}

template <class Derived>
void Client<Derived>::Render(const Circle& circle,
                             const sf::Color& color,
                             real thickness)
{
    Render(circle, color, color, thickness);
}

template <class Derived>
void Client<Derived>::Render(const VP& polygon,
                             const sf::Color& color,
                             real thickness)
{
    if (polygon.empty())
        return;

    std::vector<sf::Vertex> sfpolygon(polygon.size() + 1);

    for (int i = 0; i < polygon.size(); ++i)
    {
        sfpolygon[i] = sf::Vector2f(polygon[i].x, polygon[i].y);
        Render(polygon[i], color);
    }

    sfpolygon[polygon.size()] = sf::Vector2f(polygon[0].x, polygon[0].y);

    m_Window.draw(&sfpolygon[0], polygon.size() + 1, sf::LinesStrip);
}

template <class Derived>
void Client<Derived>::Render(const Polygon& polygon,
                             const sf::Color& color,
                             real thickness)
{
    if (polygon.NumPoints() == 0)
        return;

    for (int i = 0; i < polygon.NumPoints() + 1; ++i)
    {
        Segment edge(polygon[i], polygon[i + 1]);

        Render(edge, color, thickness);
    }
}

template <class Derived>
void Client<Derived>::Render(const Line& line,
                             const sf::Color& color,
                             real thickness)
{
    Render(Segment(line.Position() + line.Direction()*100000,
                   line.Position() - line.Direction()*100000),
           color,
           thickness);
}

template <class Derived>
void Client<Derived>::Render(const Ray& ray,
                             const sf::Color& color,
                             real thickness)
{
    Render(Segment(ray.Position(), ray.Position() + ray.Direction()*100000),
           color,
           thickness);
}

template <class Derived>
void Client<Derived>::Render(const Box& box,
                             const sf::Color& color,
                             real thickness)
{
    Render(Polygon(box), color, thickness);
}

template <class Derived>
void Client<Derived>::Render(const Box& box,
                             const sf::Color& fillcolor,
                             const sf::Color& outlinecolor,
                             int thickness)
{
    sf::RectangleShape rectangle(Point(box.Width(), box.Height()));
    rectangle.move(box.UpLeft());
    rectangle.setFillColor(fillcolor);
    rectangle.setOutlineColor(outlinecolor);
    rectangle.setOutlineThickness(thickness);
    m_Window.draw(rectangle);
}

template <class Derived>
void Client<Derived>::Render(const std::string& txt,
                             const Point& point,
                             const sf::Color& color,
                             int size)
{
    sf::Text mytext(txt, m_Font, size);
    mytext.setFillColor(color);

    mytext.setPosition(point);
    m_Window.draw(mytext);
}

template <class Derived>
void Client<Derived>::ClientRenderGUIPanel()
{
    GUI.Render(*this);
}

template <class Derived>
void Client<Derived>::NextFont()
{
    static int font = 0;

    ++font;

    if (font == 3)
        font = 0;

    if (font == 0)
        m_Font.loadFromFile("font.ttf");
    else if (font == 1)
        m_Font.loadFromFile("font-mono.ttf");
    else
        m_Font.loadFromFile("font-serif.ttf");
}
