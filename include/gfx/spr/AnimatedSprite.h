#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <string>

#include "SDL.h"
#include "gfx/spr/Sprite.h"
#include "util/Colour.h"

class AnimatedSprite : public Sprite
{
    public:
        AnimatedSprite( const AnimatedSprite &animated_sprite );
        AnimatedSprite( const Sprite &sprite, double _rate = 0, int _start_index = 0, int _end_index = -1, bool _repeat = true );
        AnimatedSprite( SDL_Surface *image, double _rate = 0, int _start_index = 0, int _end_index = -1, bool _repeat = true, int sprite_width = 0, int sprite_height = 0, double sprite_centre_x = 0, double sprite_centre_y = 0 );
        AnimatedSprite( std::string filename, double _rate = 0, int _start_index = 0, int _end_index = -1, bool _repeat = true, int sprite_width = 0, int sprite_height = 0, double sprite_centre_x = 0, double sprite_centre_y = 0 );
        virtual ~AnimatedSprite();

        AnimatedSprite &operator=( const AnimatedSprite &other );

        void set_rate( double _rate );
        void set_start_index( int index );
        void set_end_index( int index );
        void set_index( int index );
        void set_repeat( bool _repeat );
        void toggle_repeat();

        virtual void update( SDL_Surface *screen, double delta );
        virtual void render( SDL_Surface *screen, double x, double y, int index, double x_scale = 1, double y_scale = 1, Colour *colour = &Colour::WHITE, double theta = 0 );

        int start_index, end_index, anim_index;
        double rate, time_accumulated;
        bool repeat;
    protected:
    private:
        void init( double _rate, int _start_index, int _end_index, bool _repeat );
        void set_index_value( int &value_loc, int value );
};

#endif // ANIMATEDSPRITE_H
