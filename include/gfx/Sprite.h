#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL.h"
#include "SDL_opengl.h"
#include "util/Colour.h"
#include "util/Vector2f.h"

class Sprite
{
    public:
        Sprite();
        Sprite( SDL_Surface *image, int spriteWidth = 0, int spriteHeight = 0, double spriteCentreX = 0, double spriteCentreY = 0 );
        Sprite( std::string filename, int spriteWidth = 0, int spriteHeight = 0, double spriteCentreX = 0, double spriteCentreY = 0 );
        virtual ~Sprite();
        int getCount() const;
        int getHorizontalCount() const;
        int getVerticalCount() const;
        int getWidth() const;
        int getHeight() const;
        double getCentreX() const;
        double getCentreY() const;
        bool isVisible() const;

        void setCentreX( double nCX );
        void setCentreY( double nCY );
        void setVisible( bool visiblity );
        void toggleVisible();

        void render( SDL_Surface *screen, double x, double y, int index = 0, double xScale = 1, double yScale = 1, Colour *colour = &Colour::WHITE, double theta = 0 );
        void render( SDL_Surface *screen, double x, double y, int xIndex = 0, int yIndex = 0, double xScale = 1, double yScale = 1, Colour *colour = &Colour::WHITE, double theta = 0 );

        void update( SDL_Surface *screen, int delta );

        Vector2f *indexToCoord( int i );
        int coordToIndex( Vector2f &coord );
        int coordToIndex( int x, int y );
    protected:
        void handleImageError( int errorStatus );

        GLuint texture;
        GLenum textureFormat;
        GLint colourFormat;
        int countX, countY, sizeX, sizeY;
        double centreX, centreY;
        bool visible = true;
    private:
        SDL_Surface *loadImage( std::string filename );
        void init( SDL_Surface *image, int spriteWidth, int spriteHeight, double spriteCentreX, double spriteCentreY );
};

#endif // SPRITE_H
