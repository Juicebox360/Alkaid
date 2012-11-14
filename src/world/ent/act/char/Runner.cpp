#include "SDL.h"

#include "util/Utils.h"
#include "util/Constants.h"
#include "world/ent/act/Actor.h"
#include "world/ent/act/char/Runner.h"
#include "gfx/spr/AnimatedSprite.h"

Runner::Runner( World *_world, Vector2d *_position ) : Actor( _world, CLASS_ID, new AnimatedSprite( spr() ), _position )
{
}

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

AnimatedSprite &Runner::spr()
{
    static AnimatedSprite *spr = new AnimatedSprite( Utils::concat( Constants::SPRITE_DIR, "class/ScoutStrip.png" ), 300, 2, 3, true, 64, 64, 32, 32 );
    return *spr;
}
