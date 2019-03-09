
#include "LargeImage.h"

// Function for taking a chunk out of the Large image
double* LargeImage::splitImage(int x, int y) 
{	
	//create array for the chunk
	double* data = new double[Wally_width*Wally_height];
	int count = 0;

	//loop through the height and width with the current width and height thats beeing looped through
	for (int i = y; i < y + Wally_height; i++)
	{
		for (int j = x; j < x + Wally_width; j++)
		{
			//gets the clustered scene saved in the 2d array and puts it into a 1d array to be compared
			data[count] = this->Data2d[i][j];
			count++;
		}
	}
	//Return it to be compared
	return data;
}

//Function to highlight the best match
double* LargeImage::highlightBestImage(int x, int y)
{
	for(int i = y; i < y + Wally_height; i++)
	{
		for(int j = x; j < x + Wally_width; j++)
		{
			//Create a black box around the match
			if(((i >= y) && (i < y+5)) || ((j >= x) && (j < x+5)) || ((i < y+49) && (i >= y+45)) || ((j < x+36) && (j >= x+32)))
				this->Data2d[i][j] = 0;
		}
	}
	double* output = this->convert1D();

	return output;
}

//Function to highlight the other matches
double* LargeImage::highlightImage(int x, int y)
{
	for (int i = y; i < y + Wally_height; i++)
	{
		for (int j = x; j < x + Wally_width; j++)
		{
			//Create a black box
			if (((i >= y) && (i < y + 3)) || ((j >= x) && (j < x + 3)) || ((i < y + 49) && (i >= y + 46)) || ((j < x + 36) && (j >= x + 33)))
				this->Data2d[i][j] = 0; 
		}
	}

	//Put the change into the array
	double* output = this->convert1D(); 

	return output;
}