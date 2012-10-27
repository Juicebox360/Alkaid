#include <ctime>
#include <sstream>
#include <tuple>
#include <utility>
#include <iostream>

#include "util/Utils.h"

std::stringstream Utils::sstr;

void Utils::pre_init()
{
    srand( (unsigned) time( 0 ) );
}

int Utils::random_int( int min, int max )
{
    return min + (rand() % (max - min + 1));
}
