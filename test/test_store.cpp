#include "../include/er_store.hpp"

int main()
{
	{
	auto id = cpeq::get_id(cpeq::eq_relation{3});
	
	std::cout << id << ": " << cpeq::get_er(id) << std::endl;
	}
	
	{
	const auto& ers_4 = cpeq::enumerate(4);
	
	std::vector<cpeq::default_id_t> ids;
	
	for (const auto& er : ers_4)
	{
		ids.emplace_back(cpeq::get_id(er));
	}
	
	for (const auto id : ids)
	{
		std::cout << id << ": " << cpeq::get_er(id) << '\n';
	}
	}
}
