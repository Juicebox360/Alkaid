#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>

#include "util/Colour.h"
#include "gfx/fnt/Font.h"

Font::Font( TTF_Font *_font )
{
    font = _font;
}

Font::~Font()
{
    TTF_CloseFont( font );
}

void Font::draw_text_shaded( std::string text, double x, double y, double hover_spacing, Colour &foregroundColour, Colour &backgroundColour )
{
    SDL_Surface *textSurface;

    if ( !(textSurface = TTF_RenderUTF8_Blended( font, text.c_str(), {255, 255, 255} ) ) )
    {
        handle_ttf_error();
    }

    int w = textSurface->w, h = textSurface->h;

    GLuint texture;
    text_process( &texture, textSurface );

    glTranslatef( x + hover_spacing, y + hover_spacing, 0.0 );

    glBindTexture( GL_TEXTURE_2D, texture );
    glColor4ub( backgroundColour.get_red_int(), backgroundColour.get_green_int(), backgroundColour.get_blue_int(), backgroundColour.get_alpha_int() );
    glEnable( GL_TEXTURE_2D );

    glBegin( GL_QUADS );
    glTexCoord2i( 0, 0 );
    glVertex3f( 0, 0, 0 );
    glTexCoord2i( 1, 0 );
    glVertex3f( w, 0, 0 );
    glTexCoord2i( 1, 1 );
    glVertex3f( w, h, 0 );
    glTexCoord2i( 0, 1 );
    glVertex3f( 0, h, 0 );
    glEnd();

    glDisable( GL_TEXTURE_2D );
    glLoadIdentity();

    //glClear( GL_COLOR_BUFFER_BIT );
    glTranslatef( x, y, 0.0 );

    glBindTexture( GL_TEXTURE_2D, texture );
    glColor4ub( foregroundColour.get_red_int(), foregroundColour.get_green_int(), foregroundColour.get_blue_int(), foregroundColour.get_alpha_int() );
    glEnable( GL_TEXTURE_2D );

    glBegin( GL_QUADS );
    glTexCoord2i( 0, 0 );
    glVertex3f( 0, 0, 0 );
    glTexCoord2i( 1, 0 );
    glVertex3f( w, 0, 0 );
    glTexCoord2i( 1, 1 );
    glVertex3f( w, h, 0 );
    glTexCoord2i( 0, 1 );
    glVertex3f( 0, h, 0 );
    glEnd();

    glDisable( GL_TEXTURE_2D );
    glColor4ub( 255, 255, 255, 255 );
    glLoadIdentity();

    glDeleteTextures( 1, &texture );
}
void Font::draw_text_shaded( std::string *text, double x, double y, double hover_spacing, Colour &foregroundColour, Colour &backgroundColour )
{
    draw_text_shaded( text, x, y, hover_spacing, foregroundColour, backgroundColour );
}
void Font::draw_text_shaded( const char *text, double x, double y, double hover_spacing, Colour &foregroundColour, Colour &backgroundColour )
{
    std::string temp = std::string( text );
    draw_text_shaded( temp, x, y, hover_spacing, foregroundColour, backgroundColour );
}

void Font::handle_ttf_error()
{
    printf( "Font: %s\n", TTF_GetError() );
    exit( EXIT_FAILURE );
}

void Font::text_process( GLuint *dest_surf, SDL_Surface *text )
{
    GLenum texture_format;
    GLint colour_format = text->format->BytesPerPixel;

    // Alpha channel check
    if ( colour_format == 4 )
    {
        if ( text->format->Rmask == 0x000000ff )
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
        if ( text->format->Rmask == 0x000000ff )
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
        printf( "Warning! A text's colourdata is not truecolour." );
    }

    glGenTextures( 1, dest_surf );
    glBindTexture( GL_TEXTURE_2D, *dest_surf );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, colour_format, text->w, text->h, 0, texture_format, GL_UNSIGNED_BYTE, text->pixels );

    if ( text )
    {
        SDL_FreeSurface( text );
    }
}
