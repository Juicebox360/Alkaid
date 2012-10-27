#include "SDL.h"

#include "world/World.h"
#include "world/ent/EntityController.h"

World::World()
{
    entities = new EntityController();
}

World::~World()
{
    delete entities;
    entities = NULL;
}

EntityController *World::get_entity_controller()
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
