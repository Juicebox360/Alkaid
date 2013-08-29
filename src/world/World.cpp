#include <SDL2/SDL.h>

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

void World::render( SDL_Window *window )
{
    entities->render( window );
}

void World::update( SDL_Window *window, double delta )
{
    entities->update( window, delta );
}
