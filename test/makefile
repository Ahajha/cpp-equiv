all: test_er test_hash test_store

test_%: test_%.cpp
	g++ --std=c++20 -Wall -Wextra -Wpedantic -I ../include $< -o $@
	./$@
	rm ./$@
