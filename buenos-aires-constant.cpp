/*         _.._
 *      .' .-'`      ____  _     _____ _      ____  ____    ____  _  ____  _____ ____    ____  ____  _      ____  _____  ____  _      _____
 *     /  /         /  _ \/ \ /\/  __// \  /|/  _ \/ ___\  /  _ \/ \/  __\/  __// ___\  /   _\/  _ \/ \  /|/ ___\/__ __\/  _ \/ \  /|/__ __\
 *     |  |         | | //| | |||  \  | |\ ||| / \||    \  | / \|| ||  \/||  \  |    \  |  /  | / \|| |\ |||    \  / \  | / \|| |\ ||  / \
 *     \  '.___.;   | |_\\| \_/||  /_ | | \||| \_/|\___ |  | |-||| ||    /|  /_ \___ |  |  \_ | \_/|| | \||\___ |  | |  | |-||| | \||  | |
 *      '._  _.'    \____/\____/\____\\_/  \|\____/\____/  \_/ \|\_/\_/\_\\____\\____/  \____/\____/\_/  \|\____/  \_/  \_/ \|\_/  \|  \_/
 *         ``
 * Alexander
 * Töpfer 2020
 * Inspired by one of my favourite youtube channels https://www.youtube.com/watch?v=_gCKX6VMvmU
 */
#include <boost/math/special_functions/pow.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#define cpp_float cpp_dec_float_100
#define arr_size( x ) (sizeof( x ) / sizeof( x[0] ))
using namespace boost::multiprecision;
unsigned short primes_51[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                              31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                              73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
                              127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                              179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233 }, iter;
cpp_float prime_constant = 0, (*cppFloor)( cpp_float ) = []( cpp_float val ){ return cpp_float( cpp_int( val ) ); };
cpp_int prime_denominator = 1;
int main() {
    // calculate prime constant based on formula up to one hundred digits of accuracy
    // f_n = (p_n - 1) + ( (p_(n+1) - 1) / p_n ) + ( (p_(n+2) - 1) / (p_(n+1) * p_n) ) + ( (p_(n+3) - 1) / (p_(n+2) * p_(n+1) * p_n) )...
    for( iter = 0; iter < arr_size( primes_51 ); ++iter ) {
        prime_constant += ( primes_51[iter] - 1 ) / cpp_float( prime_denominator );
        prime_denominator *= primes_51[iter];
    }
    // prime constant or buenos aires constant: 2.920050977316...
    std::cout << prime_constant.str(100) << std::endl;
    // unwrap constant to first fifty prime numbers
    // f_(n+1) = floor(f_n) * ( f_n - floor(f_n) + 1)
    for( iter = 0; iter < arr_size( primes_51 )-1; ++iter ) {
        std::cout << cppFloor( prime_constant ) << ( ( iter < (arr_size( primes_51 )-2) ) ? "," : " " );
        prime_constant = cppFloor( prime_constant ) * ( prime_constant - cppFloor( prime_constant ) + 1 );
    }
}
