#include "InfoSheet.h"
#include "util/MathUtils.h"

const double InfoSheet::G = 0.1d;
const float InfoSheet::FADE_RATE = 0.02d;

AnimatedSprite* InfoSheet::sheet[InfoSheet::SHEET_TYPES];

InfoSheet::InfoSheet( double _x, double _y, double velocityX, double velocityY )
{
    init( _x, _y, velocityX, velocityY );
}

InfoSheet::~InfoSheet()
{
    //dtor
}

void InfoSheet::update( SDL_Surface *screen, int delta )
{
    if ( visible )
    {
        (sheet[sheetIndex])->update( screen, delta );

        // Simulate movement. Gravity constant at 9.8.
        //velocity.translateY( G * delta );
        velocity.translateY( G );

        //position.translate( velocity.getX() * delta, velocity.getY() * delta );
        position.translate( velocity.getX(), velocity.getY() );

        colour.addAlpha( -InfoSheet::FADE_RATE );

        if ( colour.getAlphaI() == 0 )
        {
            visible = false;
        }

        printf( "Sheet data:\nx: %f\ny: %f\nxVel: %f\nyVel: %f\nindex: %i\n", position.getX(), position.getY(), velocity.getX(), velocity.getY(), sheetIndex );
    }
}

void InfoSheet::render( SDL_Surface *screen )
{
    if ( visible )
    {
        (sheet[sheetIndex])->render( screen, position.getX(), position.getY(), 2.0d, 2.0d, &colour, 0.0d );
    }

    (sheet[1])->render( screen, 400, 400, 2.0d, 2.0d, &colour, 0.0d );
}

void InfoSheet::init( double _x, double _y, double velocityX, double velocityY )
{
    position.setX( _x );
    position.setY( _y );
    velocity.setX( velocityX );
    velocity.setY( velocityY );

    sheetIndex = MathUtils::randomInt( 0, SHEET_TYPES - 1 );

    //printf( "The newly created sheet data:\nx: %f\ny: %f\nxVel: %f\nyVel: %f\nindex: %i\n", position.getX(), position.getY(), velocity.getX(), velocity.getY(), sheetIndex );
}

void InfoSheet::preInit()
{
    // Initial animation loading
    sheet[0] = new AnimatedSprite( "sheets.png", ANIM_RATE, 0, 4, true, 10, 10, 5, 5 );
    sheet[1] = new AnimatedSprite( "sheets.png", ANIM_RATE, 5, 9, true, 10, 10, 5, 5 );
    sheet[2] = new AnimatedSprite( "sheets.png", ANIM_RATE, 10, 14, true, 10, 10, 5, 5 );
}

bool InfoSheet::isVisible() const
{
    return visible;
}
