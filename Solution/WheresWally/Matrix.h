#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "details.h"

class Matrix
{
public:

	Matrix();

	//Overloaded constructor
	Matrix(int rows, int cols, double* data);

	~Matrix();

	//Makes the two dimensional array into a one dimensional array
	double* convert1D(); 

	double* get1d();


protected:
	double** Data2d;
	double* Data1d;
	int rowy;
	int colx;
};

#endif