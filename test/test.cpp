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
	auto er1_copy = er1;
	
	er1.merge(3,4);
	
	assert(er1 == er1_copy);
	
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
	
	{
	// Test adding elements
	
	cpeq::eq_relation er1, er2(1);
	
	er1.append_element();
	
	assert(er1 == er2);
	
	er1.append_element();
	er1.merge(0,1);
	er1.append_element();
	
	std::cout << er1 << '\n'; // 0 0 1
	assert(er1.n_groups() == 2);
	}
	
	// Testing enumeration
	{
	const auto ers_5 = cpeq::enumerate(5);
	
	assert(ers_5.size() == cpeq::bell(5));
	
	std::cout << "All 52 5-element ERs:\n";
	for (const auto& er : ers_5)
	{
		std::cout << er << '\n';
	}
	}
	
	// Testing reverse
	{
	cpeq::eq_relation er1(5), er2(5), er3(7), er4(7);
	
	assert(er1 == er1.reverse());
	
	er1.merge(0,1);
	er2.merge(3,4);
	
	assert(er1 == er2.reverse());
	assert(er1.reverse() == er2);
	
	assert(er1.reverse().n_groups() == 4);
	
	er3.merge(1,2);
	er3.merge(3,5);
	er3.merge(5,6);
	
	er4.merge(0,1);
	er4.merge(0,3);
	er4.merge(4,5);
	
	assert(er3.reverse() == er4);
	assert(er3 == er4.reverse());
	}
	
	// Testing + and +=
	{
	cpeq::eq_relation er1(2);
	
	assert(er1 + er1 == cpeq::eq_relation(4));
	
	er1.merge(0,1);
	
	cpeq::eq_relation er2(4);
	
	er2.merge(0,1);
	er2.merge(2,3);
	
	assert(er1 + er1 == er2);
	
	er1 += cpeq::eq_relation(1);
	
	cpeq::eq_relation er3(6);
	
	er3.merge(1,2);
	er3.merge(4,3);
	
	assert(er1.reverse() + er1 == er3);
	
	// Appending an empty ER should have no effect.
	assert(er3 + cpeq::eq_relation() == er3);
	}
	
	// Testing - and -=
	{
	const auto ers_5 = cpeq::enumerate(5), ers_3 = cpeq::enumerate(3);
	
	// The first 5 elements of ers_5 have the same 3-long ER base
	std::size_t i = 0;
	for (; i < 5; ++i)
	{
		assert(ers_5[i] - 2 == ers_3[0]);
	}
	// Then the rest up to index 15
	for (; i < 15; ++i)
	{
		assert(ers_5[i] - 2 == ers_3[1]);
	}
	// 25
	for (; i < 25; ++i)
	{
		assert(ers_5[i] - 2 == ers_3[2]);
	}
	
	// 35
	for (; i < 35; ++i)
	{
		assert(ers_5[i] - 2 == ers_3[3]);
	}
	
	// Rest
	for (; i < 52; ++i)
	{
		assert(ers_5[i] - 2 == ers_3[4]);
	}
	
	// (white box testing)
	// Force a situation where a leader needs to be truncated
	cpeq::eq_relation er1(5);
	
	er1.merge(3,4); // Either 3 or 4 is the leader
	er1.merge(2,3); // 2 looks to either 3 or 4 as the leader
	
	er1 -= 2;
	
	assert(er1 == cpeq::eq_relation(3));
	
	// Removing nothing should have no effect.
	// (random index used)
	assert(ers_5[45] - 0 == ers_5[45]);
	}
	
	// Test fine-ness comparisons
	{
	cpeq::eq_relation er1(5), er2(5);
	
	assert(er1 <=> er2 == std::partial_ordering::equivalent);
	
	er2.merge(3,4);
	
	assert(er1 < er2);
	
	er1.merge(3,4);
	
	assert(er1 <=> er2 == std::partial_ordering::equivalent);
	
	er1.merge(0,1);
	
	assert(er1 > er2);
	
	assert(er1 < cpeq::universal_relation(5));
	assert(er2 < cpeq::universal_relation(5));
	
	er2.merge(2,3);
	
	assert(er1 <=> er2 == std::partial_ordering::unordered);
	}
}
