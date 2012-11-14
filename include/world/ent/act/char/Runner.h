#ifndef RUNNER_H
#define RUNNER_H


#include "SDL.h"

#include "world/ent/act/Actor.h"
#include "gfx/spr/AnimatedSprite.h"
#include "util/Utils.h"

class Runner : public Actor
{
    public:
        Runner( World *_world, Vector2d *_position = &Vector2d::ZERO_VEC );
        virtual ~Runner();

        virtual void render( SDL_Surface *screen );
        virtual void update( SDL_Surface *screen, double delta );

        const int CLASS_ID = ENTITY_RUNNER;
        AnimatedSprite &spr();
    protected:
    private:
};

#endif // RUNNER_H
