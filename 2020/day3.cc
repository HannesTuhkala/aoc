#include <iostream>
#include <fstream>
#include <vector>

std::size_t find_trees() {
	
}

int main() {
	std::ifstream source{"input3.txt"};
	std::string tempLine{};
	
	int* data = new int[323*31];
	int row{};
	int column{};

	while (std::getline(source, tempLine)) {
		std::cout << "The line is: " << tempLine << std::endl;
		for (char c : tempLine) {
			data[row*31 + column] = static_cast<int>(c == '#');
	
			std::cout << "row: " << row << " and column: " << column << std::endl;
	
			column++;
		}

		row++;
		column = 0;
	}

	int x{};
	int y{};
	
	std::size_t trees_a{};

	while (y <= 323) {
		if (data[y*31 + x]) {
			trees_a++;
		}

		x = (x + 3) % 31;
		y += 1;
	}

	std::cout << "The correct answer for a) is: " << trees_a << std::endl;

	delete data;
}
