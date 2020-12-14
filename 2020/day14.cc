#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <bitset>

typedef unsigned long long ullong;

ullong apply_mask_a(ullong value, std::string& mask) {
	std::string string_value = std::bitset<36>(value).to_string();

	for (int i{0}; i < 36; i++) {
		if (mask[i] != 'X') {
			string_value[i] = mask[i];
		}
	}

	return std::bitset<36>(string_value).to_ullong();
}

void address_helper(std::vector<ullong>& addresses, std::queue<int> positions, std::string address) {
	if (!positions.empty()) {
		int position{positions.front()};
		positions.pop();

		address[position] = '0';
		address_helper(addresses, positions, address);

		address[position] = '1';
		address_helper(addresses, positions, address);
	} else {
		addresses.push_back(std::bitset<36>(address).to_ullong());
	}
}

std::vector<ullong> apply_mask_b(ullong address, std::string& mask) {
	std::string string_address = std::bitset<36>(address).to_string();
	std::vector<ullong> addresses{};
	std::queue<int> positions{};

	for (int i{0}; i < 36; i++) {
		if (mask[i] == '0') {
			continue;
		} else if (mask[i] == '1') {
			string_address[i] = '1';
		} else {
			positions.push(i);
		}
	}

	address_helper(addresses, positions, string_address);

	return addresses;
}

ullong sum(std::map<ullong, ullong>& memory) {
	ullong result{0};
	for (std::pair<ullong, ullong>&& pair : memory) {
		result += pair.second;
	}

	return result;
}

template<typename Function>
void apply_mask(std::istream& source, Function f) {
	std::string tempLine{};
	std::string mask{};
	ullong address{};
	ullong value{};

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
	std::map<ullong, ullong> memory_a{};
	std::map<ullong, ullong> memory_b{};

	apply_mask(source, [&memory_a](ullong address, ullong value, std::string mask) -> void {
				memory_a[address] = apply_mask_a(value, mask);
	});

	std::cout << "The answer to part a) is: " << sum(memory_a) << std::endl;

	apply_mask(source, [&memory_b](ullong address, ullong value, std::string mask) -> void {
				std::vector<ullong> addresses = apply_mask_b(address, mask);
				for (ullong address : addresses) {
					memory_b[address] = value;
				}
	});

	std::cout << "The answer to part b) is: " << sum(memory_b) << std::endl;
}
