#include <SDL2/SDL.h>

#include "util/Utils.h"
#include "util/Constants.h"
#include "world/ent/act/Actor.h"
#include "world/ent/act/char/Rocketman.h"
#include "gfx/spr/AnimatedSprite.h"

Rocketman::Rocketman( World *_world, Vector2d *_position ) : Actor( _world, CLASS_ID, new AnimatedSprite( spr() ), _position )
{
}

Rocketman::~Rocketman()
{
    //dtor
}

void Rocketman::render( SDL_Window *window )
{
    Actor::render( window );
}

void Rocketman::update( SDL_Window *window, double delta )
{
    Actor::update( window, delta );
}

AnimatedSprite &Rocketman::spr()
{
    static AnimatedSprite *spr = new AnimatedSprite( Utils::concat( Constants::SPRITE_DIR, "class/SoldierStrip.png" ), 500, 2, 3, true, 64, 64, 32, 32 );
    return *spr;
}
