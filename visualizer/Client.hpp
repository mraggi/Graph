#pragma once

#include "Animator.hpp"
#include "GUIPanel.hpp"
#include "Geometry/AllConvex.hpp"
#include "RichText.hpp"
#include "TimeHelpers.hpp"
#include <SFML/Graphics.hpp>

class GUIPanel;

const real CameraMoveSpeed = 0.25;
const real CameraZoomSpeed = 0.12;

const int ColorDepth   = 24;
const int AntiAliasing = 8;
const int Stencil	  = 8;

template <class Derived>
class Client
{
private:
	friend Derived;
	Client(const string& Name = "Window"); // Standard way to do CRTP

public:
	using animation = Animation<Client<Derived>>;

	GUIPanel GUI;

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

	/// ************** Start Geometry rendering
	void Render(const Point& origin, const sf::Color& color = sf::Color::Blue, int thickness = 5);

	void Render(const Segment&   A,
				const sf::Color& color	 = sf::Color::Green,
				int				 thickness = 1,
				bool			 directed  = false);

	void Render(const Circle& circle, const sf::Color& color = sf::Color::Red, int thickness = 2);

	void Render(const Circle&	circle,
				const sf::Color& fillcolor,
				const sf::Color& outlinecolor,
				int				 thickness = 2);

	void Render(const VP& polygon, const sf::Color& color = sf::Color::Magenta, int thickness = 1);

	void
	Render(const Polygon& polygon, const sf::Color& color = sf::Color::Magenta, int thickness = 1);

	void Render(const Line& line, const sf::Color& color = sf::Color::Green, int thickness = 1);

	void Render(const Ray& ray, const sf::Color& color = sf::Color::Yellow, int thickness = 1);

	void Render(const Box& box, const sf::Color& color = sf::Color::Cyan, int thickness = 1);
	void Render(const Box&		 box,
				const sf::Color& fillcolor,
				const sf::Color& outlinecolor,
				int				 thickness = 0);

	void Render(const Convex& conv, const sf::Color& color = sf::Color::White, int thickness = 1);

	void Render(const string& filename, const FConvex& conv, real angle = 0);

	void Render(const string& txt, const Point& point, const sf::Color& color, int size);

	animation& CreateAnimation(bool pause_after_every_scene = false)
	{
		m_animations.emplace_back(new animation(this, pause_after_every_scene));
		return (*m_animations.back());
	}

	/// *************** End Geometry rendering
private:
	void Update(real time) { underlying().Update(time); }

	void RenderWorld() { underlying().RenderWorld(); }
	void RenderGUIPanel() { underlying().RenderGUIPanel(); }

	void ClientRenderGUIPanel();

	// ********** EVENT HANDLING

	void ClientUpdate(real time);
	void ClientRender();
	void ClientOnEvent(const sf::Event& evt);
	void ClientOnKeyPress(sf::Keyboard::Key key);
	void ClientOnKeyRelease(sf::Keyboard::Key key);
	void ClientOnMouseButtonRelease(sf::Mouse::Button btn);
	void ClientOnMouseButtonPress(sf::Mouse::Button btn);
	void ClientOnMouseWheelMoved(int delta);
	void ClientOnMouseMoved();

	void OnEvent(const sf::Event& evt) { underlying().OnEvent(evt); }
	void OnKeyPress(sf::Keyboard::Key key) { underlying().OnKeyPress(key); }
	void OnKeyRelease(sf::Keyboard::Key key) { underlying().OnKeyRelease(key); }
	void OnMouseButtonRelease(sf::Mouse::Button btn) { underlying().OnMouseButtonRelease(btn); }
	void OnMouseButtonPress(sf::Mouse::Button btn) { underlying().OnMouseButtonPress(btn); }
	void OnMouseWheelMoved(int delta) { underlying().OnMouseWheelMoved(delta); }
	void OnMouseMoved() { underlying().OnMouseMoved(); }

	void Resize(real w, real h);

	void FixAspectRatio()
	{
		real r = WindowWidth() / WindowHeight();
		if (m_Camera.Width() / m_Camera.Height() > r)
		{
			m_Camera.SetHeight(m_Camera.Width() / r);
		}
		else
		{
			m_Camera.SetWidth(r * m_Camera.Height());
		}
	}

public:
	void ClearScreen() { m_Window.clear(); }
	void DisplayScreen() { m_Window.display(); }

	void SetGuiView()
	{
		sf::View GUIPanelView(sf::FloatRect(0.0, 0.0, WindowWidth(), WindowHeight()));
		m_Window.setView(GUIPanelView);
	}

	void SetWorldView() { m_Window.setView(m_View); }

	void SynchronizeCameraWithView();

	Point WindowSize() const { return m_Window.getSize(); }
	real  WindowWidth() const { return m_Window.getSize().x; }
	real  WindowHeight() const { return m_Window.getSize().y; }

	Point GlobalToLocalScreen(const Point& P)
	{
		return P.GlobalToLocal(Point(0, 0), Point(WindowWidth(), 0), Point(0, WindowHeight()));
	}

	Point LocalToGlobalScreen(const Point& P)
	{
		return P.LocalToGlobal(Point(0, 0), Point(WindowWidth(), 0), Point(0, WindowHeight()));
	}

private:
	Client(const Client& rhs) = delete;
	Client& operator=(const Client& rhs) = delete;

	void ToggleFullScreen();

	Point m_vMousePosition;

	sf::RenderWindow m_Window;
	sf::View		 m_View;
	Box				 m_Camera;

	sf::Font m_Font;
	bool	 m_bShouldClose;

	Derived&	   underlying() { return static_cast<Derived&>(*this); }
	Derived const& underlying() const { return static_cast<Derived const&>(*this); }

	string m_title;

	real fps{60.0};

	real time_dilation{1.0};

	std::vector<std::unique_ptr<animation>> m_animations;

}; // class client definition

inline std::ostream& operator<<(std::ostream& os, const sf::Keyboard::Key& rhs);

template <class Derived>
Client<Derived>::Client(const string& Name)
	: m_vMousePosition(0, 0)
	, m_Window(sf::VideoMode::getDesktopMode(),
			   Name,
			   sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar,
			   sf::ContextSettings(ColorDepth, Stencil, AntiAliasing))
	, m_View()
	, m_Camera(Point(0, 0), Point(800, 600))
	, m_Font()
	, m_bShouldClose(false)
	, m_title(Name)
{
	if (!m_Font.loadFromFile("font.ttf"))
		cout << "Fatal error; Could not load font!" << endl;

	m_Window.setVerticalSyncEnabled(true);

	m_Window.setKeyRepeatEnabled(true);

	auto width  = sf::VideoMode::getDesktopMode().width;
	auto height = sf::VideoMode::getDesktopMode().height;

	Resize(width, height);

	SynchronizeCameraWithView();

	SetWorldView();
	m_Camera.Translate({-double(width) / 8, -double(height) / 4});
	m_Camera.Scale(1.8);

	SynchronizeCameraWithView();

	sf::Color orange(255, 150, 0);

	m_vMousePosition = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window), m_View);
	GUI.AddWatcher(fps, "FPS", orange);

	GUI.AddController(
	  time_dilation, "Time scale", 0.1, sf::Keyboard::Comma, sf::Keyboard::Period, orange);
	GUI.AddAction("Toggle Fullscreen", sf::Keyboard::F, [this]() { ToggleFullScreen(); }, orange);
	GUI.AddAction("Change font",
				  sf::Keyboard::F1,
				  [this]() {
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
				  },
				  orange);
	GUI.AddAction("Animation step",
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
	cout << "Starting client" << endl;

	sf::ContextSettings settings = m_Window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	cout << "Finished loading!" << endl;

	Chronometer main_clock;
	Chronometer fps_clock;
	Chronometer render_clock;

	long numframes = 0;

	const int fps_numframes_before_reset = 30;

	while (!ShouldClose())
	{
		if (fps_clock.Peek() > 0.5)
		{
			fps		  = numframes / fps_clock.Reset();
			numframes = 0;
		}

		double frame_time = main_clock.Reset();
		ClientUpdate(frame_time * time_dilation);

		if (render_clock.Peek() > 1.0 / 60.0)
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
	m_vMousePosition = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window), m_View);

	// Handle Events
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		ClientOnEvent(event);
	}

	real  power = CameraMoveSpeed * m_Camera.Perimeter() * time;
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

/************************************* START KEY EVENTS */
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

	std::cout << "Done resizing" << endl;

	m_Window.close();

	if (!fullscreen)
	{
		cout << "Creating window..." << endl;
		cout << "Title: " << m_title << endl;
		m_Window.create(sf::VideoMode::getFullscreenModes()[0],
						m_title,
						sf::Style::Fullscreen,
						sf::ContextSettings(ColorDepth, Stencil, AntiAliasing));
		cout << "Done!" << endl;
		fullscreen = true;
	}
	else
	{
		m_Window.create(sf::VideoMode::getDesktopMode(),
						m_title,
						sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar,
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
	case sf::Keyboard::Escape:
	{
		Kill();
		return;
	}
	break;

	default:
		break;
	}

	OnKeyRelease(key);
}

/******************************************** START MOUSE EVENTS */
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
	real scale = 1.0 - CameraZoomSpeed * delta;
	m_Camera.Scale(scale);
	m_Camera.Translate((m_vMousePosition - m_Camera.Position()) * (1 - scale));
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

	real scale = sqrt(m_Camera.Area() / (w * h));
	m_Camera.SetWH(w * scale, h * scale);
	m_Camera.SetPosition(oldpos);
}

///////////// START GEOMETRY RENDERING
template <class Derived>
void Client<Derived>::Render(const Point& origin, const sf::Color& color, int thickness)
{
	real			radius = thickness;
	sf::CircleShape circle(radius, 48);

	circle.setPosition(origin.x - radius, origin.y - radius);

	circle.setFillColor(color);

	m_Window.draw(circle);
}

template <class Derived>
void Client<Derived>::Render(const Segment& A, const sf::Color& color, int thickness, bool directed)
{
	// 	Render( A.Origin(), color,thickness+1);
	// 	Render( A.End(),color,thickness+1);

	sf::RectangleShape hola(Point(A.Length(), 0));
	hola.setOutlineColor(color);
	hola.setOutlineThickness(thickness);

	hola.rotate(RadiansToDegrees(A.Angle()));
	hola.move(A.Origin());

	m_Window.draw(hola);

	if (directed)
	{
		auto  T   = sf::ConvexShape(3);
		Point dir = (A.End() - A.Origin()).Normalized();
		Point D   = (A.Origin() + A.End()) / 2 + dir * 6;
		T.setPoint(0, D - dir.Rotated(pi / 2) * 7 * thickness);
		T.setPoint(1, D - dir.Rotated(-pi / 2) * 7 * thickness);
		T.setPoint(2, D + dir * 18 * thickness);
		T.setFillColor(color);
		T.setOutlineColor(sf::Color::Red);
		T.setOutlineThickness(0);
		m_Window.draw(T);
		// draw an arrow or something
	}

	/*


	sf::Vector2f aosf(A.Origin().x, A.Origin().y);
	sf::Vector2f aesf(A.End().x, A.End().y);

	sf::Vertex line[2] = {aosf, aesf};

	m_Window.draw(line, 2, sf::Lines);*/
}

template <class Derived>
void Client<Derived>::Render(const Circle&	circle,
							 const sf::Color& fill,
							 const sf::Color& outline,
							 int			  thickness)
{
	real  radius = circle.Radius();
	Point origin = circle.Position();

	sf::CircleShape circleshape(radius, 50);
	circleshape.setPosition(origin.x - radius, origin.y - radius);

	circleshape.setOutlineColor(outline);
	circleshape.setOutlineThickness(thickness);
	circleshape.setFillColor(fill);

	m_Window.draw(circleshape);
}

template <class Derived>
void Client<Derived>::Render(const Circle& circle, const sf::Color& color, int thickness)
{
	Render(circle, color, color, thickness);
}

template <class Derived>
void Client<Derived>::Render(const VP& polygon, const sf::Color& color, int thickness)
{
	if (polygon.empty())
		return;

	vector<sf::Vertex> sfpolygon(polygon.size() + 1);

	for (int i = 0; i < polygon.size(); ++i)
	{
		sfpolygon[i] = sf::Vector2f(polygon[i].x, polygon[i].y);
		Render(polygon[i], color);
	}

	sfpolygon[polygon.size()] = sf::Vector2f(polygon[0].x, polygon[0].y);

	m_Window.draw(&sfpolygon[0], polygon.size() + 1, sf::LinesStrip);
}

template <class Derived>
void Client<Derived>::Render(const Polygon& polygon, const sf::Color& color, int thickness)
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
void Client<Derived>::Render(const Line& line, const sf::Color& color, int thickness)
{
	Render(Segment(line.Position() + line.Direction() * 100000,
				   line.Position() - line.Direction() * 100000),
		   color,
		   thickness);
}

template <class Derived>
void Client<Derived>::Render(const Ray& ray, const sf::Color& color, int thickness)
{
	Render(Segment(ray.Position(), ray.Position() + ray.Direction() * 100000), color, thickness);
}

template <class Derived>
void Client<Derived>::Render(const Box& box, const sf::Color& color, int thickness)
{
	Render(Polygon(box), color, thickness);
}

template <class Derived>
void Client<Derived>::Render(const Box&		  box,
							 const sf::Color& fillcolor,
							 const sf::Color& outlinecolor,
							 int			  thickness)
{
	sf::RectangleShape rectangle(Point(box.Width(), box.Height()));
	rectangle.move(box.UpLeft());
	rectangle.setFillColor(fillcolor);
	rectangle.setOutlineColor(outlinecolor);
	rectangle.setOutlineThickness(thickness);
	m_Window.draw(rectangle);
}

template <class Derived>
void Client<Derived>::Render(const string&	txt,
							 const Point&	 point,
							 const sf::Color& color,
							 int			  size)
{
	sf::Text mytext(txt, m_Font, size);
	mytext.setFillColor(color);

	mytext.setPosition(point);
	m_Window.draw(mytext);
}

template <class Derived>
void Client<Derived>::Render(const Convex& conv, const sf::Color& color, int thickness)
{
	if (conv.Type() == shape_Point)
	{
		Render(conv.Position(), color, thickness);

		return;
	}

	if (conv.Type() == shape_Line)
	{
		const Line* oy = dynamic_cast<const Line*>(&conv);

		Render(*oy, color, thickness);

		return;
	}

	if (conv.Type() == shape_Ray)
	{
		Render(*dynamic_cast<const Ray*>(&conv), color, thickness);

		return;
	}

	if (conv.Type() == shape_Segment)
	{
		Render(*dynamic_cast<const Segment*>(&conv), color, thickness);

		return;
	}

	if (conv.Type() == shape_Circle)
	{
		Render(*dynamic_cast<const Circle*>(&conv), color, thickness);

		return;
	}

	if (conv.Type() == shape_Box)
	{
		Render(*dynamic_cast<const Box*>(&conv), color, thickness);

		return;
	}

	if (conv.Type() == shape_Polygon)
	{
		Render(*dynamic_cast<const Polygon*>(&conv), color, thickness);

		return;
	}
}

template <class Derived>
void Client<Derived>::ClientRenderGUIPanel()
{
	GUI.Render(*this);
}
