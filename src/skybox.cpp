#include <skybox.h>

Skybox::Skybox() {
  add(std::make_shared<Cube>(1400));
  component.back()->texture.insert(component.back()->texture.end(), 6,
                                   Texture{"assets/skybox_face.png"});
  component.back()->texture[2] = Texture{"assets/skybox_face.png"};

  trans.back().translate = {200, 200, 0};
  trans.back().scale = {2, 900.0f / 1400.0f, 1};

  build();
}
