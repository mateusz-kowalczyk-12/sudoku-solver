#include "Field.h"


Field::Field()
{
	active_number = NONE;

	for (int digit = MIN_DIGIT; digit <= MAX_DIGIT; digit++)
	{
		notes[digit - 1] = false;
	}
}


int Field::get_notes_number()
{
	int notes_number = 0;

	for (int digit = 1; digit <= DIGITS_NUMBER; digit++)
	{
		if (notes[digit - 1])
			notes_number++;
	}

	return notes_number;
}

int Field::get_set_note_digit()
{
	for (int digit = 1; digit <= DIGITS_NUMBER; digit++)
	{
		if (notes[digit - 1])
			return digit;
	}

	return -1;
}


short Field::get_active_number()
{
	return active_number;
}

void Field::set_active_number(int active_number)
{
	this->active_number = active_number;
}

void Field::set_note(int digit, bool value)
{
	notes[digit - 1] = value;
}

bool Field::get_note(int digit)
{
	return notes[digit - 1];
}
