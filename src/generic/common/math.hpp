/**
 * @file math.hpp
 * @brief Contains helpful math functions
 *
 * @date November 19, 2018 11:43
 * @author Koen Komeya 
 */

#ifndef GENERIC_COMMON_MATH_HPP_
#define GENERIC_COMMON_MATH_HPP_

#include <type_traits>

/**
 * @namespace kMath
 * @brief Supplies math functions
 *
 * @author Koen Komeya
 * @since November 19, 2018 11:44
 */
namespace kMath {

    /** Helper for sqrtNR */
    template <typename F>
    constexpr F sqrtNR_helper (F x, F guess, F lastG){
        return (guess == lastG ? guess :
                sqrtNR_helper<F>(x, 0.5 * (guess + x / guess), guess));
    }
    /**
     * @fn sqrtNR
     * @brief determines square root via the Newton-Raphson algorithm.
     * Determines square root via the Newton-Raphson algorithm.
     * Inspired by https://stackoverflow.com/a/34134071
     * @param   x the number to find the square root of
     *
     * @return  square root of x
     * @since November 19, 2018 11:45
    **/
    template <typename F>
    constexpr F sqrtNR (F x){
        static_assert(std::is_floating_point<F>::value,
                "F is not floating point");
        return sqrtNR_helper<F>(x, x, 0);
    }

}  // namespace kMath


#endif /* GENERIC_COMMON_MATH_HPP_ */
