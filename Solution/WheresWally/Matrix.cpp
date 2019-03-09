#include "Matrix.h"

Matrix::Matrix()
{

}

//The overloaded the constructor
Matrix::Matrix(int cols, int rows, double* input) 
{
	Data2d = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		Data2d[i] = new double[cols];
	}

	rowy = rows;
	colx = cols;
	Data1d = input;

	//Loops through the rows and columns and inputs it into a two dimensional array.
	for (int i = 0; i < rowy; i++) 
	{
		for (int j = 0; j < colx; j++) 
		{
			//Finds current position by multiplying I with the column and j is the row position.
			Data2d[i][j] = input[i*colx + j];
		}
	}

	//std::cout << "Matrix Created!" << std::endl;
}

//destructor deletes the two dimensional array
Matrix::~Matrix() 
{
	for (int i = 0; i < rowy; ++i)    
	{
		delete[] Data2d[i];
	}

	delete[] Data2d;
}


//Converts the two dimensional array back to a one dimensional array
double* Matrix::convert1D() 
{
	double* Data1d = new double[colx*rowy];

	int loop = 0;

	for (int i = 0; i < rowy; i++)
	{
		for (int j = 0; j < colx; j++)
		{
			Data1d[loop] = this->Data2d[i][j];
			loop++;
		}
	}

	return Data1d;
}

double* Matrix::get1d()
{
	return Data1d;
}

