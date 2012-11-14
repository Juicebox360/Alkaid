#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>

#include "world/ent/Supervisor.h"

class Supervisor;

class World
{
    public:
        World();
        virtual ~World();

        Supervisor *get_entity_supervisor();

        virtual void render( SDL_Surface *screen );
        virtual void update( SDL_Surface *screen, double delta );

        Supervisor *entities;
    protected:
    private:
};

#endif // WORLD_H
