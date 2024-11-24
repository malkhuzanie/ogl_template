#include <clock.h>
#include <renderer.h>
#include <window.h>

int main(void) {
  Window window;

  Renderer::instance().add(std::make_shared<Clock>());

  window.show();
  return 0;
}
