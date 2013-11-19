//  Copyright Neil Groves 2009. 
//  Copyright Eric Niebler 2013
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef RANGES_V3_ALGORITHM_FOR_EACH_HPP
#define RANGES_V3_ALGORITHM_FOR_EACH_HPP

#include <utility>
#include <algorithm>
#include <functional>
#include <range/v3/begin_end.hpp>
#include <range/v3/concepts.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/utility/bindable.hpp>

namespace ranges
{
    inline namespace v3
    {
        struct for_eacher
        {
            /// \brief template function \c for_eacher::operator()
            ///
            /// range-based version of the \c for_each std algorithm
            ///
            /// \pre \c InputRange is a model of the InputRange concept
            /// \pre \c UnaryFunction is a model of the UnaryFunction concept
            template<typename InputRange, typename UnaryFunction>
            UnaryFunction operator()(InputRange && rng, UnaryFunction fun) const
            {
                CONCEPT_ASSERT(ranges::InputRange<InputRange>());
                return std::for_each(ranges::begin(rng), ranges::end(rng), std::move(fun));
            }

            /// \overload
            template<typename UnaryFunction, typename This = for_eacher>
            auto operator()(UnaryFunction fun) const
                -> decltype(bindable<This>{}(std::placeholders::_1, std::move(fun)))
            {
                return bindable<This>{}(std::placeholders::_1, std::move(fun));
            }
        };

        constexpr bindable<for_eacher> for_each {};

    } // inline namespace v3

} // namespace ranges

#endif // include guard