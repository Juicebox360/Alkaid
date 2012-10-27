#ifndef RUNNER_H
#define RUNNER_H


#include "SDL.h"

#include "world/ent/act/Actor.h"
#include "gfx/spr/AnimatedSprite.h"
#include "gfx/spr/Sprite.h"
#include "util/Utils.h"

class Runner : public Actor
{
    public:
        Runner( World *_world, Vector2d *_position = &Vector2d::ZERO_VEC ) : Actor( _world, CLASS_ID, (spr ? new AnimatedSprite( dynamic_cast<AnimatedSprite*>( spr ) ) : NULL), _position ) { init(); };
        virtual ~Runner();

        virtual void render( SDL_Surface *screen );
        virtual void update( SDL_Surface *screen, double delta );

        const int CLASS_ID = ENTITY_RUNNER;
        static Sprite *spr;
    protected:
    private:
        void init();
};

#endif // RUNNER_H
