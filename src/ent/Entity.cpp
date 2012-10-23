#include "gfx/Sprite.h"
#include "ent/Entity.h"

Entity::Entity( EntityController *_entityControl, int _classID, Sprite *_sprite, Vector2d *_position, Vector2d *_velocity, Vector2d *_acceleration )
{
    init( _entityControl, _classID, _sprite, _position, _velocity, _acceleration );
}

Entity::~Entity()
{
    //dtor
}

void Entity::init( EntityController *_entityControl, int _classID, Sprite *_sprite, Vector2d *_position, Vector2d *_velocity, Vector2d *_acceleration )
{
    entityControl = _entityControl;
    position = _position;
    velocity = _velocity;
    sprite = _sprite;

    uniqueID = entityControl->generateNextUniqueID();
    classID = _classID;
}

void Entity::render( SDL_Surface *screen, double x, double y, int index, double xScale, double yScale, Colour *colour, double theta )
{
    if ( sprite != NULL )
    {
        sprite->render( screen, x, y, index, xScale, yScale, colour, theta );
    }
}

void Entity::update( SDL_Surface *screen, int delta )
{
    // First, modulate the velocity by acceleration
    if ( acceleration != NULL && velocity != NULL )
    {
        velocity->translate( acceleration->x, acceleration->y );
    }

    // Then modulate position by velocity
    if ( velocity != NULL && position != NULL )
    {
        position->translate( acceleration->x, acceleration->y );
    }

    // Update the sprite, if we've got one.
    if ( sprite != NULL )
    {
        sprite->update( screen, delta );
    }
}
