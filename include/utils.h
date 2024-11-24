#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <stdexcept>
#include <iostream>
#include <random>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <glad/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>


inline void error(const std::string& err)
{
    throw std::runtime_error(err);
}

// template <typename T>
// std::ostream& operator<<(std::ostream& os, const T& g)
// {
//     os << glm::to_string(g);
// }

// template <typename T>
// float rand(const T& low, const T& high)
// {
//     std::random_device r;
//     static std::default_random_engine eng{r()};
//     static std::uniform_real_distribution<> dis(
//             low,
//             std::nextafter(high, std::numeric_limits<T>::max())
//             );
//     return dis(eng);
// }

#endif 
