#ifndef SHAPE_H
#define SHAPE_H

// #include <entity.h>
#include <renderer.h>

extern std::shared_ptr<Renderer> renderer;

// a closed cylinder 
struct C_cylinder : public Entity {
    C_cylinder(const float& base, const float& top, const float& height, const int slices)
    {
        component = {
            std::make_shared<Cylinder>(base, top, height, slices),
            std::make_shared<Circle>(base, slices),
            std::make_shared<Circle>(top, slices)
        };

        trans = {
            Transform(),
            Transform{{0, - height / 2, 0}, {1, 1, 1}, {90, 0, 0}},
            Transform{{0, + height / 2, 0}, {1, 1, 1}, {90, 0, 0}} 
        };
    }
};

struct Dome_top : public Entity {
    Dome_top(const Transform& transform, const glm::vec3& cl = {255, 255, 255})
    {
        this->transform = transform;
        for (size_t i = 0; i < 4; ++i) {
            if (component.empty()) {
                add(std::make_shared<Sphere>(1, 22, 22), 
                    Transform{{0, 0, 0}, {1.7, 1, 1}}, 
                    cl);
            } else {
                float scale = (i & 1 ? 1.3 : 1.7);
                add(component.back(), Transform{{0, 2 * i, 0}, {scale, 1, 1}}, cl);
            }
            add(component.back(), Transform{{0, 2 * i, 0}, {1, 2, 1}}, cl);
        }
        add(C_cylinder(0.3, 0.3, 1, 50), Transform{{0, 8.4, 0}}, cl);
        add(std::make_shared<Cylinder>(2, 0.5, 50), 
            Transform{{0, 10.9, 0}, {1, 1, 1}, {90, 0, 0}}, 
            cl);

        build();
    }
};

struct Dome : public Entity {
public:
    Dome() 
    {
        add(std::make_shared<Sphere>(2, 22, 22));
        add(std::make_shared<Cylinder>(2.3, 0.1));
        add(std::make_shared<Cylinder>(2, 0.5));
    }
};

inline Dome dome;

struct Entrance : public Entity {
    Entrance(const Transform& transform, const float& len, const float& b_len)
    {
        this->transform = transform;

        auto cube = std::make_shared<Cube>(1);
        for (float i = 0; i < len / 2; i += 0.005) {
            add(cube, Transform{{i, i / 4, 0}, {b_len, b_len, 1}});
            add(cube, Transform{{len - i, i / 4, 0}, {b_len, b_len, 1}});
        }

        // cube with height of 0.5
        add(cube, Transform{{0, -0.25 - b_len / 2, 0}, {b_len, 0.5, 1}});
        add(cube, Transform{{len, -0.25 - b_len / 2, 0}, {b_len, 0.5, 1}});

        // cube with width of 3
        // hw = 1.5
        // 0.25 half height of (top cube)
        add(cube, Transform{{-1.5 + b_len / 2, -0.1 - 0.25 * 2 - b_len / 2, 0},
                            {3, 0.2, 1}});
        add(cube,
            Transform{{len + 1.5 - b_len / 2, -0.1 - 0.25 * 2 - b_len / 2, 0},
                      {3, 0.2, 1}});

        build();
    }
};

struct O_ent : public Entity {
    O_ent(const Transform& transform, const float& len, const float& b_len)
    {
        this->transform = transform;

        auto cube = std::make_shared<Cube>(1);
        for (float i = 0; i < len / 2; i += 0.005) {
            add(cube, Transform{{i, i, 0}, {b_len, b_len, 1}}, {145, 121, 121});
            add(cube, Transform{{len - i, i, 0}, {b_len, b_len, 1}}, {145, 121, 121});
        }

        add(cube, Transform{{0, -2, 0}, {b_len, 4, 1}}, {145, 121, 121});
        add(cube, Transform{{len, -2, 0}, {b_len, 4, 1}}, {145, 121, 121});

        build();
    }
};

struct Tree : public Entity {
    Tree(const Transform& transform, const float& base, const float& top, const float& height) 
    {
        this->transform = transform;

        add(C_cylinder(base, top, height, 100), Transform(), {45, 87, 4});
        add(C_cylinder(top / 2, top / 2, height, 100),
            Transform{{0, -height, 0}}, {91, 31, 22});

        build();
    }
};

struct Grass : public Entity {
    Grass(const Transform& transform, const float& length, const float& height)
    {
        this->transform = transform;

        add(std::make_shared<Cube>(length));

        trans.back().scale = {1, 0.3 / length, height / length};
        trans.back().rotate = {90, 0, 0};

        component.back()->texture.insert(component.back()->texture.end(), 6,
                                         Texture{"assets/g.jpg"});
        build();
    }
};

struct Building : public Entity { 
    Building(const Transform& transform = {}) 
    {
        this->transform = transform;

        add(std::make_shared<Cube>(20));
        component.back()->texture.insert(component.back()->texture.end(), 6,
                                         Texture{"assets/b_face.png"});

        // add(std::make_shared<Sphere>(10, 22, 22), Transform{{0, 4, 0}});

        build();
    }
};

#endif
