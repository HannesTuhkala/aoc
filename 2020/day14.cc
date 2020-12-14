#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <bitset>

std::string apply_mask_a(unsigned long long value, std::string& mask) {
	std::string string_value = std::bitset<36>(value).to_string();

	for (int i{0}; i < 36; i++) {
		if (mask[i] != 'X') {
			string_value[i] = mask[i];
		}
	}

	return string_value;
}

std::vector<int> apply_mask_b(int address, std::string& mask) {
	std::string string_address = std::bitset<36>(address).to_string();
	std::vector<int> addresses{};

	for (int i{0}; i < 36; i++) {
		if (mask[i] == 0) {
			continue;
		} else if (mask[i] == 1) {
			string_address[i] = 1;
		} else {
			string_address[i] = 'X';
		}
	}

	return addresses;
}

int main() {
	std::ifstream source{"input14.txt"};
	std::map<int, std::string> memory{};
	std::string tempLine{};
	std::string mask{};
	int address{};
	unsigned long long value{};

	while (std::getline(source, tempLine)) {
		if (tempLine.substr(0, 3) == "mas") {
			mask = tempLine.substr(7, std::string::npos);
		} else {
			address = stoi(tempLine.substr(4, tempLine.find(']', 4) - 4));
			value = stoi(tempLine.substr(tempLine.find("= ", 6) + 2, std::string::npos));
			memory[address] = apply_mask_a(value, mask);
		}
	}

	unsigned long long sum{0};
	for (auto&& pair : memory) {
		sum += std::bitset<36>(pair.second).to_ullong();
	}

	source.clear();
	source.seekg(0, std::ios::beg);

	std::cout << "The answer to part a) is: " << sum << std::endl;
}
