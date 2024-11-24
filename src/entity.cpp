#include <entity.h>

void Entity::add(std::shared_ptr<Shape> comp, const Transform& tr,
        const glm::vec3& cl)
{
    component.emplace_back(comp);
    trans.emplace_back(tr);
    colour.emplace_back(cl);
}

void Entity::add(const Entity& ent, const Transform& tr, const glm::vec3& cl)
{
    for (size_t i = 0; i < ent.component.size(); ++i) {
        add(ent.component[i], ent.trans[i] + tr, cl);
    }
}

void Entity::build()
{
    for (const auto& comp : component) {
        comp->build(comp->type);
    }
}

void Entity::render()
{
    glPushMatrix();

    glTranslatef(transform.translate.x, transform.translate.y, transform.translate.z);
    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
    glRotated(transform.rotate.x, 1, 0, 0);
    glRotated(transform.rotate.y, 0, 1, 0);
    glRotated(transform.rotate.z, 0, 0, 1);

    auto it = trans.begin();
    auto cl = colour.begin();
    for (const auto& comp : component) {
        glPushMatrix();

        glColor3ub(cl->x, cl->y, cl->z);
        glTranslatef(it->translate.x, it->translate.y, it->translate.z);
        glScalef(it->scale.x, it->scale.y, it->scale.z);
        glRotated(it->rotate.x, 1, 0, 0);
        glRotated(it->rotate.y, 0, 1, 0);
        glRotated(it->rotate.z, 0, 0, 1);

        comp->render();
        glPopMatrix();
        ++it;
        ++cl;
    }
    glPopMatrix();
}

unsigned int Entity::size() 
{
    return component.size();
}

const std::vector<std::shared_ptr<Shape>>& Entity::data()
{
    return component;
}
