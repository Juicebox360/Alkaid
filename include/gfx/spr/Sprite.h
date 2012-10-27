#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL.h"
#include "SDL_opengl.h"
#include "util/Colour.h"
#include "util/Vector2d.h"

class Sprite
{
    public:
        Sprite();
        Sprite( const Sprite *sprite );
        Sprite( SDL_Surface *image, int spriteWidth = 0, int spriteHeight = 0, double spriteCentreX = 0, double spriteCentreY = 0 );
        Sprite( std::string filename, int spriteWidth = 0, int spriteHeight = 0, double spriteCentreX = 0, double spriteCentreY = 0 );
        virtual ~Sprite();

        int get_count() const;

        void set_centre_x( double sprite_centre_x );
        void set_centre_y( double sprite_centre_y );
        void set_visible( bool visiblity );
        void toggle_visible();

        virtual void render( SDL_Surface *screen, double x, double y, int index = 0, double x_scale = 1.0d, double y_scale = 1.0d, Colour *colour = &Colour::WHITE, double theta = 0.0d );
        virtual void render( SDL_Surface *screen, double x, double y, int x_index = 0, int y_index = 0, double x_scale = 1.0d, double y_scale = 1.0d, Colour *colour = &Colour::WHITE, double theta = 0.0d );
        virtual void update( SDL_Surface *screen, double delta );

        Vector2d *index_to_coord( int i );
        int coord_to_index( Vector2d &coord );
        int coord_to_index( int x, int y );

        GLuint texture;
        GLenum texture_format;
        GLint colour_format;
        int count_x, count_y, w, h;
        double centre_x, centre_y;
        bool visible = true;
    protected:
        void handle_image_error( int error_code );
    private:
        SDL_Surface *load_image( std::string filename );
        void init( SDL_Surface *image, int spriteWidth, int spriteHeight, double spriteCentreX, double spriteCentreY );
};

#endif // SPRITE_H
