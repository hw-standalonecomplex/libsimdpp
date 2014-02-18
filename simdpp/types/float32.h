/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/types/float32x8.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_fp
/// @{

/** Class representing a @a float32 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class float32 {
public:

    using element_type = float;
    using uint_element_type = uint32_t;
    using int_vector_type = gint32<N>;
    using uint_vector_type = uint32<N>;
    using base_vector_type = float32v;
    using mask_type = mask_float32<N>;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_FLOAT32_SIZE - 1) / SIMDPP_FAST_FLOAT32_SIZE;

    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    float32<N>() = default;
    float32<N>(const float32<N>&) = default;
    float32<N>& operator=(const float32<N>&) = default;

    /// @{
    /// Construct from compatible int32 integer vector type
    explicit float32<N>(gint32<N> d)
    {
        for (unsigned i = 0; i < vec_length; i++) {
            (*this)[i] = d[i];
        }
    }

    float32<N>& operator=(gint32<N> d)  { operator=(float32<N>(d)); return *this; }
    /// @}

    const float32v* begin() const   { return d_; }
    float32v* begin()               { return d_; }
    const float32v* end() const     { return d_+vec_length; }
    float32v* end()                 { return d_+vec_length; }
    const float32v& operator[](unsigned i) const { return *(d_+i); }
    float32v& operator[](unsigned i)             { return *(d_+i); }

    /** Creates a float32 vector with the contents set to zero

        @code
        r0 = 0.0f
        ...
        rN = 0.0f
        @endcode
    */
    static float32<N> zero()
    {
        return float32<N>::set_broadcast(float32v::zero());
    }

    /** Creates a float vector from a value loaded from memory.

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float32<N> load_broadcast(const float* v0)
    {
        return float32<N>::set_broadcast(float32v::load_broadcast(v0));
    }

    /** Creates a float vector from a value stored in a core register.

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float32<N> set_broadcast(float v0)
    {
        return float32<N>::set_broadcast(float32v::set_broadcast(v0));
    }

    /** Creates a float vector from a native vector

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float32<N> set_broadcast(float32v v0)
    {
        float32<N> r;
        for (auto &v : r) v = v0;
        return r;
    }

    /** Creates a float32 vector from a value known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v0 v0 v0   ... ]
        @endcode
    */
    static float32<N> make_const(float v0)
    {
        return float32<N>::set_broadcast(float32v::make_const(v0));
    }

    /** Creates a float32 vector from two values known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v1 v0 v1   ... ]
        @endcode
    */
    static float32<N> make_const(float v0, float v1)
    {
        return float32<N>::set_broadcast(float32v::make_const(v0, v1));
    }

    /** Creates a float32 vector from four values known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v1 v2 v3   ... ]
        @endcode
    */
    static float32<N> make_const(float v0, float v1, float v2, float v3)
    {
        return float32<N>::set_broadcast(float32v::make_const(v0, v1, v2, v3));
    }

private:
    float32v d_[vec_length];
};

/// Class representing a mask for 32-bit floating point vector of arbitrary
/// length. The vector always contains at least one native vector.
template<unsigned N>
class mask_float32 {
public:
    using base_vector_type = mask_float32v;
    static constexpr unsigned length = 8;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_FLOAT32_SIZE - 1) / SIMDPP_FAST_FLOAT32_SIZE;

    mask_float32<N>() = default;
    mask_float32<N>(const mask_float32 &) = default;
    mask_float32<N> &operator=(const mask_float32 &) = default;

    const mask_float32v* begin() const   { return d_; }
    mask_float32v* begin()               { return d_; }
    const mask_float32v* end() const     { return d_+vec_length; }
    mask_float32v* end()                 { return d_+vec_length; }
    const mask_float32v& operator[](unsigned i) const { return *(d_+i); }
    mask_float32v& operator[](unsigned i)             { return *(d_+i); }

    /// Convert to a regular vector
    operator float32<N>() const
    {
        float32<N> r;
        for (unsigned i = 0; i < vec_length; ++i) {
            r[i] = d_[i];
        }
        return r;
    }

private:
    mask_float32v d_[vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif