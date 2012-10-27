#include "util/Vector2d.h"

Vector2d Vector2d::ZERO_VEC = Vector2d();

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

void Vector2d::translate_x( double x_trans )
{
    x += x_trans;
}

void Vector2d::translate_y( double y_trans )
{
    y += y_trans;
}

void Vector2d::translate( double x_trans, double y_trans )
{
    translate_x( x_trans );
    translate_y( y_trans );
}
void Vector2d::translate( Vector2d &trans_vec )
{
    translate( trans_vec.x, trans_vec.y );
}

void Vector2d::scale_x( double x_scale )
{
    x *= x_scale;
}

void Vector2d::scale_y( double y_scale )
{
    y *= y_scale;
}

void Vector2d::scale( double x_scale, double y_scale )
{
    scale_x( x_scale );
    scale_y( y_scale );
}
void Vector2d::scale( Vector2d &scale_vec )
{
    scale( scale_vec.x, scale_vec.y );
}
