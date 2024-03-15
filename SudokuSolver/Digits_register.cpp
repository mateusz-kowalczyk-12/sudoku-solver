#include "Digits_register.h"


Digits_register::Digits_register()
{
	for (int digit_number = MIN_DIGIT; digit_number <= MAX_DIGIT; digit_number++)
	{
		for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
		{
			digits_in_rows[row_number][digit_number - 1] = false;
		}

		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			digits_in_columns[column_number][digit_number - 1] = false;
		}

		for (int square_number = 0; square_number < DIGITS_NUMBER; square_number++)
		{
			digits_in_squares[square_number][digit_number - 1] = false;
		}
	}
}


Digits_register Digits_register::get_copy()
{
	Digits_register new_digits_register;

	for (int digit_number = MIN_DIGIT; digit_number <= MAX_DIGIT; digit_number++)
	{
		for (int row_number = 0; row_number < ROWS_NUMBER; row_number++)
		{
			new_digits_register.digits_in_rows[row_number][digit_number - 1] = digits_in_rows[row_number][digit_number - 1];
		}

		for (int column_number = 0; column_number < COLUMNS_NUMBER; column_number++)
		{
			new_digits_register.digits_in_columns[column_number][digit_number - 1] = digits_in_columns[column_number][digit_number - 1];
		}

		for (int square_number = 0; square_number < DIGITS_NUMBER; square_number++)
		{
			new_digits_register.digits_in_squares[square_number][digit_number - 1] = digits_in_squares[square_number][digit_number - 1];
		}
	}

	return new_digits_register;
}


void Digits_register::set_digit_presence(int row_number, int column_number, int square_number, int digit, bool presence)
{
	digits_in_rows[row_number][digit - 1] = presence;
	digits_in_columns[column_number][digit - 1] = presence;
	digits_in_squares[square_number][digit - 1] = presence;
}


bool Digits_register::is_digit_in_row(int row_number, int digit)
{
	return digits_in_rows[row_number][digit - 1];
}

bool Digits_register::is_digit_in_column(int column_number, int digit)
{
	return digits_in_columns[column_number][digit - 1];
}

bool Digits_register::is_digit_in_square(int square_number, int digit)
{
	return digits_in_squares[square_number][digit - 1];
}