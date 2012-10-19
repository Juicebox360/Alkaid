#include "gfx/AnimatedSprite.h"

// TODO: Backward animation. Utilising the same texture sheet for different animation indices

AnimatedSprite::~AnimatedSprite()
{
    //dtor
}

void AnimatedSprite::init( int animRate, int startIndex, int endIndex, bool repetition )
{
    setAnimationRate( animRate );
    setAnimationStartIndex( startIndex );
    setAnimationEndIndex( endIndex );
    setRepeat( repetition );
}

void AnimatedSprite::setAnimationRate( int animRate )
{
    if ( animRate < 0 )
    {
        rate = 0;
    }
    else
    {
        rate = animRate;
    }
}

void AnimatedSprite::setAnimationStartIndex( int startIndex )
{
    setIndex( animStartIndex, startIndex );
}

void AnimatedSprite::setAnimationEndIndex( int endIndex )
{
    setIndex( animEndIndex, endIndex );
}

void AnimatedSprite::setAnimationIndex( int index )
{
    setIndex( animCurrIndex, index );
}

void AnimatedSprite::setRepeat( bool repetition )
{
    repeat = repetition;
}

void AnimatedSprite::toggleRepeat()
{
    repeat = !repeat;
}

int AnimatedSprite::getAnimationRate() const
{
    return rate;
}

int AnimatedSprite::getAnimationStartIndex() const
{
    return animStartIndex;
}

int AnimatedSprite::getAnimationEndIndex() const
{
    return animEndIndex;
}

int AnimatedSprite::getAnimationIndex() const
{
    return animCurrIndex;
}

bool AnimatedSprite::isRepeating() const
{
    return repeat;
}

void AnimatedSprite::update( SDL_Surface *screen, int delta )
{
    Sprite::update( screen, delta );

    accumulatedTime += delta;
    if ( accumulatedTime >= rate )
    {
        if ( animCurrIndex + 1 <= animEndIndex )
        {
            animCurrIndex++;
        }
        else
        {
            if ( repeat )
            {
                animCurrIndex = animStartIndex;
            }
        }
        accumulatedTime = 0;
    }
}

void AnimatedSprite::render( SDL_Surface *screen, double x, double y, double xScale, double yScale, Colour *colour, double theta )
{
    Sprite::render( screen, x, y, animCurrIndex, xScale, yScale, colour, theta );
}

void AnimatedSprite::setIndex( int &valueLoc, int value )
{
    if ( value < 0 || value >= getCount() )
    {
        valueLoc = getCount() - 1;
    }
    else
    {
        valueLoc = value;
    }
}
