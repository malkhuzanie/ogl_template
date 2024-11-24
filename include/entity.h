#ifndef ENTITY_H
#define ENTITY_H

#include <component.h>

struct Entity {
  Entity() {}
  virtual void render() = 0;
};

#endif
