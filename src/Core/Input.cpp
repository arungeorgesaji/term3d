#include "Core/Input.h"

namespace Core {

GLFWwindow* Input::s_window = nullptr;

void Input::Initialize(GLFWwindow* window) {
    s_window = window;
}

bool Input::IsKeyPressed(int key) {
    if (!s_window) return false;
    return glfwGetKey(s_window, key) == GLFW_PRESS;
}

bool Input::IsKeyReleased(int key) {
    if (!s_window) return false;
    return glfwGetKey(s_window, key) == GLFW_RELEASE;
}

bool Input::IsMouseButtonPressed(int button) {
    if (!s_window) return false;
    return glfwGetMouseButton(s_window, button) == GLFW_PRESS;
}

void Input::GetMousePosition(double& x, double& y) {
    if (s_window) {
        glfwGetCursorPos(s_window, &x, &y);
    } else {
        x = y = 0.0;
    }
}

double Input::GetMouseX() {
    double x, y;
    GetMousePosition(x, y);
    return x;
}

double Input::GetMouseY() {
    double x, y;
    GetMousePosition(x, y);
    return y;
}

bool Input::IsAnyKeyPressed() {
    if (!s_window) return false;
    
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) {
        if (glfwGetKey(s_window, key) == GLFW_PRESS) {
            return true;
        }
    }
    return false;
}

} 
