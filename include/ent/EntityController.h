#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include <SDL.h>

#include "ent/Entity.h"

// EntityController is a proxy between typical game ops and the current World.
class Entity;

class EntityController
{
    public:
        EntityController();
        virtual ~EntityController();
        int generateNextUniqueID();
        bool addEntityToWorld( Entity *entity );
        bool removeEntityFromWorld( Entity *entity );
        bool removeEntityFromWorld( int uniqueID );
        bool entityIsInWorld( Entity *entity );
        bool entityIsInWorld( int uniqueID );

        void render( SDL_Surface *screen );
        void update( SDL_Surface *screen, int delta );

        int currUniqueID;
        //World *world;
    protected:
    private:
};

#endif // ENTITYCONTROLLER_H
