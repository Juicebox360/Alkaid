#include "sys/Supervisor.h"

using namespace std;

Supervisor::Supervisor()
{
    //ctor
}

Entity* Supervisor::instance_create(Entity* spawned_entity)
{
    instance_list.push_back(spawned_entity);
    return spawned_entity; // return the pointer that was given; for functional purposes
}

bool Supervisor::instance_kill(Entity* spawned_entity)
{
    long entity_index = instance_get_index(spawned_entity);
    if( entity_index != -1 ) // entity pointer exists in entity table
    {
        instance_list.erase(instance_list.begin()+entity_index);
        delete spawned_entity;
        return 0;
    }
    else
    {
        cout << "Bad entity ptr... Supervisor::instance_kill " << spawned_entity;
        return 1;
    }
}

long Supervisor::instance_get_index(Entity* spawned_entity)
{
    for (long i = 0; i < instance_list.size(); i++)
    {
        if (instance_list[i] == spawned_entity)
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
