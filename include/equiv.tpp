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
	
	for (T i = 0; i < size; ++i)
	{
		// Start with each element in its own group
		elements.emplace_back(1,i);
		cgl.emplace_back(i);
	}
}

template<std::unsigned_integral T = default_T>
[[nodiscard]] eq_relation<T> universal_relation(std::size_t size)
{
	eq_relation<T> result(size);
	
	// Arbitrarily choose 0 as the universal leader,
	// everything else should be updated to this.
	for (std::size_t i = 1; i < size; ++i)
	{
		result.elements[i].boss = 0;
		result.cgl[i] = 0;
	}
	result._n_groups = 1;
	result.elements[0].n_group_members = size;
	
	return result;
}

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

template<std::unsigned_integral T>
void eq_relation<T>::append_element()
{
	elements.emplace_back(1,elements.size());
	++_n_groups;
	changed = true;
}

template<std::unsigned_integral T>
bool eq_relation<T>::operator==(const eq_relation& S) const
{
	if (elements.size() != S.elements.size()) return false;
	
	return canonical_group_labeling() == S.canonical_group_labeling();
}

/*
std::partial_ordering operator<=>(const eq_relation& S) const;
*/

template<std::unsigned_integral T = default_T>
[[nodiscard]] std::vector<eq_relation<T>> enumerate(std::size_t size)
{
	std::vector<eq_relation<T>> result;
	
	if (size == 0)
	{
		// Only one of size 0
		result.emplace_back();
	}
	else
	{
		const auto smallerERs = enumerate(size - 1);
		
		for (const auto& R : smallerERs)
		{
			// For each group in R, there will be a new ER
			// with the last member merged with that group.
			for (unsigned i = 0; i < size - 1; ++i)
			{
				// Since we are looking for the unique groups,
				// just look for the leaders.
				if (R.elements[i].boss == i)
				{
					// Add a copy of R, and add an element.
					result.emplace_back(R).append_element();
					
					// Make the new element equivalent to element i.
					result.back().merge(i,size - 1);
				}
			}
			
			// The last option is to have on element not equivalent to anything.
			result.emplace_back(R).append_element();
		}
	}
	
	return result;
}

template<std::unsigned_integral T>
eq_relation<T> eq_relation<T>::reverse() const
{
	const std::size_t n = elements.size(); // for brevity
	eq_relation result;
	
	for (unsigned i = 0; i < n; ++i)
	{
		result.elements.emplace_back(
			elements[n - i - 1].n_group_members, n - leader(n - i - 1) - 1
		);
	}
	result._n_groups = _n_groups;
	
	// CGL is non-trivial to determine, so regenerate it normally.
	result.changed = true;
	
	return result;
}

/*
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
	
	for (std::size_t label : cgl) stream << label << ' ';
	
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
	
	T group_num = 0;
	for (std::size_t i = 0; i < elements.size(); ++i)
	{
		// If an element has already been marked, then it is
		// a leader, we can ignore this case and just let it
		// get overwritten again.
		
		T lead = leader(i);
		if (!filled[lead])
		{
			cgl[lead] = group_num++;
			filled[lead] = true;
		}
		cgl[i] = cgl[lead];
		filled[i] = true;
	}
}

[[nodiscard]] constexpr std::size_t bell(std::size_t n)
{
	// List from https://oeis.org/A000110
	std::size_t table[] {
		1,1,2,5,15,52,203,877,4140,21147,115975,678570,4213597,27644437,
		190899322,1382958545,10480142147,82864869804,682076806159,5832742205057,
		51724158235372,474869816156751,4506715738447323,44152005855084346,
		445958869294805289,4638590332229999353
	};

	return table[n];
}
