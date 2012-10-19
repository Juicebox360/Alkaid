#ifndef COLOUR_H
#define COLOUR_H

#include "SDL.h"

class Colour
{
    public:
        Colour( int r = 255, int g = 255, int b = 255, int a = 255 );
        Colour( float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f );
        virtual ~Colour();
        float getRedF() const;
        float getGreenF() const;
        float getBlueF() const;
        float getAlphaF() const;
        int getRedI() const;
        int getGreenI() const;
        int getBlueI() const;
        int getAlphaI() const;
        void setRed( float _r );
        void setRed( int _r );
        void setGreen( float _g );
        void setGreen( int _g );
        void setBlue( float _b );
        void setBlue( int _b );
        void setAlpha( float _a );
        void setAlpha( int _a );
        void addRed( float _r );
        void addRed( int _r );
        void addGreen( float _g );
        void addGreen( int _g );
        void addBlue( float _b );
        void addBlue( int _b );
        void addAlpha( float _a );
        void addAlpha( int _a );
        SDL_Color toEngineFormat() const;

        // Some constants
        static Colour WHITE;
        static Colour BLACK;
        static Colour RED;
        static Colour GREEN;
        static Colour BLUE;
    protected:
    private:
        void init( float r, float g, float b, float a );
        void setColourValue( float &valueLoc, float value );

        float r;
        float g;
        float b;
        float a;
};

#endif // COLOUR_H
