#include "gfx/spr/AnimatedSprite.h"
#include "util/Utils.h"

// TODO: Backward animation. Utilising the same texture sheet for different animation indices

AnimatedSprite::~AnimatedSprite()
{
    //dtor
}

void AnimatedSprite::init( double _rate, int _start_index, int _end_index, bool _repeat )
{
    set_rate( _rate );
    set_start_index( _start_index );
    set_end_index( _end_index );
    set_repeat( _repeat );
}

void AnimatedSprite::set_rate( double _rate )
{
    if ( _rate < 0 )
    {
        rate = 0;
    }
    else
    {
        rate = _rate;
    }
}

void AnimatedSprite::set_start_index( int index )
{
    set_index_value( start_index, index );
}

void AnimatedSprite::set_end_index( int index )
{
    set_index_value( end_index, index );
}

void AnimatedSprite::set_index( int index )
{
    set_index_value( anim_index, index );
}

void AnimatedSprite::set_repeat( bool _repeat )
{
    repeat = _repeat;
}

void AnimatedSprite::toggle_repeat()
{
    repeat = !repeat;
}

void AnimatedSprite::update( SDL_Surface *screen, double delta )
{
    Sprite::update( screen, delta );

    time_accumulated += delta;
    if ( time_accumulated >= rate )
    {
        if ( anim_index + 1 <= end_index )
        {
            anim_index++;
        }
        else
        {
            if ( repeat )
            {
                anim_index = start_index;
            }
        }
        time_accumulated = 0;
    }
    //printf( Utils::concat( start_index, " <- ", anim_index, " -> ", end_index, "\n" ).c_str() );
    //printf( "t: %f; dt: %f\n", time_accumulated, delta );
}

void AnimatedSprite::render( SDL_Surface *screen, double x, double y, int index, double x_scale, double y_scale, Colour *colour, double theta )
{
    Sprite::render( screen, x, y, (index < 0 ? anim_index : index), x_scale, y_scale, colour, theta );
}

void AnimatedSprite::set_index_value( int &value_loc, int value )
{
    if ( value < 0 || value >= get_count() )
    {
        value_loc = get_count() - 1;
    }
    else
    {
        value_loc = value;
    }
}
