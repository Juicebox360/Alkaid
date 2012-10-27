#include <math.h>

#include "util/Colour.h"

Colour Colour::WHITE( 255, 255, 255, 255 );
Colour Colour::BLACK( 0, 0, 0, 255 );
Colour Colour::RED( 255, 0, 0, 255 );
Colour Colour::GREEN( 0, 255, 0, 255 );
Colour Colour::BLUE( 0, 0, 255, 255 );

Colour::Colour( int _r, int _g, int _b, int _a )
{
    init( _r / 255.0d, _g / 255.0d, _b / 255.0d, _a / 255.0d );
}
Colour::Colour( double _r, double _g, double _b, double _a )
{
    init( _r, _g, _b, _a );
}

Colour::~Colour()
{
    //dtor
}

void Colour::init( double _r, double _g, double _b, double _a )
{
    set_red( _r );
    set_green( _g );
    set_blue( _b );
    set_alpha( _a );
}

double Colour::get_red_double() const
{
    return r;
}

double Colour::get_green_double() const
{
    return g;
}

double Colour::get_blue_double() const
{
    return b;
}

double Colour::get_alpha_double() const
{
    return a;
}

int Colour::get_red_int() const
{
    return int( ceil( r * 255 ) );
}

int Colour::get_green_int() const
{
    return int( ceil( g * 255 ) );
}

int Colour::get_blue_int() const
{
    return int( ceil( b * 255 ) );
}

int Colour::get_alpha_int() const
{
    return int( ceil( a * 255 ) );
}

void Colour::set_red( double _r )
{
    set_colour_value( r, _r );
}
void Colour::set_red( int _r )
{
    set_red( _r / 255.0f );
}

void Colour::set_green( double _g )
{
    set_colour_value( g, _g );
}
void Colour::set_green( int _g )
{
    set_green( _g / 255.0f );
}

void Colour::set_blue( double _b )
{
    set_colour_value( b, _b );
}
void Colour::set_blue( int _b )
{
    set_blue( _b / 255.0f );
}

void Colour::set_alpha( double _a )
{
    set_colour_value( a, _a );
}
void Colour::set_alpha( int _a )
{
    set_alpha( _a / 255.0f );
}

void Colour::add_red( double _r )
{
    set_colour_value( r, r + _r );
}
void Colour::add_red( int _r )
{
    add_red( _r / 255.0f );
}

void Colour::add_green( double _g )
{
    set_colour_value( g, g + _g );
}
void Colour::add_green( int _g )
{
    add_green( _g / 255.0f );
}

void Colour::add_blue( double _b )
{
    set_colour_value( b, b + _b );
}
void Colour::add_blue( int _b )
{
    add_blue( _b / 255.0f );
}

void Colour::add_alpha( double _a )
{
    set_colour_value( a, a + _a );
}
void Colour::add_alpha( int _a )
{
    add_alpha( _a / 255.0f );
}

SDL_Color Colour::engine_format() const
{
    return SDL_Color {int( ceil( r * 255 ) ), int( ceil( g * 255 ) ), int( ceil( b * 255 ) )};
}

void Colour::set_colour_value( double &value_loc, double value )
{
    if ( value <= 0.0d )
    {
        value_loc = 0.0d;
    }
    else if ( value >= 1.0d )
    {
        value_loc = 1.0d;
    }
    else
    {
        value_loc = value;
    }
}
