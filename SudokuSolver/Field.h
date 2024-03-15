#include "Definitions.h"


class Field
{
	int active_number;
	bool notes[DIGITS_NUMBER];


public:

	Field();


	int get_notes_number();

	int get_set_note_digit();


	short get_active_number();

	void set_active_number(int active_number);

	void set_note(int digit, bool value);

	bool get_note(int digit);
};

