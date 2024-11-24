#include <renderer.h>

std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();

Renderer::Renderer() {}

void Renderer::render() {
  for (const auto &ent : entity) {
    glPushMatrix();
    ent->render();
    glPopMatrix();
  }
}

void Renderer::add(std::shared_ptr<Entity> entity) {
  this->entity.emplace_back(entity);
}

Renderer &Renderer::instance() {
  static Renderer instance;
  return instance;
}
