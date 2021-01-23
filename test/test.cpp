#include "../include/equiv.hpp"
#include <iostream>
#include <cassert>

int main()
{
	{
	cpeq::eq_relation er1(5);
	
	std::cout << er1 << '\n'; // 0 1 2 3 4
	assert(er1.n_groups() == 5);
	
	// Test equivalences
	for (unsigned i = 0; i < er1.size(); ++i)
	{
		for (unsigned j = 0; j < er1.size(); ++j)
		{
			// No elements should be equivalent, except for self-equivalence
			assert(er1.equivalent(i,j) == (i == j));
		}
	}
	
	// Test merging and equivalence tests, along with printing of merged objects.
	er1.merge(2,4);
	
	std::cout << er1 << '\n'; // 0 1 2 3 2
	assert(er1.n_groups() == 4);
	
	for (unsigned i = 0; i < er1.size(); ++i)
	{
		for (unsigned j = 0; j < er1.size(); ++j)
		{
			if ((i == 2 && j == 4) || (i == 4 && j == 2))
				assert(er1.equivalent(i,j));
			else
				assert(er1.equivalent(i,j) == (i == j));
		}
	}
	
	er1.merge(1,3);
	
	std::cout << er1 << '\n'; // 0 1 2 1 2
	assert(er1.n_groups() == 3);
	
	assert(er1.equivalent(1,3));
	assert(er1.equivalent(3,1));
	assert(!er1.equivalent(1,4));
	assert(!er1.equivalent(3,2));
	assert(!er1.equivalent(1,2));
	assert(!er1.equivalent(3,4));
	assert(!er1.equivalent(1,0));
	assert(!er1.equivalent(3,0));
	
	er1.merge(2,3);
	
	std::cout << er1 << '\n'; // 0 1 1 1 1
	assert(er1.n_groups() == 2);
	
	for (unsigned i = 0; i < er1.size(); ++i)
	{
		for (unsigned j = 0; j < er1.size(); ++j)
		{
			// Index 0 is alone, so i and j are equivalent
			// iff either both or none of them are 0.
			assert(!er1.equivalent(i,j) == ((i == 0) ^ (j == 0)));
		}
	}
	
	// This merge should have no effect.
	er1.merge(3,4);
	
	std::cout << er1 << '\n'; // 0 1 1 1 1
	assert(er1.n_groups() == 2);
	
	for (unsigned i = 0; i < er1.size(); ++i)
	{
		for (unsigned j = 0; j < er1.size(); ++j)
		{
			// Index 0 is alone, so i and j are equivalent
			// iff either both or none of them are 0.
			assert(!er1.equivalent(i,j) == ((i == 0) ^ (j == 0)));
		}
	}
	
	er1.merge(0,4);
	
	std::cout << er1 << '\n'; // 0 0 0 0
	assert(er1.n_groups() == 1);
	
	for (unsigned i = 0; i < er1.size(); ++i)
	{
		for (unsigned j = 0; j < er1.size(); ++j)
		{
			// All elements are equivalent.
			assert(er1.equivalent(i,j));
		}
	}
	
	// Test universal relations
	auto univ = cpeq::universal_relation(5);
	
	std::cout << univ << '\n'; // 0 0 0 0 0
	assert(univ.n_groups() == 1);
	
	for (unsigned i = 0; i < univ.size(); ++i)
	{
		for (unsigned j = 0; j < univ.size(); ++j)
		{
			// All elements are equivalent.
			assert(univ.equivalent(i,j));
		}
	}
	
	// Test equivalence
	assert(er1 == univ);
	}
}
