#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::ifstream source{"input1.txt"};
	std::string tempLine{};

	std::vector<unsigned int> numbers{};

	while (std::getline(source, tempLine)) {
		numbers.push_back(stoi(tempLine));
	}

	int answer_a{};
	int answer_b{};

	for (auto& elem1: numbers) {
		for (auto& elem2: numbers) {
			if ((elem1 + elem2) == 2020) {
				answer_a = elem1 * elem2;
			}
			for (auto& elem3: numbers) {
				if ((elem1 + elem2 + elem3) == 2020) {
					answer_b = elem1 * elem2 * elem3;
				}
			}
		}
	}

	std::cout << "The correct answer for a) is: " << answer_a << std::endl;
	std::cout << "The correct answer for b) is: " << answer_b << std::endl;
}
