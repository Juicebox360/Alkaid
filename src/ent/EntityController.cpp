#include <SDL.h>

#include "ent/EntityController.h"
#include "ent/Entity.h"

EntityController::EntityController()
{
}

EntityController::~EntityController()
{
}

int EntityController::generateNextUniqueID()
{
    return ++currUniqueID;
}

bool EntityController::addEntityToWorld( Entity *entity )
{
    //return world->addEntity( entity );
    return true;
}

bool EntityController::removeEntityFromWorld( Entity *entity )
{
    //return world->removeEntity( entity );
    return true;
}

bool EntityController::removeEntityFromWorld( int uniqueID )
{
    //return world->removeEntity( uniqueID );
    return true;
}

bool EntityController::entityIsInWorld( Entity *entity )
{
    //return (world->findEntity( entity ) != -1);
    return true;
}

bool EntityController::entityIsInWorld( int uniqueID )
{
    //return (world->findEntity( uniqueID ) != -1);
    return true;
}

void EntityController::render( SDL_Surface *screen )
{
    //world->render( screen );
}

void EntityController::update( SDL_Surface *screen, int delta )
{
    //world->update( screen );
}
