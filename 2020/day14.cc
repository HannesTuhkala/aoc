#include <iostream>
#include <fstream>
#include <map>
#include <bitset>

std::string apply_mask(int value, std::string& mask) {
	std::string string_value = std::bitset<36>(value).to_string();

	if (value == 22302) {
		std::cout << string_value << std::endl;
	}

	for (int i{0}; i < 36; i++) {
		if (mask[i] != 'X') {
			string_value[i] = mask[i];
		}
	}

	if (value == 22302) {
		std::cout << string_value << std::endl;
	}

	return string_value;
}

int main() {
	std::ifstream source{"input14.txt"};
	std::map<int, std::string> memory{};
	std::string tempLine{};
	std::string mask{};
	int address{};
	int value{};

	while (std::getline(source, tempLine)) {
		if (tempLine.substr(0, 3) == "mas") {
			mask = tempLine.substr(7, std::string::npos);
		} else {
			address = stoi(tempLine.substr(4, tempLine.find(']', 4) - 4));
			value = stoi(tempLine.substr(tempLine.find("= ", 6) + 2, std::string::npos));
			if (address == 23657) {
				std::cout << value << std::endl;
			}
			memory.insert({address, apply_mask(value, mask)});
		}

		//std::cout << "Current mask is: " << mask << std::endl;
		//std::cout << "Current address is: " << address << " and value is: " << value << std::endl;
	}

	unsigned long long sum{0};
	for (auto&& pair : memory) {
		std::cout << "Current address is: " << pair.first << " and value is: " << pair.second << std::endl;
		sum += std::bitset<36>(pair.second).to_ullong();
	}

	std::cout << "The answer to part a) is: " << sum << std::endl;
}
