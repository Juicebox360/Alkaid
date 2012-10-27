#ifndef ROCKETMAN_H
#define ROCKETMAN_H

#include "SDL.h"

#include "world/ent/act/Actor.h"
#include "gfx/spr/AnimatedSprite.h"
#include "gfx/spr/Sprite.h"
#include "util/Utils.h"

class Rocketman : public Actor
{
    public:
        Rocketman( World *_world, Vector2d *_position = &Vector2d::ZERO_VEC ) : Actor( _world, CLASS_ID, (spr ? new AnimatedSprite( dynamic_cast<AnimatedSprite*>( spr ) ) : NULL), _position ) { init(); };
        virtual ~Rocketman();

        virtual void render( SDL_Surface *screen );
        virtual void update( SDL_Surface *screen, double delta );

        const int CLASS_ID = ENTITY_ROCKETMAN;
        static Sprite *spr;
    protected:
    private:
        void init();
};

#endif // ROCKETMAN_H
