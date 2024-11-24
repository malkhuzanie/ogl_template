#ifndef RENDERER_H
#define RENDERER_H

#include <entity.h>
#include <iostream>

class Renderer {
public:
  Renderer();

  static Renderer &instance();
  void render();
  void add(std::shared_ptr<Entity> entity);

private:
  std::vector<std::shared_ptr<Entity>> entity;
};

#endif
