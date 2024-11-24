#include <component.h>

void Renderable::build(GLenum mode)
{
    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    glPushMatrix();
    auto tex = texture.begin();
    auto cor = tex_cor.begin();
    for (auto it = vertex.begin(); it != vertex.end(); ) {
        if (tex != texture.end() && tex->id) {
            tex->bind();
        }
        glBegin(mode);
            for (int i = 0; i < offset; ++i) {
                if (cor != tex_cor.end()) {
                    glTexCoord2f(cor->x, cor->y);
                    ++cor;
                }
                auto cur = std::next(it, i);
                glVertex3f(cur->x, cur->y, cur->z);
            }
        glEnd();
        it = std::next(it, offset);
        if (tex != texture.end()) {
            tex->unbind();
            ++tex;
        }
    }
    glPopMatrix();
    glEndList();
}

void Renderable::texture_repeat(const int& xr, const int& yr) 
{
    for (auto& cor : tex_cor) {
        cor.x = (cor.x ? xr : cor.x);
        cor.y = (cor.y ? yr : cor.y);
    }
}

void Renderable::texture_repeat(const int& xr, const int& yr, const int& face) {}

void Shape::render()
{
    glCallList(list_id);
}

Rectangle::Rectangle(const glm::vec2& p, const float& w, const float& h)
{
    offset = 4;
    vertex = {
        {p.x, p.y, 0, 1}, {p.x + w, p.y, 0, 1},
        {p.x + w, p.y + h, 0, 1}, {p.x, p.y + h, 0, 1}
    };
}

Rectangle::Rectangle(const float& w, const float& h)
{
    auto hw = w / 2;
    auto hh = h / 2;
    vertex.emplace_back(glm::vec4(-hw, -hh, 0, 1));
    vertex.emplace_back(glm::vec4( hw, -hh, 0, 1));
    vertex.emplace_back(glm::vec4( hw,  hh, 0, 1));
    vertex.emplace_back(glm::vec4(-hw,  hh, 0, 1));

    tex_cor = {
        {0, 0}, {1, 0}, {1, 1}, {0, 1}
    };

    offset = 4;
    type = GL_QUADS;
}

std::vector<glm::vec3> Circle::gen_vertices(const T& radius, int count)
{
    std::vector<glm::vec3> vertex;
    const float angle = 360.0f / (float) count;
    for (int i = 0; i < count; ++i) {
        float theta = angle * (float) i;
        vertex.emplace_back(radius * cos(glm::radians(theta)), 0,
                            radius * sin(glm::radians(theta)));
    }
    return vertex;
}

Circle::Circle(const T& radius, int count)
{
    const float angle = 360.0f / (float) count;
    for (int i = 0; i < count; ++i) {
        float theta = angle * (float) i;
        vertex.emplace_back(radius * cos(glm::radians(theta)),
                            radius * sin(glm::radians(theta)),
                            0.0f, 1.0f);
    }
    // vertex.emplace_back(glm::vec4(radius, 0, 0, 1));

    offset = vertex.size();
    type = GL_TRIANGLE_FAN;
}

Sphere::Sphere(const float& radius, const int& stacks, const int& slices) 
{
    offset = 3;
    for (int i = 0; i < stacks; ++i) {
        float phi1 = M_PI * (float) i / stacks;
        float phi2 = M_PI * (float) (i + 1) / stacks;
        for (int j = 0; j < slices; ++j) {
            float theta1 = 2 * M_PI * (float) j / slices;
            float theta2 = 2 * M_PI * (float) (j + 1) / slices;
            vertex.emplace_back(
                    radius * sin(phi1) * cos(theta1),
                    radius * sin(phi1) * sin(theta1),
                    radius * cos(phi1), 1);
            vertex.emplace_back(
                    radius * sin(phi1) * cos(theta2),
                    radius * sin(phi1) * sin(theta2),
                    radius * cos(phi1), 1);
            vertex.emplace_back(
                    radius * sin(phi2) * cos(theta2),
                    radius * sin(phi2) * sin(theta2),
                    radius * cos(phi2), 1);

            vertex.emplace_back(vertex[vertex.size() - 3]);
            vertex.emplace_back(vertex[vertex.size() - 2]);
            vertex.emplace_back(
                    radius * sin(phi2) * cos(theta1),
                    radius * sin(phi2) * sin(theta1),
                    radius * cos(phi2), 1);
        }
    }
    type = GL_TRIANGLES;
}

Cube::Cube(const double& len)
{
    offset = 4;

    auto hl = len / (float) 2;
    vertex = {
        {-hl, -hl,  hl, 1}, { hl, -hl,  hl, 1}, { hl,  hl,  hl, 1}, {-hl,  hl,  hl, 1}, 
        {-hl, -hl, -hl, 1}, {-hl,  hl, -hl, 1}, { hl,  hl, -hl, 1}, { hl, -hl, -hl, 1},
        {-hl,  hl, -hl, 1}, {-hl,  hl,  hl, 1}, { hl,  hl,  hl, 1}, { hl,  hl, -hl, 1},
        {-hl, -hl, -hl, 1}, { hl, -hl, -hl, 1}, { hl, -hl,  hl, 1}, {-hl, -hl,  hl, 1}, 
        { hl, -hl, -hl, 1}, { hl,  hl, -hl, 1}, { hl,  hl,  hl, 1}, { hl, -hl,  hl, 1},
        {-hl, -hl, -hl, 1}, {-hl, -hl,  hl, 1}, {-hl,  hl,  hl, 1}, {-hl,  hl, -hl, 1}
    };

    tex_cor = {
        {0, 0}, {1, 0}, {1, 1}, {0, 1},
        {1, 0}, {1, 1}, {0, 1}, {0, 0},
        {0, 1}, {0, 0}, {1, 0}, {1, 1},
        {1, 1}, {0, 1}, {0, 0}, {1, 0},
        {1, 0}, {1, 1}, {0, 1}, {0, 0},
        {0, 0}, {1, 0}, {1, 1}, {0, 1},
    };

    type = GL_QUADS;
}

void Cube::texture_repeat(const int& xr, const int& yr, const int& face)
{
    if (!face) {
        error("face number starts from 1");
    }
    for (int i = 4 * (face - 1); i < 4 * face; ++i) {
        tex_cor[i].x = (tex_cor[i].x ? xr : tex_cor[i].x);
        tex_cor[i].y = (tex_cor[i].y ? yr : tex_cor[i].y);
    }
}
