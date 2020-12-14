#include <iostream>
#include <fstream>
#include <vector>

std::size_t find_occurrences(std::string& str, char c) {
	std::size_t occurrences{0};

	for (char ch : str) {
		if (ch == c) {
			occurrences++;
		}
	}

	return occurrences;
}

bool is_policy_b(std::string& str, std::size_t pos1, std::size_t pos2, char c) {
	std::size_t occurrences{0};

	if (str[pos1-1] == c) {
		occurrences++;
	}

	if (str[pos2-1] == c) {
		occurrences++;
	}

	return occurrences == 1;
}

int main() {
	std::ifstream source{"input2.txt"};
	std::string tempLine{};

	std::size_t colon_pos{};
	std::size_t hyphen_pos{};
	std::size_t space_pos{};

	std::size_t matches_a{};
	std::size_t matches_b{};

	while (std::getline(source, tempLine)) {
		colon_pos = tempLine.find(':', 5);
		hyphen_pos = tempLine.find('-', 1);
		space_pos = tempLine.find(' ', 3);
		std::string password{tempLine.substr(colon_pos + 2, std::string::npos)};
		std::size_t start = static_cast<std::size_t>(stoi(tempLine.substr(0, hyphen_pos)));
		std::size_t end = static_cast<std::size_t>(stoi(tempLine.substr(hyphen_pos + 1, space_pos)));
		char c{tempLine[space_pos + 1]};
		
		std::size_t occurrences = find_occurrences(password, c);

		if (start <= occurrences && occurrences <= end) {
			matches_a++;
		}

		if (is_policy_b(password, start, end, c)) {
			matches_b++;
		}
	}

	std::cout << "The correct answer for a) is: " << matches_a << std::endl;
	std::cout << "The correct answer for b) is: " << matches_b << std::endl;
}
