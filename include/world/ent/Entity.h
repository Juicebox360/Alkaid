#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

#include "world/World.h"
#include "gfx/spr/Sprite.h"
#include "util/Vector2d.h"

class World;

class Entity
{
    public:
        Entity( World *_world, int _class_id, Sprite *_sprite = NULL, Vector2d *_position = NULL, Vector2d *_velocity = NULL );
        virtual ~Entity();
        //virtual void render( SDL_Window *window, double x, double y, int index = 0, double x_scale = 1, double y_scale = 1, Colour *colour = &Colour::WHITE, double theta = 0 );
        virtual void render( SDL_Window *window );
        virtual void update( SDL_Window *window, double delta );

        World *world;
        Vector2d *position, *velocity;
        Sprite *sprite;
        long class_id;
    protected:
    private:
        void init( World *_world, int _class_id, Sprite *_sprite, Vector2d *_position, Vector2d *_velocity );
};

#endif // ENTITY_H
