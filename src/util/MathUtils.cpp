#include "util/MathUtils.h"

#include <ctime>

void MathUtils::init()
{
    srand( (unsigned) time( 0 ) );
}

int MathUtils::randomInt( int min, int max )
{
    return min + (rand() % (max - min + 1));
}
