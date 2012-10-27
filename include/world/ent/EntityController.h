#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include <SDL.h>

#include "world/ent/Entity.h"
#include "world/ent/EntityEnums.h"
#include "world/World.h"
#include "util/Vector2d.h"
#include "util/ObjectFactory.h"

// EntityController is a proxy-factory between typical game ops and the current World.
class World;
class Entity;

class EntityController
{
    public:
        static void pre_init();
        EntityController();
        virtual ~EntityController();
        long generate_next_unique_id();
        long get_current_unique_id();
        //template <typename UniqueIdType>
        //Entity *entity_create( UniqueIdType entity_typename, World *world, Vector2d *location );
        Entity *entity_create( int entity_typename, World *world, Vector2d *location );
        bool entity_remove( Entity *entity );
        bool entity_remove( long unique_id );
        bool entity_kill( Entity *entity );
        bool entity_kill( long unique_id );
        bool entity_exists( Entity *entity );
        bool entity_exists( long unique_id );
        Entity *entity_get( long unique_id );
        std::map<long, Entity*> *entity_list();
        void reset();
        void render( SDL_Surface *screen );
        void update( SDL_Surface *screen, double delta );
    protected:
    private:
        long curr_unique_id = 0;
        std::map<long, Entity*> entities;
        static ObjectFactory<Entity *(World*, Vector2d*), int> entity_factory;
};

#endif // ENTITYCONTROLLER_H
