#include <renderer.h>
#include <window.h>

Camera camera;
glm::vec2 prev{0, 0};

bool first = true;

std::vector<GLfloat> ambient_light = {1, 1, 1, 1.0};
std::vector<GLfloat> diffuse_light = {1.0, 1.0, 1.0, 1.0};
std::vector<GLfloat> light_pos = {1.0, 0.0, -3.0, 1.0};
std::vector<GLfloat> mat_ambient = {1.0f, 0.5f, 0.5f, 1.0f};
std::vector<GLfloat> mat_diffuse = {0.5, 0.5, 0.5, 1.0};
std::vector<GLfloat> mat_specular = {0.3, 0.2, 0.4, 1.0};
std::vector<GLfloat> mat_shininess = {0.5, 0.5, 0.5, 1.0};

void Window::init() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  glShadeModel(GL_SMOOTH);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  init_texture();
  init_lighting();
  camera = Camera();
}

void Window::init_lighting() {
  glLightfv(GL_LIGHT1, GL_AMBIENT, &ambient_light[0]);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, &diffuse_light[0]);
  glLightfv(GL_LIGHT1, GL_POSITION, &light_pos[0]);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);
  glMaterialf(GL_FRONT, GL_AMBIENT, mat_ambient[0]);
  glMaterialf(GL_FRONT, GL_DIFFUSE, mat_diffuse[0]);
  glMaterialf(GL_FRONT, GL_SPECULAR, mat_specular[0]);
  glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess[0]);
  glEnable(GL_COLOR_MATERIAL);
}

void Window::init_texture() { glEnable(GL_TEXTURE_2D); }

Window::Window(int width, int height, std::string title) {
  if (!glfwInit()) {
    error("---------- cannot initialise glfw library ----------");
  }
  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!window) {
    error("Error. Cannot create window!");
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(1);

  glfwSetKeyCallback(window, key_callback);
  glfwSetCharCallback(window, character_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetTime(0.0);

  init();
}

void Window::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  camera.set_view();

  Renderer::instance().render();
}

void Window::show() {
  while (!glfwWindowShouldClose(window)) {
    // key_callback();

    display();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Window::close() { glfwSetWindowShouldClose(window, true); }

void Window::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  glViewport(0, 0, std::max(width, 1), std::max(height, 1));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(camera.fov, (float)width / (float)height, 0.1f, 2000.0);
  // gluOrtho2D(0, 100, 0, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action,
                          int mods) {
  switch (key) {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, true);
    break;
  case GLFW_KEY_K:
    camera.keyboard(FORWARD);
    break;
  case GLFW_KEY_J:
    camera.keyboard(BACKWARD);
    break;
  case GLFW_KEY_H:
    camera.keyboard(LEFT);
    break;
  case GLFW_KEY_L:
    camera.keyboard(RIGHT);
    break;
  }
}

void Window::character_callback(GLFWwindow *window, unsigned int codepoint) {
  switch (codepoint) {
  case 'q':
    glfwSetWindowShouldClose(window, true);
    break;
  case 'm': {
    GLint mode[2];
    glGetIntegerv(GL_POLYGON_MODE, mode);
    if (mode[0] == GL_FILL) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    break;
  }
  }
}

void Window::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (first) {
    prev = {xpos, ypos};
    first = false;
  }
  camera.mouse(xpos - prev.x, prev.y - ypos);
  prev = {xpos, ypos};
}
