#include "SDL.h"

#include "util/Utils.h"
#include "util/Constants.h"
#include "world/ent/act/Actor.h"
#include "world/ent/act/char/Healer.h"
#include "gfx/spr/AnimatedSprite.h"
#include "gfx/spr/Sprite.h"

Sprite *Healer::spr = NULL;

Healer::~Healer()
{
    //dtor
}

void Healer::render( SDL_Surface *screen )
{
    Actor::render( screen );
}

void Healer::update( SDL_Surface *screen, double delta )
{
    Actor::update( screen, delta );
}

void Healer::init()
{
    if ( Healer::spr == NULL )
    {
        //Healer::spr = new Sprite( Utils::concat( Constants::SPRITE_DIR, "class/SoldierStrip.png" ), 64, 64, 32, 32 );
        Healer::spr = new AnimatedSprite( Utils::concat( Constants::SPRITE_DIR, "class/MedicStrip.png" ), 400, 2, 3, true, 64, 64, 32, 32 );
        sprite = new AnimatedSprite( dynamic_cast<AnimatedSprite*>( spr ) );
    }
}
