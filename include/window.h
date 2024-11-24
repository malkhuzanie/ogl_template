#ifndef WINDOW_H
#define WINDOW_H

#include <camera.h>
#include <utils.h>
// #include <renderer.h>
#include <entity.h>

class Window {
public:
  Window(int width = 1920, int height = 1080, std::string title = "window");

  void init();
  void init_texture();
  void init_lighting();
  void show();
  void display();
  void close();

  // callback functions
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);
  static void character_callback(GLFWwindow *window, unsigned int codepoint);
  static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

private:
  GLFWwindow *window;
};

#endif
