/*
 *
 * This code is written by
 * Mohammed Alkhuzanie
 * Mohammed Diab
 * Mohammed Fael
 *
 */

#include <skybox.h>
#include <window.h>

#include <audio.h>

int main(void) {
  Window window;

  renderer->add(std::make_shared<Skybox>());

  window.show();
  return 0;
}
