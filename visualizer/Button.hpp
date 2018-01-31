#pragma once

class ButtonBase
{
public:
	ButtonBase(const std::string& name = "") : m_name(name) {}
	virtual ~ButtonBase() = default;
	virtual void Activate() = 0;
	
	const std::string& Name() const { return m_name; }
	void SetName(const std::string& newname) { m_name = newname; }
private:
	std::string m_name;
};

template <class Func>
class Button : public ButtonBase
{
public:
	Button(const string& name_, Func f_) : ButtonBase(name_), f(f_) {} 
	void Activate() { f(); }
private:
	Func f;
};
