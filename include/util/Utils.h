#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <string>
#include <ctime>
#include <sstream>
#include <tuple>
#include <utility>
#include <iostream>

enum CONSTANTS
{
};

class Utils
{
    public:
        template <class... Variables>
        static std::string concat( Variables... variables )
        {
            // Clear the stream
            Utils::sstr.str( "" );

            auto variablesTuple = std::make_tuple( variables... );
            Utils::concat( variablesTuple );

            return Utils::sstr.str();
        }
        static int random_int( int min, int max );
        static void pre_init();
    protected:
    private:
        template<std::size_t I = 0, typename... Tp>
        static inline typename std::enable_if<I == sizeof...(Tp), void>::type
            concat( std::tuple<Tp...>& t ) {}

        template<std::size_t I = 0, typename... Tp>
        static inline typename std::enable_if<I < sizeof...(Tp), void>::type
            concat( std::tuple<Tp...>& t )
            {
                sstr << std::get<I>( t );
                concat<I + 1, Tp...>( t );
            }

        static std::stringstream sstr;
};

#endif // UTILS_H
