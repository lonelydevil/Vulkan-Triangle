#ifndef GLFW_FUN_H
#define GLFW_FUN_H

#include "std_c.h"
#include "ext.h"

GLFWwindow *createVulkanWindow(int width, int height, const char *title);
void deleteWindow(GLFWwindow *pWindow);

#endif // GLFW_FUN_H
