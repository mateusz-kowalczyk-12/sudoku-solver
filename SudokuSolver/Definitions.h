#include <iostream>
#include <string>
#include <fstream>


//Digits data:

#define DIGITS_NUMBER 9

#define MIN_DIGIT 1
#define MAX_DIGIT 9

#define NONE 0


//Fields data:

#define ROWS_NUMBER 9
#define COLUMNS_NUMBER 9

#ifndef STRUCT_POINT
#define STRUCT_POINT
struct Point
{
	int row_number;
	int column_number;


	Point(int row_number, int column_number)
	{
		this->row_number = row_number;
		this->column_number = column_number;
	}
};
#endif