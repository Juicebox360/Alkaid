/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. Also, your mom
 * probably writes better code than this.
 *
 *
 * Sprite.cpp: Defined functions for the Sprite class
 */

#include "SDL_image.h"

#include "gfx/Sprite.h"
#include "util/Colour.h"

Sprite::Sprite()
{
    init( NULL, 0, 0, 0, 0 );
    visible = false;
}
Sprite::Sprite( SDL_Surface *image, int spriteWidth, int spriteHeight, double spriteCentreX, double spriteCentreY )
{
    init( image, spriteWidth, spriteHeight, spriteCentreX, spriteCentreY );
}
Sprite::Sprite( std::string filename, int spriteWidth, int spriteHeight, double spriteCentreX, double spriteCentreY )
{
    init( loadImage( filename ), spriteWidth, spriteHeight, spriteCentreX, spriteCentreY );
}

Sprite::~Sprite()
{
    glDeleteTextures( 1, &texture );
}

void Sprite::init( SDL_Surface *image, int spriteWidth, int spriteHeight, double spriteCentreX, double spriteCentreY )
{
    if ( !image )
    {
        printf( "Notice: Image was designated as null; not initialising.\n" );
        return;
    }
    printf( "Starting sprite initialisation.\n" );

    if ( (image->w & (image->w - 1)) != 0 )
    {
        printf( "Notice: An image's width is %i (not a power of 2).\n", image->w );
    }
    if ( (image->h & (image->h - 1)) != 0 )
    {
        printf( "Notice: An image's height is %i (not a power of 2).\n", image->h );
    }

    if ( spriteWidth != 0 )
    {
        sizeX = spriteWidth;
    }
    else
    {
        sizeX = image->w;
    }
    if ( spriteHeight != 0 )
    {
        sizeY = spriteHeight;
    }
    else
    {
        sizeY = image->h;
    }
    centreX = spriteCentreX;
    centreY = spriteCentreY;

    countX = (image->w / sizeX);
    countY = (image->h / sizeY);

    colourFormat = image->format->BytesPerPixel;
    // Alpha channel check
    if ( colourFormat == 4 )
    {
        if ( image->format->Rmask == 0x000000ff )
        {
            textureFormat = GL_RGBA;
        }
        else
        {
            textureFormat = GL_BGRA;
        }
    }
    else if ( colourFormat == 3 )
    {
        if ( image->format->Rmask == 0x000000ff )
        {
            textureFormat = GL_RGB;
        }
        else
        {
            textureFormat = GL_BGR;
        }
    }
    else
    {
        printf( "Warning! An image's colourdata is not truecolour (%i).\n", colourFormat );
    }

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, colourFormat, image->w, image->h, 0, textureFormat, GL_UNSIGNED_BYTE, image->pixels );

    if ( image )
    {
        SDL_FreeSurface( image );
    }
    printf( "Finishing sprite initialisation.\n" );
}

void Sprite::handleImageError( int errorStatus )
{
    printf( "Sprite Error Code %i\nDetails: %s\n", errorStatus, IMG_GetError() );
    exit( EXIT_FAILURE );
}

SDL_Surface *Sprite::loadImage( std::string filename )
{
    SDL_Surface *destSurf;
    if ( filename.empty() )
    {
        handleImageError( 0 );
    }
    destSurf = IMG_Load( filename.c_str() );
    if ( !destSurf )
    {
        handleImageError( 1 );
    }

    printf( "The dimensions of the image are %i x %i\n", destSurf->w, destSurf->h );
    return destSurf;
}

int Sprite::getCount() const
{
    return countX * countY;
}

int Sprite::getHorizontalCount() const
{
    return countX;
}

int Sprite::getVerticalCount() const
{
    return countY;
}

int Sprite::getWidth() const
{
    return sizeX;
}

int Sprite::getHeight() const
{
    return sizeY;
}

double Sprite::getCentreX() const
{
    return centreX;
}

double Sprite::getCentreY() const
{
    return centreY;
}

bool Sprite::isVisible() const
{
    return visible;
}

void Sprite::setCentreX( double nCX )
{
    centreX = nCX;
}

void Sprite::setCentreY( double nCY )
{
    centreY = nCY;
}

void Sprite::setVisible( bool visibility )
{
    visible = visibility;
}

void Sprite::toggleVisible()
{
    visible = !visible;
}

void Sprite::render( SDL_Surface *screen, double x, double y, int index, double xScale, double yScale, Colour *colour, double theta )
{
    Vector2f *coords = indexToCoord( index );
    //printf( "Coords: (%f, %f)\n", coords->getX(), coords->getY() );
    render( screen, x, y, coords->getX(), coords->getY(), xScale, yScale, colour, theta );
    delete coords;
}
void Sprite::render( SDL_Surface *screen, double x, double y, int xIndex, int yIndex, double xScale, double yScale, Colour *colour, double theta )
{
    if ( !visible )
    {
        return;
    }

    glTranslatef( x, y, 0.0 );
    glRotatef( theta, 0.0, 0.0, 1.0 );

    glBindTexture( GL_TEXTURE_2D, texture );
    //glColorMask( true, true, true, true );
    glColor4ub( colour->getRedI(), colour->getGreenI(), colour->getBlueI(), colour->getAlphaI() );

    glEnable( GL_TEXTURE_2D );

    // xDiv & yDiv should probably be pre-calculated since they are constant
    double xDiv = 1.0d / countX;
    double xStart = xIndex * xDiv;
    double xEnd = (1 + xIndex) * xDiv;

    double yDiv = 1.0d / countY;
    double yStart = yIndex * yDiv;
    double yEnd = (1 + yIndex) * yDiv;

    //printf( "xDiv: %f\nxStart: %f\nxEnd: %f\n\nyDiv: %f\nyStart: %f\nyEnd: %f\n----------------------------\n", xDiv, xStart, xEnd, yDiv, yStart, yEnd );

    glBegin( GL_QUADS );
    glTexCoord2d( xStart, yStart );
    glVertex3f( -centreX, -centreY, 0 );
    glTexCoord2d( xEnd, yStart );
    glVertex3f( -centreX + sizeX * xScale, -centreY, 0 );
    glTexCoord2d( xEnd, yEnd );
    glVertex3f( -centreX + sizeX * xScale, -centreY + sizeY * yScale, 0 );
    glTexCoord2d( xStart, yEnd );
    glVertex3f( -centreX, -centreY + sizeY * yScale, 0 );
    glEnd();

    glDisable( GL_TEXTURE_2D );
    glColor4ub( 255, 255, 255, 255 );

    // Debug origin
    glPointSize( 2.0f );
    glBegin( GL_POINTS );
    glVertex2i( 0, 0 );
    glEnd();

    glLoadIdentity();
}

void Sprite::update( SDL_Surface *screen, int delta )
{
}

Vector2f *Sprite::indexToCoord( int i )
{
    Vector2f *retVal = new Vector2f( 0, 0 );
    if ( i <= 0 )
    {
        retVal->setX( 0 );
        retVal->setY( 0 );
    }
    else if ( i >= countX * countY )
    {
        retVal->setX( countX );
        retVal->setY( countY );
    }
    else
    {
        retVal->setX( i % countX );
        retVal->setY( int( i / countX ) );
    }

    return retVal;
}

int Sprite::coordToIndex( Vector2f &coord )
{
    return coordToIndex( int( coord.getX() ), int( coord.getY() ) );
}
int Sprite::coordToIndex( int x, int y )
{
    return y * countX + x;
}
