#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {

	const std::string high_scores_filename = "high_scores.txt";

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	const int max_value = 100;
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int random_value = std::rand() % 100;
	std::cout << "The figure is hidden: " << random_value << std::endl;

	const int target_value = random_value;
	int current_value = 0;
	bool not_win = true;

	std::cout << "Enter your guess:" << std::endl;
	int count = 0;
	do {
		std::cin >> current_value;
		
		if (current_value < target_value) {
			std::cout << "less than " << current_value << std::endl;
			count++;
		}
		else if (current_value > target_value) {
			std::cout << "greater than " << current_value << std::endl;
			count++;
		}
		else {
			std::cout << "you win! attempts = " << count << std::endl;
			break;
		}

	} while (true);

	// Get the last high score
	std::cout << "Your high score:" << std::endl;
	int attempts_count = count;
	if (std::cin.fail()) {
		std::cout << "Bad value!" << std::endl;
		return -1;
	}

	// Write new high score to the records table
	{
		// We should open the output file in the append mode - we don't want
		// to erase previous results.
		std::ofstream out_file{ high_scores_filename, std::ios_base::app };
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		// Append new results to the table:
		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	} // end of score here just to mark end of the logic block of code

	// Read the high score file and print all results
	{
		std::ifstream in_file{ high_scores_filename };
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		std::cout << "High scores table:" << std::endl;

		std::string username;
		int high_score = 0;
		while (true) {
			// Read the username first
			in_file >> username;
			// Read the high score next
			in_file >> high_score;
			// Ignore the end of line symbol
			in_file.ignore();

			if (in_file.fail()) {
				break;
			}

			// Print the information to the screen
			std::cout << username << '\t' << high_score << std::endl;
		}
	}
	return 0;
}