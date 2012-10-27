#include "SDL.h"

#include "world/ent/act/Actor.h"

Actor::~Actor()
{
    //dtor
}

void Actor::render( SDL_Surface *screen )
{
    Entity::render( screen );
}

void Actor::update( SDL_Surface *screen, double delta )
{
    Entity::update( screen, delta );
}
