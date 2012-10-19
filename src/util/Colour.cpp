#include "util/Colour.h"
#include <math.h>

Colour Colour::WHITE( 255, 255, 255, 255 );
Colour Colour::BLACK( 0, 0, 0, 255 );
Colour Colour::RED( 255, 0, 0, 255 );
Colour Colour::GREEN( 0, 255, 0, 255 );
Colour Colour::BLUE( 0, 0, 255, 255 );

Colour::Colour( int _r, int _g, int _b, int _a )
{
    init( _r / 255.0f, _g / 255.0f, _b / 255.0f, _a / 255.0f );
}
Colour::Colour( float _r, float _g, float _b, float _a )
{
    init( _r, _g, _b, _a );
}

Colour::~Colour()
{
    //dtor
}

void Colour::init( float _r, float _g, float _b, float _a )
{
    setRed( _r );
    setGreen( _g );
    setBlue( _b );
    setAlpha( _a );
}

float Colour::getRedF() const
{
    return r;
}

float Colour::getGreenF() const
{
    return g;
}

float Colour::getBlueF() const
{
    return b;
}

float Colour::getAlphaF() const
{
    return a;
}

int Colour::getRedI() const
{
    return int( ceil( r * 255 ) );
}

int Colour::getGreenI() const
{
    return int( ceil( g * 255 ) );
}

int Colour::getBlueI() const
{
    return int( ceil( b * 255 ) );
}

int Colour::getAlphaI() const
{
    return int( ceil( a * 255 ) );
}

void Colour::setRed( float _r )
{
    setColourValue( r, _r );
}
void Colour::setRed( int _r )
{
    setRed( _r / 255.0f );
}

void Colour::setGreen( float _g )
{
    setColourValue( g, _g );
}
void Colour::setGreen( int _g )
{
    setGreen( _g / 255.0f );
}

void Colour::setBlue( float _b )
{
    setColourValue( b, _b );
}
void Colour::setBlue( int _b )
{
    setBlue( _b / 255.0f );
}

void Colour::setAlpha( float _a )
{
    setColourValue( a, _a );
}
void Colour::setAlpha( int _a )
{
    setAlpha( _a / 255.0f );
}

void Colour::addRed( float _r )
{
    setColourValue( r, r + _r );
}
void Colour::addRed( int _r )
{
    addRed( _r / 255.0f );
}

void Colour::addGreen( float _g )
{
    setColourValue( g, g + _g );
}
void Colour::addGreen( int _g )
{
    addGreen( _g / 255.0f );
}

void Colour::addBlue( float _b )
{
    setColourValue( b, b + _b );
}
void Colour::addBlue( int _b )
{
    addBlue( _b / 255.0f );
}

void Colour::addAlpha( float _a )
{
    setColourValue( a, a + _a );
}
void Colour::addAlpha( int _a )
{
    addAlpha( _a / 255.0f );
}

SDL_Color Colour::toEngineFormat() const
{
    return SDL_Color {int( ceil( r * 255 ) ), int( ceil( g * 255 ) ), int( ceil( b * 255 ) )};
}

void Colour::setColourValue( float &valueLoc, float value )
{
    if ( value <= 0.0f )
    {
        valueLoc = 0.0f;
    }
    else if ( value >= 1.0f )
    {
        valueLoc = 1.0f;
    }
    else
    {
        valueLoc = value;
    }
}
