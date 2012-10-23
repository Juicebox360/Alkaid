#include "Supervisor.h"

Supervisor::Supervisor()
{
    //ctor
}

Entity* Supervisor::instance_create(Entity* spawned_entity)
{
    entity_list.push_back(spawned_entity);
    return spawned_entity; // return the pointer that was given; for functional purposes
}

bool Supervisor::instance_kill(Entity* spawned_entity)
{
    Entity* entity_index = instance_get_index(spawned_entity)
    if( entity_index != -1 ) // entity pointer exists in entity table
    {
        entity_list.erase(entity_index);
        delete spawned_entity;
        return 0;
    }
    else
    {
        virtual const char* what() const throw()
        {
            return "Exception in Supervisor::instance_kill; invalid Entity pointer";
        }
        return 1;
    }
}

long Supervisor::instance_get_index(Entity* spawned_entity)
{
    for (long i = 0; i < entity_list.size(); i++)
    {
        if (entity_list[i] == spawned_entity)
        {
            return i;
        }
    }
    return -1;
}

Supervisor::~Supervisor()
{
    //dtor
}
