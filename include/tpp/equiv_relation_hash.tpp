#pragma once

template<std::unsigned_integral T>
std::size_t er_hash<T>::operator()(const eq_relation<T>& er) const
{
	// This implementation is based off djb2, found at
	// http://www.cse.yorku.ca/~oz/hash.html
	
	// This is simple but decently well performing, you can view
	// a sample of the bucket layout by running the hash test.
	
	std::size_t hash = 5381;
	
	const auto& cgl = er.canonical_group_labeling();
	
	for (const auto c : cgl)
	{
		// Adding 1 here, just in case 0s mess with anything.
		hash = ((hash << 5) + hash) + c + 1; // hash * 33 + c
	}
	
	return hash;
}
