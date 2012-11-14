#ifndef ENTITYENUMS_H
#define ENTITYENUMS_H

#include "world/ent/Entity.h"
#include "world/World.h"
#include "util/Vector2d.h"
#include "util/ObjectFactory.h"

// Add entity types here, but don't forget to add the
// function registers in EntityEnums.cpp!
enum ENTITY
{
   ENTITY_RUNNER,
   ENTITY_ROCKETMAN,
   ENTITY_HEALER
};

class Entity;
class World;

class EntityEnums
{
    public:
        static void pre_init( ObjectFactory<Entity* (World*, Vector2d*), int> &factory );
};

#endif // ENTITYENUMS_H
