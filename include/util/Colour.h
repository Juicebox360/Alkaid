#ifndef COLOUR_H
#define COLOUR_H

#include "SDL.h"

class Colour
{
    public:
        Colour( int r = 255, int g = 255, int b = 255, int a = 255 );
        Colour( double r = 1.0f, double g = 1.0f, double b = 1.0f, double a = 1.0f );
        virtual ~Colour();
        double getRedF() const;
        double getGreenF() const;
        double getBlueF() const;
        double getAlphaF() const;
        int getRedI() const;
        int getGreenI() const;
        int getBlueI() const;
        int getAlphaI() const;
        void setRed( double _r );
        void setRed( int _r );
        void setGreen( double _g );
        void setGreen( int _g );
        void setBlue( double _b );
        void setBlue( int _b );
        void setAlpha( double _a );
        void setAlpha( int _a );
        void addRed( double _r );
        void addRed( int _r );
        void addGreen( double _g );
        void addGreen( int _g );
        void addBlue( double _b );
        void addBlue( int _b );
        void addAlpha( double _a );
        void addAlpha( int _a );
        SDL_Color toEngineFormat() const;

        // Some constants
        static Colour WHITE;
        static Colour BLACK;
        static Colour RED;
        static Colour GREEN;
        static Colour BLUE;

        double r;
        double g;
        double b;
        double a;
    protected:
    private:
        void init( double r, double g, double b, double a );
        void setColourValue( double &valueLoc, double value );
};

#endif // COLOUR_H
