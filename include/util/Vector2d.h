#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d
{
    public:
        Vector2d();
        Vector2d( double _x, double _y );
        virtual ~Vector2d();
        void translateX( double xTrans );
        void translateY( double yTrans );
        void translate( double xTrans, double yTrans );
        void translate( Vector2d &transVector );
        void scaleX( double xScale );
        void scaleY( double yScale );
        void scale( double xScale, double yScale );
        void scale( Vector2d &scaleVector );
        void setX( double _x );
        void setY( double _y );
        double getX() const;
        double getY() const;

        double x;
        double y;
    protected:
    private:
};

#endif // VECTOR2d_H
