#include "util/Vector2f.h"

Vector2f::Vector2f()
{
    x = 0;
    y = 0;
}
Vector2f::Vector2f( double _x, double _y )
{
    x = _x;
    y = _y;
}

Vector2f::~Vector2f()
{
    //dtor
}

void Vector2f::translateX( double xTrans )
{
    x += xTrans;
}

void Vector2f::translateY( double yTrans )
{
    y += yTrans;
}

void Vector2f::translate( double xTrans, double yTrans )
{
    translateX( xTrans );
    translateY( yTrans );
}
void Vector2f::translate( Vector2f &transVector )
{
    translate( transVector.x, transVector.y );
}

void Vector2f::scaleX( double xScale )
{
    x *= xScale;
}

void Vector2f::scaleY( double yScale )
{
    y *= yScale;
}

void Vector2f::scale( double xScale, double yScale )
{
    scaleX( xScale );
    scaleY( yScale );
}
void Vector2f::scale( Vector2f &scaleVector )
{
    scale( scaleVector.x, scaleVector.y );
}

void Vector2f::setX( double _x )
{
    x = _x;
}

void Vector2f::setY( double _y )
{
    y = _y;
}

double Vector2f::getX() const
{
    return x;
}

double Vector2f::getY() const
{
    return y;
}
