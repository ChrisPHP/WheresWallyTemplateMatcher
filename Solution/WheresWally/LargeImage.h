#pragma once
#ifndef LARGEIMAGE_H
#define LARGEIMAGE_H

#include "Matrix.h"
#include "details.h"

class LargeImage : public Matrix
{
public:
	using Matrix::Matrix;

	//Takes a chunk of the image from the cluttered scene
	double* splitImage(int x, int y);
	//Draws square around the best matching image
	double* highlightBestImage(int x, int y);
	//Smaller square for the other best results
	double* highlightImage(int x, int y);
};
#endif