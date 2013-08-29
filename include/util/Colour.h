#ifndef COLOUR_H
#define COLOUR_H

#include <SDL2/SDL.h>

class Colour
{
    public:
        Colour( int r = 255, int g = 255, int b = 255, int a = 255 );
        Colour( double r = 1.0d, double g = 1.0d, double b = 1.0d, double a = 1.0d );
        virtual ~Colour();
        double get_red_double() const;
        double get_green_double() const;
        double get_blue_double() const;
        double get_alpha_double() const;
        int get_red_int() const;
        int get_green_int() const;
        int get_blue_int() const;
        int get_alpha_int() const;
        void set_red( double _r );
        void set_red( int _r );
        void set_green( double _g );
        void set_green( int _g );
        void set_blue( double _b );
        void set_blue( int _b );
        void set_alpha( double _a );
        void set_alpha( int _a );
        void add_red( double _r );
        void add_red( int _r );
        void add_green( double _g );
        void add_green( int _g );
        void add_blue( double _b );
        void add_blue( int _b );
        void add_alpha( double _a );
        void add_alpha( int _a );
        SDL_Color engine_format() const;

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
        void set_colour_value( double &value_loc, double value );
};

#endif // COLOUR_H
