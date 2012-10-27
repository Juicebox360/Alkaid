#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d
{
    public:
        Vector2d();
        Vector2d( double _x, double _y );
        virtual ~Vector2d();
        void translate_x( double x_trans );
        void translate_y( double y_trans );
        void translate( double x_trans, double y_trans );
        void translate( Vector2d &trans_vec );
        void scale_x( double x_scale );
        void scale_y( double y_scale );
        void scale( double x_scale, double y_scale );
        void scale( Vector2d &scale_vec );

        double x;
        double y;

        static Vector2d ZERO_VEC;
    protected:
    private:
};

#endif // VECTOR2d_H
