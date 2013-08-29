#include <SDL2/SDL.h>

#include "util/Utils.h"
#include "util/Constants.h"
#include "world/ent/act/Actor.h"
#include "world/ent/act/char/Healer.h"
#include "gfx/spr/AnimatedSprite.h"

Healer::Healer( World *_world, Vector2d *_position ) : Actor( _world, CLASS_ID, new AnimatedSprite( spr() ), _position )
{
}

Healer::~Healer()
{
    //dtor
}

void Healer::render( SDL_Window *window )
{
    Actor::render( window );
}

void Healer::update( SDL_Window *window, double delta )
{
    Actor::update( window, delta );
}

AnimatedSprite &Healer::spr()
{
    static AnimatedSprite *spr = new AnimatedSprite( Utils::concat( Constants::SPRITE_DIR, "class/MedicStrip.png" ), 400, 2, 3, true, 64, 64, 32, 32 );
    return *spr;
}
