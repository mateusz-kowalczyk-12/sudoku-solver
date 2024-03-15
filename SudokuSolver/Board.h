#include "Field.h"
#include "Digits_register.h"


class Board
{
	Field fields[ROWS_NUMBER][COLUMNS_NUMBER];

	Digits_register digits_register;

public:

	Board();


	Field* operator[](int column_number);

	Board get_copy();


	void set_notes();

	void reset_notes_after_field_set(int set_field_row_number, int set_field_column_number, int set_field_digit);

	bool set_known_fields();


	void set_fields_with_single_note(bool& any_field_set);

	void set_fields_with_only_note_in_row(bool& any_field_set);

	void set_fields_with_only_note_in_column(bool& any_field_set);

	void set_fields_with_only_note_in_square(bool& any_field_set);


	void set_field_notes(int row_number, int column_number);

	int get_notes_in_row_number(int row_number, int note_digit);

	int get_notes_in_column_number(int column_number, int note_digit);

	int get_notes_in_square_number(int square_number, int note_digit);

	void set_field_with_single_note(int row_number, int column_number);

	void set_field_with_only_note_in_row(int row_number, int digit);

	void set_field_with_only_note_in_column(int column_number, int digit);

	void set_field_with_only_note_in_square(int square_number, int digit);

	Point guess_correct_note(int note_to_assume_correct_number);

	void unguess_correct_note(Point location);


	void read_board();

	void print_board();


	void print_horizontal_lines(int row_number);

	void print_vertical_lines(int column_number);

	int get_square_number(int row_number, int column_number);

	bool is_filled();

	bool is_empty_field_without_notes();

};

