#pragma once

template<std::unsigned_integral T, std::unsigned_integral id_t>
class _er_storage
{
	static inline std::vector<eq_relation<T>> _ers{};
	static inline std::unordered_map<eq_relation<T>,id_t,er_hash<T>> _ids{};
	
	friend id_t get_id<T,id_t>(const eq_relation<T>&);
	friend const eq_relation<T>& get_er<T,id_t>(id_t);
	friend void clear_storage<T,id_t>();
};

template<std::unsigned_integral T = default_T, std::unsigned_integral id_t = default_id_t>
id_t get_id(const eq_relation<T>& er)
{
	using store = _er_storage<T,id_t>;
	const auto search = store::_ids.find(er);
	
	if (search == store::_ids.end())
	{
		// Not found
		store::_ids[er] = store::_ers.size();
		store::_ers.emplace_back(er);
		return store::_ers.size() - 1;
	}
	else
	{
		// Found
		return search->second;
	}
}

template<std::unsigned_integral T = default_T, std::unsigned_integral id_t = default_id_t>
const eq_relation<T>& get_er(id_t id)
{
	return _er_storage<T,id_t>::_ers[id];
}

template<std::unsigned_integral T = default_T, std::unsigned_integral id_t = default_id_t>
void clear_storage()
{
	_er_storage<T,id_t>::_ers.clear();
	_er_storage<T,id_t>::_ids.clear();
}
