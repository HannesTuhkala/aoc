#include <iostream>

int main() {
	int input[]{6, 13, 1, 15, 2, 0};

	static int memory[30000000]{};
	int turn{1};

	for (int i{0}; i < 6; i++) {
		memory[input[i]] = turn;
		turn++;
	}

	int current_number{0};

	for (; turn < 30000000; turn++) {
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
