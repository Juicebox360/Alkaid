#include <SDL2/SDL.h>

#include "world/ent/act/Actor.h"

Actor::~Actor()
{
    //dtor
}

void Actor::render( SDL_Window *window )
{
    Entity::render( window );
}

void Actor::update( SDL_Window *window, double delta )
{
    Entity::update( window, delta );
}
