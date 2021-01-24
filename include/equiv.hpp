#pragma once

#include <vector>
#include <iostream>
#include <compare>

namespace cpeq
{
/*
An equivalence relation (ER) deals with groups of objects.
Initially, an ER starts with a given number of distinct groups.
Groups can be merged and tested for equivalence, as well as added
and removed from the end. There are also several other useful methods.

In the following documentation, 'this' will be referred to as R, and
if there is another ER as a parameter, it will be referred to as S,
for simplicity of explanation.

No thread safety should be assumed, even when accessing unrelated
elements.

T is the size of the indexes used internally, defaults to at most
2^16 elements, a balance of space and practical size. Overflowing
the element count in any way is undefined behavior.
*/

using default_T = uint16_t;

template<std::unsigned_integral T = default_T>
struct eq_relation
{
	// Constructs an equivalence relation of a given size,
	// with all elements in their own groups by default.
	explicit eq_relation(std::size_t size = 0);
	
	// Returns the universal relation of a given size, where
	// all elements are equivalent to each other.
	template<std::unsigned_integral t>
	friend eq_relation<t> universal_relation(std::size_t size);
	
	// Sets the elements at indexes x and y to be equivalent.
	// (merges two groups together). Has no effect if x and y are
	// already equivalent.
	void merge(std::size_t x, std::size_t y);
	
	// Tests if the elements at index x and y are
	// equivalent (in the same group).
	[[nodiscard]] bool equivalent(std::size_t x, std::size_t y) const;
	
	// Appends an element to the back of R, not equivalent
	// to any other element, and in its own new group.
	void append_element();
	
	// R and S are equivalent iff R and S are the same size and, for all
	// valid indexes x and y, R.equivalent(x,y) iff S.equivalent(x,y).
	[[nodiscard]] bool operator==(const eq_relation& S) const;
	
	// Compares fine-ness of two equivalence relations.
	// If R and S of the same size, R is finer than S if, for all valid indexes
	// x and y, R.equivalent(x,y) implies S.equivalent(x,y). Intuitively, if
	// R is finer than S, then R can be turned into S via zero or more merges.
	//
	// If R and S are different sizes, behavior is undefined.
	//
	// less       -> R is finer than S
	// greater    -> S is finer than R (equivalently, R is coarser than S)
	// unordered  -> neither R nor S are finer than the other.
	// equivalent -> same definition as above, equivalent to both R and S
	//     being finer than the other.
	[[nodiscard]] std::partial_ordering operator<=>(const eq_relation& S) const;
	
	// Returns the reverse of this relation.
	// If R_rev is the reversal of R, and n is the size of R, then for all
	// valid indexes x and y, R.equivalent(x,y) iff R_rev(n-x-1,n-y-1).
	[[nodiscard]] eq_relation reverse() const;
	
	// Appends S to R. In the first case, returns a new ER
	// as the result. In the second, appends in-place to R.
	//
	// Appending S to R results in both groups from R and S
	// being in one relation, mutually non-equivalent. The
	// indexes of the elements in S are shifted over by R.size().
	[[nodiscard]] eq_relation operator+(const eq_relation& S) const;
	eq_relation& operator+=(const eq_relation& S);
	
	// Removes the last 'size' elements from the end of R.
	// In the first case, returns a new ER as the result.
	// In the second, modifies R in-place.
	[[nodiscard]] eq_relation operator-(std::size_t size) const;
	eq_relation& operator-=(std::size_t size);
	
	// Returns the canonical group labeling (CGL) of R.
	//
	// The CGL of R, C, is defined to be a list of R.size() indexes,
	// where for each valid index x, C[x] is the group number of element x.
	// Index 0 is always group 0, and each new group encountered in ascending
	// order of index is given a group label one higher.
	//
	// Examples:
	// In an ER with 5 elements with the second and last
	// elements merged, the CGL is 0 1 2 3 1.
	// In an ER with 6 elements with the first two, middle two, and last
	// two elements each forming a group, the CGL is 0 0 1 1 2 2.
	[[nodiscard]] const std::vector<T>& canonical_group_labeling() const;
	
	// Prints the canonical group labeling of R to an output stream.
	template<std::unsigned_integral t>
	friend std::ostream& operator<<(std::ostream&, const eq_relation<t>&);
	
	// Returns the number of elements in R.
	[[nodiscard]] std::size_t size() const;
	
	// Returns the number of non-equivalent groups in R.
	[[nodiscard]] T n_groups() const;
	
	// Returns all mutually non-equivalent ERs of a given size.
	// Number of ERs is equal to bell(size).
	template<std::unsigned_integral t>
	friend std::vector<eq_relation<t>> enumerate(std::size_t size);
	
	private:
	
	struct element;
	
	T leader(T) const;
	
	std::vector<element> elements;
	T _n_groups;
	
	// The CGL is cached, since many of these algorithms use it,
	// with a flag for noting if it needs updating.
	mutable std::vector<T> cgl;
	mutable bool changed;
	
	void updateCGL() const;
	
	bool finer_than(const eq_relation& S) const;
};

// Returns the nth Bell number.
// Due to size restrictions, requires 0 <= n <= 25.
// Implemented via lookup table.
[[nodiscard]] constexpr std::size_t bell(std::size_t n);

#include "equiv.tpp"
}
