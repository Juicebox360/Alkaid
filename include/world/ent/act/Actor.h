#ifndef ACTOR_H
#define ACTOR_H

#include <SDL2/SDL.h>

#include "world/ent/Entity.h"

class Actor : public Entity
{
    public:
        Actor( World *_world, int _class_id, Sprite *_sprite, Vector2d *_position = &Vector2d::ZERO_VEC, Vector2d *_velocity = &Vector2d::ZERO_VEC ) : Entity( _world, _class_id, _sprite, _position, _velocity ) {};
        virtual ~Actor();

        virtual void render( SDL_Window *window );
        virtual void update( SDL_Window *window, double delta );
    protected:
    private:
};

#endif // ACTOR_H
