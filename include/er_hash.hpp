#pragma once

#include "equiv_relation"

namespace cpeq
{
/*
Provides a hash functor for equivalence relation objects.
*/

template<std::unsigned_integral T = default_T>
struct er_hash
{
	std::size_t operator()(const eq_relation<T>&) const;
};

#include "er_hash.tpp"
}
