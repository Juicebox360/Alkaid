#ifndef FONT_H
#define FONT_H

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

#include "util/Colour.h"

class Font
{
    public:
        Font( TTF_Font *_font );
        virtual ~Font();
        void draw_text_shaded( std::string text, double x, double y, double hover_spacing, Colour &foregroundColour, Colour &backgroundColour );
        void draw_text_shaded( std::string *text, double x, double y, double hover_spacing, Colour &foregroundColour, Colour &backgroundColour );
        void draw_text_shaded( const char *text, double x, double y, double hover_spacing, Colour &foregroundColour, Colour &backgroundColour );

        TTF_Font *font;
    protected:
    private:
        void text_process( GLuint *dest_surf, SDL_Surface *text );
        void handle_ttf_error();

};

#endif // FONT_H
