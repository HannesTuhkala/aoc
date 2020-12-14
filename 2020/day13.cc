#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>

int get_time(std::ifstream& source) {
	std::string tempLine;
	std::getline(source, tempLine);

	return stoi(tempLine);
}

std::vector<std::pair<int, unsigned>> get_busses(std::ifstream& source) {
	std::string tempLine;
	std::getline(source, tempLine);
	
	std::vector<std::pair<int, unsigned>> tokens;
	std::istringstream tokenStream{tempLine};
	std::string token;

	unsigned pos{0};
	while (std::getline(tokenStream, token, ',')) {
		if (token == "x") {
			pos++;
			continue;
		}
		
		tokens.push_back(std::make_pair(stoi(token), pos));
		pos++;
	}

	return tokens;
}

bool is_correct_offset(unsigned long long time, int id, int pos) {
	return (time % id) == pos;
}

int main() {
	std::ifstream source{"input13.txt"};

	unsigned long long time = get_time(source);
	std::vector<std::pair<int, unsigned>> tokens = get_busses(source);

	int answer_a{INT_MAX};
	int best_time{INT_MAX};
	for (auto token : tokens) {
		if ((token.first - (time % token.first)) < best_time) {
			best_time = token.first - (time % token.first);
			answer_a = token.first * best_time;
		}

		std::cout << token.first << ":" << token.second << " ";
	}

	std::cout << "ASJDDJAKJKDL" << std::endl;

	//time = 100000000000003;
	bool correct{false};
	/*while (true) {
		if ((time % 19 == 0) && (time % 859) == 19 && (time % 41) == 9 && (time % 23) == 27) {
			unsigned times{1};
			for (auto token : tokens) {
				if (is_correct_offset(time, token.first, token.second)) {
					if (times > 2) {
						std::cout << "Times correct: " << times << std::endl;
					}
					correct = true;
					times++;
					continue;
				} else {
					correct = false;
					break;
				}

			}

			if (correct) break;
		}

		time += 19;
	}*/

	time = 100000000000000 + 29;
	while (true) {
		if ((time % 19 == 0) && (time % 859) == 19) {
			unsigned times{1};
			for (auto token : tokens) {
				if (is_correct_offset(time - 19, token.first, token.second)) {
					if (times > 1) {
						std::cout << "Times correct: " << times << std::endl;
					}
					correct = true;
					continue;
				} else {
					correct = false;
					break;
				}

			}

			if (correct) break;
		}

		time += 859;
	}

	std::cout << "The answer to part a) is: " << answer_a << std::endl;
	std::cout << "The answer to part b) is: " << time << std::endl;
}
