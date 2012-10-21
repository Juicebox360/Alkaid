#include "util/Utils.h"

#include <ctime>
#include <sstream>
#include <tuple>
#include <utility>
#include <iostream>

std::stringstream Utils::sstr;

void Utils::init()
{
    srand( (unsigned) time( 0 ) );
}

int Utils::randomInt( int min, int max )
{
    return min + (rand() % (max - min + 1));
}
