#ifndef ENTITY_H
#define ENTITY_H

#include "ent/EntityController.h"
#include "gfx/Sprite.h"
#include "util/Vector2d.h"

class EntityController;

class Entity
{
    public:
        Entity( EntityController *_entityControl, int _classID, Sprite *_sprite = NULL, Vector2d *_position = NULL, Vector2d *_velocity = NULL, Vector2d *_acceleration = NULL );
        virtual ~Entity();

        // I DID THESE UNDER DURESS
        // ...sort of
        EntityController *entityControl;
        Vector2d *position, *velocity, *acceleration;
        Sprite *sprite;
        int uniqueID, classID;
    protected:
    private:
        void init( EntityController *_entityControl, int _classID, Sprite *_sprite, Vector2d *_position, Vector2d *_velocity, Vector2d *_acceleration );
        virtual void render( SDL_Surface *screen, double x, double y, int index = 0, double xScale = 1, double yScale = 1, Colour *colour = &Colour::WHITE, double theta = 0 );
        void update( SDL_Surface *screen, int delta );
};

#endif // ENTITY_H
