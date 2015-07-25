#include "SolverKey.h"

#include <Physics/Collider.h>

using namespace walt;
using namespace glm;

unsigned int walt::SolverKey::get(Collider* a, Collider* b)
{
    int aid = a->id;
    int bid = b->id;

    if (aid == bid) {
        fprintf(stderr, "Impossible to collide itself.");
        throw 1;
    }
    else if (aid < bid) {
        return aid * Collider::MaxId + bid;
    }
    else {
        return bid * Collider::MaxId + aid;
    }
}
