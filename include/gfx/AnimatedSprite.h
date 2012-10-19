#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <string>

#include "SDL.h"
#include "gfx/Sprite.h"
#include "util/Colour.h"

class AnimatedSprite : public Sprite
{
    public:
        AnimatedSprite( SDL_Surface *image, int animRate = 0, int startIndex = 0, int endIndex = -1, bool repetition = true, int spriteWidth = 0, int spriteHeight = 0, double spriteCentreX = 0, double spriteCentreY = 0 ) : Sprite( image, spriteWidth, spriteHeight, spriteCentreX, spriteCentreY ) { init( animRate, startIndex, endIndex, repetition ); };
        AnimatedSprite( std::string filename, int animRate = 0, int startIndex = 0, int endIndex = -1, bool repetition = true, int spriteWidth = 0, int spriteHeight = 0, double spriteCentreX = 0, double spriteCentreY = 0 ) : Sprite( filename, spriteWidth, spriteHeight, spriteCentreX, spriteCentreY ) { init( animRate, startIndex, endIndex, repetition ); };
        virtual ~AnimatedSprite();

        void setAnimationRate( int animRate );
        void setAnimationStartIndex( int startIndex );
        void setAnimationEndIndex( int endIndex );
        void setAnimationIndex( int index );
        void setRepeat( bool repetition );
        void toggleRepeat();

        int getAnimationRate() const;
        int getAnimationStartIndex() const;
        int getAnimationEndIndex() const;
        int getAnimationIndex() const;
        bool isRepeating() const;

        void update( SDL_Surface *screen, int delta );
        void render( SDL_Surface *screen, double x, double y, double xScale = 1, double yScale = 1, Colour *colour = &Colour::WHITE, double theta = 0 );
    protected:
        int rate, accumulatedTime, animStartIndex, animEndIndex, animCurrIndex;
        bool repeat;
    private:
        void init( int animRate, int startIndex, int endIndex, bool repetition );
        void setIndex( int &valueLoc, int value );
};

#endif // ANIMATEDSPRITE_H
