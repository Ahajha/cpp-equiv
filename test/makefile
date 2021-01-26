EQUIV=../include/equiv.hpp ../include/equiv.tpp
HASH=../include/er_hash.hpp ../include/er_hash.tpp $(EQUIV)
STORE=../include/er_store.hpp ../include/er_store.tpp $(HASH)

test_er: test_er.cpp $(EQUIV)
test_hash: test_hash.cpp $(HASH)
test_store: test_store.cpp $(STORE)

test_%:
	g++ --std=c++20 -Wall -Wextra -Wpedantic $< -o $@
	./$@
	rm ./$@
