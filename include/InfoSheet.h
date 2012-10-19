#ifndef INFOSHEET_H
#define INFOSHEET_H

#include "SDL.h"

#include "util/Vector2f.h"
#include "util/Colour.h"
#include "gfx/AnimatedSprite.h"

class InfoSheet
{
    public:
        InfoSheet( double _x, double _y, double velocityX, double velocityY );
        virtual ~InfoSheet();
        void update( SDL_Surface *screen, int delta );
        void render( SDL_Surface *screen );
        bool isVisible() const;

        static void preInit();

        static const int SHEET_TYPES = 3, ANIM_RATE = 100;
        static const double G;
        static const float FADE_RATE;
    protected:
    private:
        void init( double _x, double _y, double velocityX, double velocityY );

        Vector2f position, velocity, initialVelocity;
        Colour colour = Colour( 255, 255, 255, 255 );
        int sheetIndex = 0;
        bool visible = true;
        static AnimatedSprite* sheet[];
};

#endif // INFOSHEET_H
