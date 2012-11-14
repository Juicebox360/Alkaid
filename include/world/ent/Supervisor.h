#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <boost/ptr_container/ptr_vector.hpp>

#include <SDL.h>

#include "world/ent/Entity.h"
#include "world/ent/EntityEnums.h"
#include "world/World.h"
#include "util/Vector2d.h"
#include "util/ObjectFactory.h"

// Supervisor is a proxy-factory between typical game ops and the current World.
class Entity;
class World;

class Supervisor
{
    public:
        static void pre_init();
        Supervisor();
        virtual ~Supervisor();
        //template <typename UniqueIdType>
        //Entity *entity_create( UniqueIdType entity_typename, World *world, Vector2d *location );
        Entity *entity_create( int entity_typename, World *world, Vector2d *location );
        bool entity_remove( Entity *entity );
        bool entity_kill( Entity *entity );
        bool entity_exists( Entity *entity );
        boost::ptr_vector<Entity> *entity_list();
        int entity_count();
        void reset();
        void render( SDL_Surface *screen );
        void update( SDL_Surface *screen, double delta );
    protected:
    private:
        boost::ptr_vector<Entity>::iterator get_entity_index( Entity *entity );

        struct CheckPointerValue
        {
             CheckPointerValue( Entity* entity ):anEntity( entity ) {}
             bool operator()( Entity const& ent ) { return &ent == anEntity; }
             private:
                Entity* anEntity;
        };

        boost::ptr_vector<Entity> entities;
        static ObjectFactory<Entity* (World*, Vector2d*), int> entity_factory;
};

#endif // SUPERVISOR_H
