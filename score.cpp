	#include "score.h"
    
    const std::string high_scores_filename = "high_scores.txt";
    void Score()
	{
		std::ifstream in_file{ high_scores_filename };
		if (!in_file.is_open()) 
		{
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;	
		}

		std::cout << "High scores table:" << std::endl;

		std::string username;
		int high_score = 0;
	
		while (true) {
			// Сначала прочтите имя пользователя
			in_file >> username;
			// Прочитайте высокий балл далее
			in_file >> high_score;
			// Игнорировать символ конца строки
			in_file.ignore();

			if (in_file.fail()) {
				break;
			}

			// Выведите информацию о рекордах на экран
			
			
			std::cout << username << '\t' << high_score << std::endl;
		}
	}