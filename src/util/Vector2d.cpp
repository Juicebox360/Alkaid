#include "util/Vector2d.h"

Vector2d::Vector2d()
{
    x = 0;
    y = 0;
}
Vector2d::Vector2d( double _x, double _y )
{
    x = _x;
    y = _y;
}

Vector2d::~Vector2d()
{
    //dtor
}

void Vector2d::translateX( double xTrans )
{
    x += xTrans;
}

void Vector2d::translateY( double yTrans )
{
    y += yTrans;
}

void Vector2d::translate( double xTrans, double yTrans )
{
    translateX( xTrans );
    translateY( yTrans );
}
void Vector2d::translate( Vector2d &transVector )
{
    translate( transVector.x, transVector.y );
}

void Vector2d::scaleX( double xScale )
{
    x *= xScale;
}

void Vector2d::scaleY( double yScale )
{
    y *= yScale;
}

void Vector2d::scale( double xScale, double yScale )
{
    scaleX( xScale );
    scaleY( yScale );
}
void Vector2d::scale( Vector2d &scaleVector )
{
    scale( scaleVector.x, scaleVector.y );
}

void Vector2d::setX( double _x )
{
    x = _x;
}

void Vector2d::setY( double _y )
{
    y = _y;
}

double Vector2d::getX() const
{
    return x;
}

double Vector2d::getY() const
{
    return y;
}
