#include "SDL.h"

#include "util/Utils.h"
#include "util/Constants.h"
#include "world/ent/act/Actor.h"
#include "world/ent/act/char/Runner.h"
#include "gfx/spr/AnimatedSprite.h"
#include "gfx/spr/Sprite.h"

Sprite *Runner::spr = NULL;

Runner::~Runner()
{
    //dtor
}

void Runner::render( SDL_Surface *screen )
{
    Actor::render( screen );
}

void Runner::update( SDL_Surface *screen, double delta )
{
    Actor::update( screen, delta );
}

void Runner::init()
{
    if ( Runner::spr == NULL )
    {
        //Runner::spr = new Sprite( Utils::concat( Constants::SPRITE_DIR, "class/SoldierStrip.png" ), 64, 64, 32, 32 );
        Runner::spr = new AnimatedSprite( Utils::concat( Constants::SPRITE_DIR, "class/ScoutStrip.png" ), 300, 2, 3, true, 64, 64, 32, 32 );
        sprite = new AnimatedSprite( dynamic_cast<AnimatedSprite*>( spr ) );
    }
}
