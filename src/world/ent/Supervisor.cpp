#include <SDL2/SDL.h>

#include "world/ent/Supervisor.h"
#include "world/ent/Entity.h"
#include "world/World.h"
#include "util/Vector2d.h"
#include "util/ObjectFactory.h"

ObjectFactory<Entity* (World*, Vector2d*), int> Supervisor::entity_factory;

void Supervisor::pre_init()
{
    EntityEnums::pre_init( Supervisor::entity_factory );
}

Supervisor::Supervisor()
{
}

Supervisor::~Supervisor()
{
}

Entity *Supervisor::entity_create( int entity_typename, World *world, Vector2d *location )
{
    Entity *temp_entity = Supervisor::entity_factory.create( entity_typename, world, location );
    entities.push_back( temp_entity );
    return temp_entity;
}

// This method merely disconnects the given entity from the controller,
// and thusly the world. It does not destroy the instance itself.
bool Supervisor::entity_remove( Entity *entity )
{
    printf( "Removing an entity\n" );
    // First, check if the entity exists in this Supervisor
    if ( entity_exists( entity ) )
    {
        // If it does, remove that index
        printf( "Entity exists, now releasing\n" );
        Entity *temp = entities.release( get_entity_index( entity ) ).release();
        printf( "Released entity\n" );
        return true;
    }

    return false;
}

// This method actually deletes the instance. Use with caution!
bool Supervisor::entity_kill( Entity *entity )
{
    printf( "Killing an entity\n" );
    if ( entity_remove( entity ) )
    {
        printf( "Deleting entity pointer\n" );
        delete entity;
        printf( "Nullifying entity pointer\n" );
        entity = NULL;
        printf( "Exiting entity kill\n" );
        return true;
    }

    return false;
}

bool Supervisor::entity_exists( Entity *entity )
{
    printf( "Checking for an entity\n" );
    // The check whether the entity exists is very
    // cursory; it merely compares the entity's world's
    // Supervisor with itself.
    return ( (entity->world->entities) == this );
}

boost::ptr_vector<Entity> *Supervisor::entity_list()
{
    return &entities;
}

int Supervisor::entity_count()
{
    return entities.size();
}

void Supervisor::reset()
{
    entities.clear();
}

void Supervisor::render( SDL_Window *window )
{
    for ( int i = 0; i < entities.size(); i++ )
    {
        //printf( "uID %i: WILL BE drawing the sprite at (%f, %f).\n", entity.first, entity.second->position->x, entity.second->position->y );
        entities[i].render( window );
    }
}

void Supervisor::update( SDL_Window *window, double delta )
{
    for ( int i = 0; i < entities.size(); i++ )
    {
        entities[i].update( window, delta );
    }
}

boost::ptr_vector<Entity>::iterator Supervisor::get_entity_index( Entity *entity )
{
    printf( "Finding entity index\n" );
    return std::find_if( entities.begin(), entities.end(), CheckPointerValue( entity ) );
}
