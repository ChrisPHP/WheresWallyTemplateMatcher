#pragma once
#ifndef MATCHIMAGE_H
#define MATCHIMAGE_H

#include "details.h"
#include "Matrix.h"

class CompareImg : public Matrix
{
public:
	using Matrix::Matrix;

	//the main function used to compare the image
	double compareImage(double* arrExt);

};
#endif