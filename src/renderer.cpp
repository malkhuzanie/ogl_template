#include <renderer.h>

std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();

Renderer::Renderer() 
{ 
}

void Renderer::render()
{
    auto it = trans.begin();

    glPushMatrix();
    for (const auto& ent : entity) {
        glPushMatrix();

        glTranslatef(it->translate.x, it->translate.y, it->translate.z);
        glScalef(it->scale.x, it->scale.y, it->scale.z);
        glRotated(it->rotate.x, 1, 0, 0);
        glRotated(it->rotate.y, 0, 1, 0);
        glRotated(it->rotate.z, 0, 0, 1);

        ent->render();

        ++it;
        glPopMatrix();
    }
    glPopMatrix();
}

void Renderer::add(std::shared_ptr<Entity> entity, const Transform& transform)
{
    this->entity.emplace_back(entity);
    trans.emplace_back(transform);
}

Renderer& Renderer::instance()
{
    static Renderer instance;
    return instance;
}
