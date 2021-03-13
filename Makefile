CXX = clang++
CPPFLAGS = -std=c++20 -Wall -Wextra

TEST = test_bin

all: $(TEST)

TEST_SRC = test/test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

$(TEST): $(TEST_OBJ)
	$(CXX) $(CPPFLAGS) $(TEST_OBJ) -o $(TEST)

clean:
	rm -f $(TEST) $(TEST_OBJ)