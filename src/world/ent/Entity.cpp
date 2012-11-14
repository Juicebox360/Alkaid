#include "gfx/spr/Sprite.h"
#include "world/ent/Entity.h"

#include "util/Utils.h"

Entity::Entity( World *_world, int _class_id, Sprite *_sprite, Vector2d *_position, Vector2d *_velocity )
{
    init( _world, _class_id, _sprite, _position, _velocity );
}

Entity::~Entity()
{
    delete position;
    delete velocity;
    delete sprite;

    position = velocity = NULL;
    sprite = NULL;
}

void Entity::init( World *_world, int _class_id, Sprite *_sprite, Vector2d *_position, Vector2d *_velocity )
{
    world = _world;
    position = _position;
    velocity = _velocity;
    sprite = _sprite;

    class_id = _class_id;
}

void Entity::render( SDL_Surface *screen )
{
    if ( sprite != NULL )
    {
        //printf( "uID %i: Drawing the sprite at (%f, %f).\n", unique_id, position->x, position->y );
        sprite->render( screen, position->x, position->y, -1, 1.0d, 1.0d, &Colour::WHITE, 0.0d );
    }
}

void Entity::update( SDL_Surface *screen, double delta )
{
    // Modulate position by velocity
    if ( velocity != NULL && position != NULL )
    {
        position->translate( velocity->x, velocity->y );
    }

    // Update the sprite, if we've got one.
    if ( sprite != NULL )
    {
        sprite->update( screen, delta );
    }
}
