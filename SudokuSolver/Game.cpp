#include "Game.h"


Game::Game()
{
	Board board;

	while (true)
	{
		std::cout << "Enter:\n";
		std::cout << "- 'n' to solve a new sudoku,\n";
		std::cout << "- 'q' to quit.\n";
		std::cout << "Your choice: ";

		char choice;
		std::cin >> choice;

		if (choice == 'q')
			break;
		if (choice != 'n')
		{
			std::cout << "\nUnknown choice. Please, try again.\n\n";
			continue;
		}

		std::cin >> std::noskipws >> choice; //cin whitespace (endline) to buffer
		board.read_board();

		if (solve_game(board))
		{
			board.print_board();
			std::cout << std::endl;
		}
		else
			std::cout << "\nThis sudoku is unsolvable...\n";
	}
}


bool Game::solve_game(Board& board)
{
	while (true)
	{
		board.set_notes();

		while (true)
		{
			if (board.is_filled())
				return true;

			if (!board.set_known_fields())
			{
				if (board.is_empty_field_without_notes())
					return false;
				else
				{
					int note_to_assume_correct_number = 0;

					while (true)
					{
						Board new_board = board.get_copy();
						Point guessed_field_location = new_board.guess_correct_note(note_to_assume_correct_number);

						if (guessed_field_location.row_number == -2)
							return false;
						if (solve_game(new_board))
						{
							board = new_board;
							return true;
						}
						
						note_to_assume_correct_number++;
					}
				}
			}
			board.print_board();
		}
	}
}