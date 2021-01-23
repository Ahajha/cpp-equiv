#pragma once

#include "equiv.hpp"

template<std::unsigned_integral T>
struct eq_relation<T>::element
{
	// If this element is a leader, this is the number
	// of members in the group, otherwise undefined.
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
		// Start with each element in its own group
		elements.emplace_back(1,i);
		cgl.emplace_back(i);
	}
}

/*
eq_relation universal_relation(std::size_t size);
*/

template<std::unsigned_integral T>
void eq_relation<T>::merge(std::size_t x, std::size_t y)
{
	T leadX = leader(x), leadY = leader(y);
	
	// No action needed if they are in the same group.
	if (leadX != leadY)
	{
		// Prefer to demote leaders with smaller groups
		if (elements[leadX].n_group_members < elements[leadY].n_group_members)
		{
			elements[leadY].n_group_members += elements[leadX].n_group_members;
			elements[leadX].boss = leadY;
		}
		else
		{
			elements[leadX].n_group_members += elements[leadY].n_group_members;
			elements[leadY].boss = leadX;
		}
		changed = true;
		--_n_groups;
	}
}

template<std::unsigned_integral T>
bool eq_relation<T>::equivalent(std::size_t x, std::size_t y) const
{
	return leader(x) == leader(y);
}

/*
void append_element();

bool operator==(const eq_relation& S) const;

std::partial_ordering operator<=>(const eq_relation& S) const;

std::size_t bell(std::size_t n);

std::vector<eq_relation> enumerate(std::size_t size);

eq_relation reverse() const;

eq_relation operator+(const eq_relation& S) const;

eq_relation& operator+=(const eq_relation& S);

eq_relation operator-(std::size_t size) const;

eq_relation& operator-=(std::size_t size);
*/

template<std::unsigned_integral T>
const std::vector<T>& eq_relation<T>::canonical_group_labeling() const
{
	if (changed)
	{
		updateCGL();
		changed = false;
	}
	
	return cgl;
}

template<std::unsigned_integral T>
std::ostream& operator<<(std::ostream& stream, const eq_relation<T>& R)
{
	const auto& cgl = R.canonical_group_labeling();
	
	for (unsigned label : cgl) stream << label << ' ';
	
	return stream << '\b';
}

template<std::unsigned_integral T>
std::size_t eq_relation<T>::size() const
{
	return elements.size();
}

template<std::unsigned_integral T>
T eq_relation<T>::n_groups() const
{
	return _n_groups;
}

template<std::unsigned_integral T>
T eq_relation<T>::leader(T x) const
{
	if (elements[x].boss == x) return x;
	
	return (elements[x].boss = leader(elements[x].boss));
}

template<std::unsigned_integral T>
void eq_relation<T>::updateCGL() const
{
	// This is possible if this ER was constructed 'manually'
	if (cgl.size() != elements.size()) cgl.resize(elements.size());
	
	std::vector<bool> filled(elements.size());
	
	unsigned group_num = 0;
	for (unsigned i = 0; i < elements.size(); ++i)
	{
		// If an element has already been marked, then it is
		// a leader, we can ignore this case and just let it
		// get overwritten again.
		
		unsigned lead = leader(i);
		if (!filled[lead])
		{
			cgl[lead] = group_num++;
			filled[lead] = true;
		}
		cgl[i] = cgl[lead];
		filled[i] = true;
	}
}
