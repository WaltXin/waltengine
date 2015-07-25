#include "Solver.h"

#include <glm/gtx/norm.hpp>

#include <Components/Transform.h>
#include <Physics/Collider.h>
#include <Physics/Contact.h>
#include <Physics/ContactConstraint.h>
#include <Physics/Physics.h>
#include <Physics/SolverManager.h>
#include <GameObject.h>

using namespace walt;
using namespace glm;

Solver::Solver(SolverManager* manager, Collider* a, Collider* b)
{
    this->manager = manager;
    this->a = a;
    this->b = b;
    a->solvers.push_back(this);
    b->solvers.push_back(this);
}

Solver::~Solver()
{
    a->solvers.remove(this);
    b->solvers.remove(this);
}

void Solver::addContact(glm::vec3& worldA, glm::vec3& worldB, glm::vec3& normal)
{
    auto point = 0.5f * (worldA + worldB);

    for (auto& contact : contacts)
    {
        if (length2(contact->point - point) < 1)
        {
            contact->update(worldA, worldB, normal);
            return;
        }
    }

    auto contact = new Contact(a, b, worldA, worldB, normal);
    contacts.push_back(contact);
    a->contacts.push_back(contact);
    b->contacts.push_back(contact);
}

void Solver::update()
{
    for (auto it = contacts.begin(); it != contacts.end();)
    {
        auto contact = *it;

        if (contact->getDistanceSquared() > 0.04f && contact->totalTicks != Physics::totalTicks)
        {
            a->contacts.remove(contact);
            b->contacts.remove(contact);
            it = contacts.erase(it);
        }
        else
        {
            if (manager->iteration == 0) {
                contact->constraint->prepareForIteration();
            } else {
                contact->constraint->iterate();
            }
            ++it;
        }
    }
}
