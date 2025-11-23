#pragma once
#include <GLFW/glfw3.h>

namespace Core {

class Input {
private:
    static GLFWwindow* s_window;  

public:
    static void Initialize(GLFWwindow* window);
    
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);
    static bool IsKeyJustPressed(int key); 
    
    static bool IsMouseButtonPressed(int button);
    static void GetMousePosition(double& x, double& y);
    static double GetMouseX();
    static double GetMouseY();
    
    static bool IsAnyKeyPressed();
};

}
