#include "../ImGui/imgui.h"
#include <iostream>


//List of function pointers for the key
static void (*Afunc)();

static void setAfunc(void (*_Afunc)())
{
    Afunc = _Afunc;
}

static void (*Dfunc)();

static void setDfunc(void (*_Dfunc)())
{
    Dfunc = _Dfunc;
}

static void (*Sfunc)();

static void setSfunc(void (*_Sfunc)())
{
    Sfunc = _Sfunc;
}

static void (*Wfunc)();

static void setWfunc(void (*_Wfunc)())
{
    Wfunc = _Wfunc;
}

static void (*Spacefunc)();

static void setSpacefunc(void (*_Spacefunc)())
{
    Spacefunc = _Spacefunc;
}

static void (*LeftCtrlfunc)();

static void setLeftCtrlfunc(void (*_LeftCtrlfunc)())
{
    LeftCtrlfunc = _LeftCtrlfunc;
}


static void (*MouseDeltafunc)(int, int);

static void setMouseDeltafunc(void (*_MouseDeltafunc)(int, int))
{
    MouseDeltafunc = _MouseDeltafunc;
}

static void (*MousePosfunc)(int, int);

static void setMousePosfunc(void (*_MousePosfunc)(int, int))
{
    MousePosfunc = _MousePosfunc;
}

static void (*MouseReleasefunc)();

static void setMouseReleasefunc(void (*_MouseReleasefunc)())
{
    MouseReleasefunc = _MouseReleasefunc;
}


//Get inputs
static void InputControler()
{
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
    {
        MouseReleasefunc();
    }


    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsMousePosValid() && !ImGui::GetIO().WantCaptureMouse)
    {
      //  std::cout << "Mouse pos:" << (int)ImGui::GetIO().MousePos.x << " , " << (int)ImGui::GetIO().MousePos.y << std::endl;


     //   std::cout << "Mouse delta: " << (int)ImGui::GetIO().MouseDelta.x<< " , "<< (int)ImGui::GetIO().MouseDelta.y << std::endl;

        MousePosfunc((int)ImGui::GetIO().MousePos.x, (int)ImGui::GetIO().MousePos.y);

        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }
    else
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    }
    


    struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
    ImGuiKey start_key = (ImGuiKey)0;

    //test all key to see if they are pressed
    for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
    {
        //only continue if the current key is pressed
        //apply on first frame of the key
        if (!ImGui::IsKeyPressed(key)) continue;


    }

    for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
    {
        //always apply if key is down
        if (!ImGui::IsKeyDown(key)) continue;

        if (key == ImGuiKey_A)
        {
          //  std::cout << "A" << std::endl;
            Afunc();
        }
        if (key == ImGuiKey_D)
        {
          //  std::cout << "D" << std::endl;
            Dfunc();
        }
        if (key == ImGuiKey_S)
        {
          //  std::cout << "S" << std::endl;
            Sfunc();
        }
        if (key == ImGuiKey_W)
        {
          //  std::cout << "W" << std::endl;
            Wfunc();
        }
        if (key == ImGuiKey_Space)
        {
          //  std::cout << "Space" << std::endl;
            Spacefunc();
        }
        if (key == ImGuiKey_LeftCtrl)
        {
          //  std::cout << "LeftCtrl" << std::endl;
            LeftCtrlfunc();
        }
    }

    /*
    for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
    {
        //apply on last frame
        if (!ImGui::IsKeyReleased(key)) continue;
    }
    */


}

