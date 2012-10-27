#include <SDL.h>

#include "world/ent/EntityController.h"
#include "world/ent/Entity.h"
#include "world/World.h"
#include "util/Vector2d.h"
#include "util/ObjectFactory.h"

ObjectFactory<Entity *(World*, Vector2d*), int> EntityController::entity_factory;

void EntityController::pre_init()
{
    EntityEnums::pre_init( EntityController::entity_factory );
}

EntityController::EntityController()
{
}

EntityController::~EntityController()
{
}

long EntityController::generate_next_unique_id()
{
    return curr_unique_id++;
}

long EntityController::get_current_unique_id()
{
    return curr_unique_id;
}

Entity *EntityController::entity_create( int entity_typename, World *world, Vector2d *location )
{
    Entity *temp_entity = EntityController::entity_factory.create( entity_typename, world, location );
    entities.insert( std::make_pair( temp_entity->unique_id, temp_entity ) );
    return temp_entity;
}

// This method merely disconnects the given entity from the controller,
// and thusly the world. It does not destroy the instance itself.
bool EntityController::entity_remove( Entity *entity )
{
    return entity_remove( entity->unique_id );
}
bool EntityController::entity_remove( long unique_id )
{
    return (entities.erase( unique_id ) != 0);
}

// This method actually deletes the instance. Use with caution!
bool EntityController::entity_kill( Entity *entity )
{
    if ( entities.erase( entity->unique_id ) != 0 )
    {
        delete entity;
        entity = NULL;
        return true;
    }

    return false;
}
bool EntityController::entity_kill( long unique_id )
{
    return entity_kill( entity_get( unique_id ) );
}

bool EntityController::entity_exists( Entity *entity )
{
    return (entity_exists( entity->unique_id ));
}
bool EntityController::entity_exists( long unique_id )
{
    return (entities.count( unique_id ) > 0);
}

Entity *EntityController::entity_get( long unique_id )
{
    if ( !entity_exists( unique_id ) )
    {
        return NULL;
    }

    return entities.find( unique_id )->second;
}

std::map<long, Entity*> *EntityController::entity_list()
{
    return &entities;
}

void EntityController::reset()
{
    curr_unique_id = 0;

    for ( auto entity : entities )
    {
        entity_kill( entity.first );
    }
    entities.clear();
}

void EntityController::render( SDL_Surface *screen )
{
    for ( auto entity : entities )
    {
        //printf( "uID %i: WILL BE drawing the sprite at (%f, %f).\n", entity.first, entity.second->position->x, entity.second->position->y );
        (entity.second)->render( screen );
    }
}

void EntityController::update( SDL_Surface *screen, double delta )
{
    for ( auto entity : entities )
    {
        (entity.second)->update( screen, delta );
    }
}
