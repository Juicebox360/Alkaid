#include "SDL.h"

#include "world/World.h"
#include "world/ent/Supervisor.h"

World::World()
{
    entities = new Supervisor();
}

World::~World()
{
}

Supervisor *World::get_entity_supervisor()
{
    return entities;
}

void World::render( SDL_Surface *screen )
{
    entities->render( screen );
}

void World::update( SDL_Surface *screen, double delta )
{
    entities->update( screen, delta );
}
