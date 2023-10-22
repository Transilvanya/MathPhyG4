#ifndef BASICUIWINDOW_CLASS_H
#define BASICUIWINDOW_CLASS_H
#include "../UIWindow.h"
#include "../../ImGui/imgui.h"



class BasicUIWindow : public UIWindow
{
private:
	void (*Lockfunc)();
public:
	


	void setfunc(void (*_func)())
	{
		Lockfunc = _func;
	}

	BasicUIWindow(std::string name, void (*_func)()) :  UIWindow(name)
	{

		Lockfunc = _func;
	}

	virtual void DisplayWindow()
	{
		ImGui::Begin("Debug");
		if (ImGui::CollapsingHeader("Help"))
		{
			ImGui::SeparatorText("ABOUT THIS DEMO:");
			ImGui::BulletText("Camera controls : ZQSD (qwerty), WASD (azerty),\n crtl to go down, space to go up, mouse left click to orient the camera.");
			ImGui::BulletText("The rotation of the camera will be fixed at the center\n of the screen but will keep rotation we the mouse reach the edges.");
			ImGui::BulletText("The blue shape indicape the forces applied to the particule");
		}
		if (ImGui::Button("Button"))
		{
			Lockfunc();
		}

		ImGui::End();
	}
};


#endif