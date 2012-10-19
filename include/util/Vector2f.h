#ifndef VECTOR2F_H
#define VECTOR2F_H


class Vector2f
{
    public:
        Vector2f();
        Vector2f( double _x, double _y );
        virtual ~Vector2f();
        void translateX( double xTrans );
        void translateY( double yTrans );
        void translate( double xTrans, double yTrans );
        void translate( Vector2f &transVector );
        void scaleX( double xScale );
        void scaleY( double yScale );
        void scale( double xScale, double yScale );
        void scale( Vector2f &scaleVector );
        void setX( double _x );
        void setY( double _y );
        double getX() const;
        double getY() const;
    protected:
    private:
        double x;
        double y;
};

#endif // VECTOR2F_H
