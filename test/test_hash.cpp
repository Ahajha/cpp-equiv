#include "../include/equiv.hpp"
#include "../include/er_hash.hpp"
#include <iostream>
#include <cassert>
#include <unordered_set>

int main()
{
	std::unordered_set<cpeq::eq_relation<uint16_t>,cpeq::er_hash<uint16_t>> set;
	
	for (unsigned i = 0; i < 7; ++i)
	{
		const auto ers = cpeq::enumerate(i);
		
		for (const auto& er : ers)
		{
			set.emplace(er);
		}
		
		for (unsigned i = 0; i < set.bucket_count(); ++i)
		{
			std::cout << set.bucket_size(i) << '\n';
		}
		
		std::cout << '\n';
	}
}
