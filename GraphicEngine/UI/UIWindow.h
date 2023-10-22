
#ifndef UIWINDOW_CLASS_H
#define UIWINDOW_CLASS_H

class UIWindow
{
protected:
	std::string name;
public:
	UIWindow(std::string _name) { name = _name; }
	virtual void DisplayWindow() {};
	std::string getName() { return name; }
};

#endif