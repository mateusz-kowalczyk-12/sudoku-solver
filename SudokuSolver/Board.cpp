#include "Board.h"


Board::Board()
{}


Field* Board::operator[](int column_number)
{
	return fields[column_number];
}

Board Board::get_copy()
{
	Board new_board;

	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			new_board.fields[row_number][column_number] = fields[row_number][column_number];
		}
	}

	new_board.digits_register = digits_register.get_copy();

	return new_board;
}


void Board::set_notes()
{
	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			if (fields[row_number][column_number].get_active_number() == NONE)
				set_field_notes(row_number, column_number);
		}
	}
}

void Board::reset_notes_after_field_set(int set_field_row_number, int set_field_column_number, int set_field_digit)
{
	int set_field_square_number = get_square_number(set_field_row_number, set_field_column_number);

	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			if (row_number == set_field_row_number ||
				column_number == set_field_column_number ||
				get_square_number(row_number, column_number) == set_field_square_number)
			{
				fields[row_number][column_number].set_note(set_field_digit, false);
			}
		}
	}
}

bool Board::set_known_fields()
{
	bool any_field_set = false;

	set_fields_with_single_note(any_field_set);

	set_fields_with_only_note_in_row(any_field_set);
	set_fields_with_only_note_in_column(any_field_set);
	set_fields_with_only_note_in_square(any_field_set);

	return any_field_set;
}


void Board::set_fields_with_single_note(bool& any_field_set)
{
	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			if (fields[row_number][column_number].get_active_number() != NONE)
				continue;

			if (fields[row_number][column_number].get_notes_number() == 1)
			{
				set_field_with_single_note(row_number, column_number);
				any_field_set = true;
			}
		}
	}
}

void Board::set_fields_with_only_note_in_row(bool& any_field_set)
{
	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int digit = 1; digit <= DIGITS_NUMBER; digit++)
		{
			if (get_notes_in_row_number(row_number, digit) == 1)
			{
				set_field_with_only_note_in_row(row_number, digit);
				any_field_set = true;
			}
		}
	}
}

void Board::set_fields_with_only_note_in_column(bool& any_field_set)
{
	for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
	{
		for (int digit = 1; digit <= DIGITS_NUMBER; digit++)
		{
			if (get_notes_in_column_number(column_number, digit) == 1)
			{
				set_field_with_only_note_in_column(column_number, digit);
				any_field_set = true;
			}
		}
	}
}

void Board::set_fields_with_only_note_in_square(bool& any_field_set)
{
	for (int square_number = 0; square_number < DIGITS_NUMBER; square_number++)
	{
		for (int digit = 1; digit <= DIGITS_NUMBER; digit++)
		{
			if (get_notes_in_square_number(square_number, digit) == 1)
			{
				set_field_with_only_note_in_square(square_number, digit);
				any_field_set = true;
			}
		}
	}
}

Point Board::guess_correct_note(int note_to_assume_correct_number)
{
	if (note_to_assume_correct_number == -1)
		return Point(-1, -1);  // no note should be assumed correct

	int current_note_number = -1;

	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			for (int digit = MIN_DIGIT; digit <= MAX_DIGIT; digit++)
			{
				if (fields[row_number][column_number].get_note(digit) && fields[row_number][column_number].get_active_number() == NONE)
				{
					current_note_number++;
					if (current_note_number == note_to_assume_correct_number)
					{
						int square_number = get_square_number(row_number, column_number);

						fields[row_number][column_number].set_active_number(digit);
						digits_register.set_digit_presence(row_number, column_number, square_number, digit, true);
						reset_notes_after_field_set(row_number, column_number, digit);

						return Point(row_number, column_number);
					}
				}
			}
		}
	}

	return Point(-2, -2);  // note number out of range
}

void Board::unguess_correct_note(Point location)
{
	int square_number = get_square_number(location.row_number, location.column_number);
	int prev_active_number = fields[location.row_number][location.column_number].get_active_number();

	fields[location.row_number][location.column_number].set_active_number(NONE);
	digits_register.set_digit_presence(location.row_number, location.column_number, square_number, prev_active_number, false);
}


void Board::set_field_notes(int row_number, int column_number)
{
	int square_number = get_square_number(row_number, column_number);

	for (int digit = MIN_DIGIT; digit <= MAX_DIGIT; digit++)
	{
		if (!digits_register.is_digit_in_row(row_number, digit) &&
			!digits_register.is_digit_in_column(column_number, digit) &&
			!digits_register.is_digit_in_square(square_number, digit))
		{
			fields[row_number][column_number].set_note(digit, true);
		}
	}
}

int Board::get_notes_in_row_number(int row_number, int note_digit)
{
	int notes_in_row_number = 0;

	for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
	{
		if (fields[row_number][column_number].get_active_number() != NONE)
			continue;

		if (fields[row_number][column_number].get_note(note_digit))
			notes_in_row_number++;
	}

	return notes_in_row_number;
}

int Board::get_notes_in_column_number(int column_number, int note_digit)
{
	int notes_in_column_number = 0;

	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		if (fields[row_number][column_number].get_active_number() != NONE)
			continue;

		if (fields[row_number][column_number].get_note(note_digit))
			notes_in_column_number++;
	}

	return notes_in_column_number;
}

int Board::get_notes_in_square_number(int square_number, int note_digit)
{
	int notes_in_square_number = 0;

	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			if (fields[row_number][column_number].get_active_number() != NONE)
				continue;

			if (get_square_number(row_number, column_number) == square_number)
			{
				if (fields[row_number][column_number].get_note(note_digit))
					notes_in_square_number++;
			}
		}
	}

	return notes_in_square_number;
}

void Board::set_field_with_single_note(int row_number, int column_number)
{
	int digit_to_set = fields[row_number][column_number].get_set_note_digit();
	int square_number = get_square_number(row_number, column_number);

	fields[row_number][column_number].set_active_number(digit_to_set);
	digits_register.set_digit_presence(row_number, column_number, square_number, digit_to_set, true);

	reset_notes_after_field_set(row_number, column_number, digit_to_set);
}

void Board::set_field_with_only_note_in_row(int row_number, int digit)
{
	for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
	{
		if (fields[row_number][column_number].get_active_number() != NONE)
			continue;

		if (fields[row_number][column_number].get_note(digit))
		{
			fields[row_number][column_number].set_active_number(digit);
			digits_register.set_digit_presence(row_number, column_number, get_square_number(row_number, column_number), digit, true);

			reset_notes_after_field_set(row_number, column_number, digit);
		}
	}
}

void Board::set_field_with_only_note_in_column(int column_number, int digit)
{
	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		if (fields[row_number][column_number].get_active_number() != NONE)
			continue;

		if (fields[row_number][column_number].get_note(digit))
		{
			fields[row_number][column_number].set_active_number(digit);
			digits_register.set_digit_presence(row_number, column_number, get_square_number(row_number, column_number), digit, true);

			reset_notes_after_field_set(row_number, column_number, digit);
		}
	}
}

void Board::set_field_with_only_note_in_square(int square_number, int digit)
{
	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			if (get_square_number(row_number, column_number) == square_number)
			{
				if (fields[row_number][column_number].get_active_number() != NONE)
					continue;

				if (fields[row_number][column_number].get_note(digit))
				{
					fields[row_number][column_number].set_active_number(digit);
					digits_register.set_digit_presence(row_number, column_number, get_square_number(row_number, column_number), digit, true);

					reset_notes_after_field_set(row_number, column_number, digit);
				}
			}
		}
	}
}


void Board::read_board()
{
	std::cout << "Enter the board file name:\n";

	std::string filename;
	std::cin >> filename;

	std::fstream file(filename, std::ios::in);

	char buffer;
	std::cin >> std::noskipws >> buffer;  //cin whitespace (endline) to buffer

	if (!file.good())
		exit(0);

	char field_value;

	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			file >> std::noskipws >> field_value;

			if (field_value != ' ')
			{
				int digit = field_value - '0';

				if ((digit >= MIN_DIGIT && digit <= MAX_DIGIT))
				{
					fields[row_number][column_number].set_active_number(digit);
					digits_register.set_digit_presence(row_number, column_number, get_square_number(row_number, column_number), digit, true);
				}
				else
				{
					std::cout << "Tried to set incorrect active_number: " << digit << std::endl;
				}
			}
		}

		file >> std::noskipws >> field_value; //New line character
	}

	print_board();
}

void Board::print_board()
{
	std::cout << std::endl;

	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		print_horizontal_lines(row_number);

		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			int active_number = fields[row_number][column_number].get_active_number();

			if (active_number != NONE)
				std::cout << active_number;
			else
				std::cout << " ";

			print_vertical_lines(column_number);
		}

		std::cout << std::endl;
	}
}


void Board::print_horizontal_lines(int row_number)
{
	if (row_number % 3 == 0 && row_number != 0)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			std::cout << '-';

			print_vertical_lines(column_number);
		}

		std::cout << std::endl;
	}
}

void Board::print_vertical_lines(int column_number)
{
	if (column_number % 3 == 2 && column_number < COLUMNS_NUMBER - 1)
		std::cout << '|';
}

int Board::get_square_number(int row_number, int column_number)
{
	int row_number_div_3 = row_number / 3;

	return 3 * row_number_div_3 + column_number / 3;
}

bool Board::is_filled()
{
	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			if (fields[row_number][column_number].get_active_number() == NONE)
				return false;
		}
	}

	return true;
}

bool Board::is_empty_field_without_notes()
{
	for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
	{
		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			if (fields[row_number][column_number].get_active_number() != NONE)
				continue;

			bool any_note_active = false;

			for (int digit = 1; digit <= DIGITS_NUMBER; digit++)
			{
				if (fields[row_number][column_number].get_note(digit))
				{
					any_note_active = true;
					break;
				}
			}

			if (!any_note_active)
				return true;
		}
	}

	return false;
}
