#ifndef SUPERVISOR_H
#define SUPERVISOR_H


class Supervisor
{
    public:
        Supervisor();
        virtual ~Supervisor();
        Entity* instance_create(Entity*);
        bool instance_kill(Entity*);
    protected:
    private:
        long instance_get_index(Entity*);
        vector<Entity*> instance_list;
};

#endif // SUPERVISOR_H
