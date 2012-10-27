#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>

#include "world/ent/EntityController.h"

class EntityController;

class World
{
    public:
        World();
        virtual ~World();

        EntityController *get_entity_controller();

        virtual void render( SDL_Surface *screen );
        virtual void update( SDL_Surface *screen, double delta );
    protected:
    private:
        EntityController *entities;
};

#endif // WORLD_H
