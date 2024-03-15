#include "Definitions.h"


class Digits_register
{
	bool digits_in_rows[ROWS_NUMBER][DIGITS_NUMBER];
	bool digits_in_columns[COLUMNS_NUMBER][DIGITS_NUMBER];
	bool digits_in_squares[DIGITS_NUMBER][DIGITS_NUMBER];


public:

	Digits_register();


	Digits_register get_copy();


	void set_digit_presence(int row_number, int column_number, int square_number, int digit, bool presence);


	bool is_digit_in_row(int row_number, int digit);

	bool is_digit_in_column(int column_number, int digit);
	
	bool is_digit_in_square(int square_number, int digit);
};