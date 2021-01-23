#pragma once

#include "equiv.hpp"

template<std::unsigned_integral T>
struct eq_relation<T>::element
{
	// If this element is a leader, this is the number of members in the group.
	T n_group_members;
	
	// Index of the element that it 'points' to to see which group it is in.
	// If this element's boss is its index, then it is a leader of a group.
	// Mutable, since this may be modified in const methods.
	mutable T boss;
};

template<std::unsigned_integral T>
eq_relation<T>::eq_relation(std::size_t size)
	: _n_groups(size), changed(false)
{
	elements.reserve(size);
	cgl.reserve(size);
	
	for (unsigned i = 0; i < size; ++i)
	{
		// Start with each element 
		elements.emplace_back(1,i);
		cgl.emplace_back(i);
	}
}

/*
eq_relation universal_relation(std::size_t size);

[[nodiscard]] element& operator[](std::size_t i);

[[nodiscard]] const element& operator[](std::size_t i) const;

void append_element();

[[nodiscard]] bool operator==(const eq_relation& S) const;

[[nodiscard]] std::partial_ordering operator<=>(const eq_relation& S) const;

[[nodiscard]] static std::size_t bell(std::size_t n);

[[nodiscard]] static std::vector<eq_relation> enumerate(std::size_t size);

[[nodiscard]] eq_relation reverse() const;

[[nodiscard]] eq_relation  operator+ (const eq_relation& S) const;

eq_relation& operator+=(const eq_relation& S);

[[nodiscard]] eq_relation  operator- (std::size_t size) const;

eq_relation& operator-=(std::size_t size);

[[nodiscard]] const std::vector<T>& canonical_group_labeling() const;

template<std::unsigned_integral t>
friend std::ostream& operator<<(std::ostream&, const eq_relation<t>&);

[[nodiscard]] unsigned size() const;

[[nodiscard]] unsigned n_groups() const;

unsigned leader(unsigned) const;

void updateCGL() const;
*/
