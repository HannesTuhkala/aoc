#include <iostream>

const int turns_a{2020};
const int turns_b{30000000};

int main() {
	int input[]{6, 13, 1, 15, 2, 0};

	static int memory[turns_b]{};
	int turn{1};

	for (; turn < std::size(input); turn++) {
		memory[input[turn - 1]] = turn;
	}

	int current_number{0};

	for (; turn < turns_b; turn++) {
		if (memory[current_number] == 0) {
			memory[current_number] = turn;
			current_number = 0;
		} else {
			int old_number{current_number};
			current_number = turn - memory[current_number];
			memory[old_number] = turn;
		}
	}
	
	std::cout << "The answer to part b) is: " << current_number << std::endl;
}
