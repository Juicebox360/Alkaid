#ifndef HEALER_H
#define HEALER_H

#include <SDL2/SDL.h>

#include "world/ent/act/Actor.h"
#include "gfx/spr/AnimatedSprite.h"
#include "util/Utils.h"

class Healer : public Actor
{
    public:
        Healer( World *_world, Vector2d *_position = &Vector2d::ZERO_VEC );
        virtual ~Healer();

        virtual void render( SDL_Window *window );
        virtual void update( SDL_Window *window, double delta );

        const int CLASS_ID = ENTITY_HEALER;
        AnimatedSprite &spr();
    protected:
    private:
};

#endif // HEALER_H
