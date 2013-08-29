/*
 * Sprite.cpp: Defined functions for the Sprite class
 */

#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "gfx/spr/Sprite.h"
#include "util/Colour.h"

#include "util/Utils.h"

Sprite::Sprite()
{
    init( NULL, 0, 0, 0, 0 );
    visible = false;
}
Sprite::Sprite( const Sprite &sprite )
{
    texture = sprite.texture;
    texture_format = sprite.texture_format;
    colour_format = sprite.colour_format;
    count_x = sprite.count_x;
    count_y = sprite.count_y;
    w = sprite.w;
    h = sprite.h;
    centre_x = sprite.centre_x;
    centre_y = sprite.centre_y;
    visible = sprite.visible;
}
Sprite::Sprite( SDL_Surface *image, int sprite_width, int sprite_height, double sprite_centre_x, double sprite_centre_y )
{
    init( image, sprite_width, sprite_height, sprite_centre_x, sprite_centre_y );
}
Sprite::Sprite( std::string filename, int sprite_width, int sprite_height, double sprite_centre_x, double sprite_centre_y )
{
    init( load_image( filename ), sprite_width, sprite_height, sprite_centre_x, sprite_centre_y );
}

Sprite::~Sprite()
{
    glDeleteTextures( 1, &texture );
}

Sprite &Sprite::operator=( const Sprite &other )
{
    if ( this != &other )
    {
        texture = other.texture;
        //printf( Utils::concat( "Old texture value: ", sprite->texture, "\nOld texture address: ", &(sprite->texture), "\nNew texture value: ", texture, "\nNew texture address: ", &texture, "\n" ).c_str() );
        texture_format = other.texture_format;
        colour_format = other.colour_format;
        count_x = other.count_x;
        count_y = other.count_y;
        w = other.w;
        h = other.h;
        centre_x = other.centre_x;
        centre_y = other.centre_y;
        visible = other.visible;
    }
    return *this;
}

void Sprite::init( SDL_Surface *image, int sprite_width, int sprite_height, double sprite_centre_x, double sprite_centre_y )
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

    if ( sprite_width != 0 )
    {
        w = sprite_width;
    }
    else
    {
        w = image->w;
    }
    if ( sprite_height != 0 )
    {
        h = sprite_height;
    }
    else
    {
        h = image->h;
    }
    centre_x = sprite_centre_x;
    centre_y = sprite_centre_y;

    count_x = (image->w / w);
    count_y = (image->h / h);

    colour_format = image->format->BytesPerPixel;
    // Alpha channel check
    if ( colour_format == 4 )
    {
        if ( image->format->Rmask == 0x000000ff )
        {
            texture_format = GL_RGBA;
        }
        else
        {
            texture_format = GL_BGRA;
        }
    }
    else if ( colour_format == 3 )
    {
        if ( image->format->Rmask == 0x000000ff )
        {
            texture_format = GL_RGB;
        }
        else
        {
            texture_format = GL_BGR;
        }
    }
    else
    {
        printf( "Warning! An image's colourdata is not truecolour (%i).\n", colour_format );
    }

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, colour_format, image->w, image->h, 0, texture_format, GL_UNSIGNED_BYTE, image->pixels );

    if ( image )
    {
        SDL_FreeSurface( image );
    }
    printf( "Finishing sprite initialisation.\n" );
}

void Sprite::handle_image_error( int error_code )
{
    printf( "Sprite Error Code %i\nDetails: %s\n", error_code, IMG_GetError() );
    exit( EXIT_FAILURE );
}

SDL_Surface *Sprite::load_image( std::string filename )
{
    SDL_Surface *dest_surf;
    if ( filename.empty() )
    {
        handle_image_error( 0 );
    }
    dest_surf = IMG_Load( filename.c_str() );
    if ( !dest_surf )
    {
        handle_image_error( 1 );
    }

    //printf( "The dimensions of the image are %i x %i\n", dest_surf->w, dest_surf->h );
    return dest_surf;
}

int Sprite::get_count() const
{
    return count_x * count_y;
}

void Sprite::set_centre_x( double sprite_centre_x )
{
    centre_x = sprite_centre_x;
}

void Sprite::set_centre_y( double sprite_centre_y )
{
    centre_y = sprite_centre_y;
}

void Sprite::set_visible( bool visibility )
{
    visible = visibility;
}

void Sprite::toggle_visible()
{
    visible = !visible;
}

void Sprite::render( SDL_Window *window, double x, double y, int index, double x_scale, double y_scale, Colour *colour, double theta )
{
    if ( !visible )
    {
        return;
    }

    Vector2d *coords = index_to_coord( index );
    //printf( "Coords: (%f, %f)\n", coords->getX(), coords->getY() );
    render( window, x, y, coords->x, coords->y, x_scale, y_scale, colour, theta );
    delete coords;
}
void Sprite::render( SDL_Window *window, double x, double y, int x_index, int y_index, double x_scale, double y_scale, Colour *colour, double theta )
{
    if ( !visible )
    {
        return;
    }

    glTranslatef( x, y, 0.0 );
    glRotatef( theta, 0.0, 0.0, 1.0 );

    glBindTexture( GL_TEXTURE_2D, texture );
    //glColorMask( true, true, true, true );
    glColor4ub( colour->get_red_int(), colour->get_green_int(), colour->get_blue_int(), colour->get_alpha_int() );

    glEnable( GL_TEXTURE_2D );

    // x_div & y_div should probably be pre-calculated since they are constant
    double x_div = 1.0d / count_x;
    double x_start = x_index * x_div;
    double x_end = (1 + x_index) * x_div;

    double y_div = 1.0d / count_y;
    double y_start = y_index * y_div;
    double y_end = (1 + y_index) * y_div;

    glBegin( GL_QUADS );
    glTexCoord2d( x_start, y_start );
    glVertex3f( -centre_x, -centre_y, 0 );
    glTexCoord2d( x_end, y_start );
    glVertex3f( -centre_x + w * x_scale, -centre_y, 0 );
    glTexCoord2d( x_end, y_end );
    glVertex3f( -centre_x + w * x_scale, -centre_y + h * y_scale, 0 );
    glTexCoord2d( x_start, y_end );
    glVertex3f( -centre_x, -centre_y + h * y_scale, 0 );
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

void Sprite::update( SDL_Window *window, double delta )
{
}

Vector2d *Sprite::index_to_coord( int i )
{
    Vector2d *vec = new Vector2d( 0, 0 );
    if ( i <= 0 )
    {
        vec->x = 0;
        vec->y = 0;
    }
    else if ( i >= count_x * count_y )
    {
        vec->x = count_x;
        vec->y = count_y;
    }
    else
    {
        vec->x = i % count_x;
        vec->y = int( i / count_x );
    }

    return vec;
}

int Sprite::coord_to_index( Vector2d &coord )
{
    return coord_to_index( int( coord.x ), int( coord.y ) );
}
int Sprite::coord_to_index( int x, int y )
{
    return y * count_x + x;
}
