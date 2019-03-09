#include "CompareImg.h"

//Compares the functions and gets the similarity
double CompareImg::compareImage(double* arrExt)
{
	double sim;
	int ArraySize = Wally_width * Wally_height;

	double* ar1 = arrExt;
	double* ar2 = this->Data1d;

	double m1 = 0;
	double m2 = 0;

	// Find the sum of each array and store them temporarily in the mean variables
	for (int i = 0; i < ArraySize; i++) {
		m1 += ar1[i]; 
		m2 += ar2[i];
	}

	//get the mean by dividing the total number of elements
	m1 = m1 / ArraySize;
	m2 = m2 / ArraySize;

	//deduct the mean away from the two arrays
	for (int i = 0; i < ArraySize; i++)
	{
		ar1[i] -= m1;
		ar2[i] -= m2;
	}


	double top = 0; double btmLeft = 0; double btmRight = 0; double btm;

	//Find the correlation
	for (int i = 0; i < ArraySize; i++)
	{
		top += (ar1[i] * ar2[i]);
		btmLeft += (ar1[i] * ar1[i]);
		btmRight += (ar2[i] * ar2[i]);
	}

	//square root the bottom half of the equation
	btm = btmLeft * btmRight;
	btm = sqrt(btm);

	sim = top / btm; 

	//return the similarity
	return sim;
}