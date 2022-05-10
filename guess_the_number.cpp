#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Score.h"


const std::string high_scores_filename = "high_scores.txt";

int main(int argc, char** argv) {

	// argc - это подсчет аргументов
	// Но есть некоторая деталь - ОС всегда передает один системный аргумент - имя исполняемого файла
	// Итак, если приложение было выполнено вообще без аргументов, argc будет по-прежнему == 1

	// Давайте напечатаем этот аргумент
	if (argc > 0) {
		std::cout << "We have at least one argument!" << std::endl;
		std::cout << "argv[0] = " << argv[0] << std::endl;
	}

	int parameter_value = 0;
	// Чтобы проверить - использует ли print какой-либо другой аргумент, мы должны проверить, является ли argc >= 2
	if (argc >= 2) 
	{
		std::cout << "We have one more argument!" << std::endl;
		std::cout << "argv[1] = " << argv[1] << std::endl;

		std::string arg1_value{ argv[1] };
		if (arg1_value == "-max") {
			std::cout << "-parameter argument was detected!" << std::endl;

			// Мы обнаружили аргумент '-max'. И мы ожидаем, что после этого аргумента будет значение:
			
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;
				return -1;
			}
			// Нам нужно разобрать строку до значения int
			parameter_value = std::stoi(argv[2]);
			std::cout << "The '-parameter' value = " << parameter_value << std::endl;
		}
		std::string arg2_value{ argv[1] };
		if (arg2_value == "-table") 
			{
				std::cout << "-table argument was detected!" << std::endl;

				// Мы обнаружили аргумент '-table'. И мы ожидаем, что после этого аргумента будет значение:
			
				Score();
				return 0;

		
			}
	
	}
	

	// Имя
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	const int max_value = 100;
	std::srand(std::time(nullptr)); // используется текущее время в качестве начального значения для генератора случайных чисел
	int random_value = 0;
	if (parameter_value != 0)
	{	
		random_value = std::rand() % parameter_value;
	}
	else
	{	
		random_value = std::rand() % max_value;
	}
	std::cout << random_value << std::endl;

	const int target_value = random_value;
	int current_value = 0;
	bool not_win = true;

	std::cout << "Enter your guess:" << std::endl;
	int count = 0;
	do {
		std::cin >> current_value;
		
		if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
			count++;
		}
		else if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
			count++;
		}
		else {
			std::cout << "you win! attempts = " << count << std::endl;
			break;
		}

	} while (true);

	// Получите последний высокий балл
	std::cout << "Your high score:" << std::endl;
	int attempts_count = count;
	if (std::cin.fail()) {
		std::cout << "Bad value!" << std::endl;
		return -1;
	}

	// Запишите новый высокий балл в таблицу рекордов
	{
		// Мы должны открыть выходной файл в режиме добавления - мы не хотим
		// чтобы стереть предыдущие результаты.
		std::ofstream out_file{ high_scores_filename, std::ios_base::app };
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		// Добавьте новые результаты в таблицу:
		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	} 
	// конец оценки здесь просто для того, чтобы отметить конец логического блока кода

	// Прочитайте файл с высоким баллом и распечатайте все результаты
	Score();
	return 0;
}