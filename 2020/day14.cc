#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <bitset>

unsigned long long apply_mask_a(unsigned long long value, std::string& mask) {
	std::string string_value = std::bitset<36>(value).to_string();

	for (int i{0}; i < 36; i++) {
		if (mask[i] != 'X') {
			string_value[i] = mask[i];
		}
	}

	return std::bitset<36>(string_value).to_ullong();
}

void address_helper(std::vector<int>& addresses, std::queue<int> positions, std::string address) {
	if (!positions.empty()) {
		int position{positions.front()};
		positions.pop();

		address[position] = '0';
		address_helper(addresses, positions, address);

		address[position] = '1';
		address_helper(addresses, positions, address);
	} else {
		addresses.push_back(std::bitset<36>(address).to_ulong());
	}
}

std::vector<int> apply_mask_b(int address, std::string& mask) {
	std::string string_address = std::bitset<36>(address).to_string();
	std::vector<int> addresses{};
	std::queue<int> positions{};

	for (int i{0}; i < 36; i++) {
		if (mask[i] == '0') {
			continue;
		} else if (mask[i] == '1') {
			string_address[i] = '1';
		} else {
			string_address[i] = 'X';
			positions.push(i);
		}
	}

	address_helper(addresses, positions, string_address);

	return addresses;
}

unsigned long long sum(std::map<int, unsigned long long>& memory) {
	unsigned long long result{0};
	for (auto&& pair : memory) {
		result += pair.second;
	}

	return result;
}

template<typename Function>
void apply_mask(std::istream& source, Function f) {
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

			// apply masking function
			f(address, value, mask);
		}
	}

	source.clear();
	source.seekg(0, std::ios::beg);
}

int main() {
	std::ifstream source{"input14.txt"};
	std::map<int, unsigned long long> memory{};

	apply_mask(source, [&memory](int address, unsigned long long value, std::string mask) -> void {
				memory[address] = apply_mask_a(value, mask);
	});

	std::cout << "The answer to part a) is: " << sum(memory) << std::endl;

	memory.clear();

	apply_mask(source, [&memory](int address, unsigned long long value, std::string mask) -> void {
				std::vector<int> addresses = apply_mask_b(address, mask);
				for (int address : addresses) {
					memory[address] = value;
				}
	});

	std::cout << "The answer to part b) is: " << sum(memory) << std::endl;
}
