#pragma once
#ifndef READWRITE_H
#define READWRITE_H

#include "details.h"

class ReadWrite
{
public:
	//Function for reading the Txt file
	double* read_text(char *fileName, int sizeR, int sizeC);
	//Function for creating a pgm file
	void write_pgm(char *filename, double *data, int sizeR, int sizeC, int Q);
};
#endif