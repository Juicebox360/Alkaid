#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>

#include "world/ent/Supervisor.h"

class Supervisor;

class World
{
    public:
        World();
        virtual ~World();

        Supervisor *get_entity_supervisor();

        virtual void render( SDL_Window *window );
        virtual void update( SDL_Window *window, double delta );

        Supervisor *entities;
    protected:
    private:
};

#endif // WORLD_H
