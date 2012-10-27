#include "SDL.h"

#include "util/Utils.h"
#include "util/Constants.h"
#include "world/ent/act/Actor.h"
#include "world/ent/act/char/Rocketman.h"
#include "gfx/spr/AnimatedSprite.h"
#include "gfx/spr/Sprite.h"

Sprite *Rocketman::spr = NULL;

Rocketman::~Rocketman()
{
    //dtor
}

void Rocketman::render( SDL_Surface *screen )
{
    Actor::render( screen );
}

void Rocketman::update( SDL_Surface *screen, double delta )
{
    Actor::update( screen, delta );
}

void Rocketman::init()
{
    if ( Rocketman::spr == NULL )
    {
        //Rocketman::spr = new Sprite( Utils::concat( Constants::SPRITE_DIR, "class/SoldierStrip.png" ), 64, 64, 32, 32 );
        Rocketman::spr = new AnimatedSprite( Utils::concat( Constants::SPRITE_DIR, "class/SoldierStrip.png" ), 500, 2, 3, true, 64, 64, 32, 32 );
        sprite = new AnimatedSprite( dynamic_cast<AnimatedSprite*>( spr ) );
    }
}
