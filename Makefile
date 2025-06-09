CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = tests
TEST_SOURCE = test.cpp

all: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(TEST_FLAGS)

test: $(TEST_TARGET)
	./$<

clean:
	rm -f $(TEST_TARGET)
