#ifndef MATHUTILS_H
#define MATHUTILS_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

class MathUtils
{
    public:
        static int randomInt( int min, int max );
        static void init();
    protected:
    private:
};

#endif // MATHUTILS_H
