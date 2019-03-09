//Chris Page 17636418
#include "ReadWrite.h"
#include "details.h"
#include "Matrix.h"
#include "LargeImage.h"
#include "CompareImg.h"





// Operator overload to allow std::sort to work on structs of type "comparedImages"
bool operator<(const comparedImages& inputA, const comparedImages& inputB);

void Manipulating(std::vector<comparedImages> &imageDetails, int posx, int posy);
void Manipulating_2(std::vector<comparedImages> &imageDetails, int posx, int posy, bool thread);

LargeImage *ClutteredImage;
Matrix *Wally;

int main(int argc, char *argv[])
{
	bool thread = false;
	int menu;
	std::cout << "Welcome to Wheres Wally Template Matcher!" << std::endl;
	std::cout << "type 1 to search with two threads\nType 2 search on a single thread\nAnd type anything to exit" << std::endl;
	std::cin >> menu;

	switch (menu) {
	case 1: 
		thread = true;
		break;
	case 2: 
		thread = false;
		break;
	default: return 0;
	}

	ReadWrite RW;

	/*=========================Read Text File===========================*/

	double* data = 0; // Container for input data

	//Reads the provided text file and stores in a double
	data = RW.read_text(WallyTxt, Wally_width, Wally_height);	
	//creates a matrix
	Wally = new Matrix(Wally_width, Wally_height, data);	

	//reset the data
	data = 0;

	//read the cluster text file
	data = RW.read_text(ClustTxt, img_width, img_height);
	//Object for the clustered image
	ClutteredImage = new LargeImage(img_width, img_height, data); 




	/*=========================Create Comparison===========================*/
	//store the compared data
	std::vector<comparedImages> imgdetails;
	std::vector<comparedImages> imgdetails_2;

	//Check wether the user chose to use 2 threads or single threaded mode
	if (thread == true)
	{
		//begin a timer for the execution time
		auto t_start = std::chrono::high_resolution_clock::now();

		//Create two threads, one for each function
		std::thread one (Manipulating, std::ref(imgdetails), 0, 0);
		std::thread two (Manipulating_2, std::ref(imgdetails_2), 512, 0, thread);

		//Join the threads so they complete together and prevent the main function from continuing 
		one.join();
		two.join();

		//End the clock and output the execution time in miliseconds 
		auto t_end = std::chrono::high_resolution_clock::now();
		std::cout << "total time required with two threads" << std::endl;
		std::cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms\n";

		//Join the two vectors together
		imgdetails.insert(imgdetails.end(), imgdetails_2.begin(), imgdetails_2.end());
	}
	else {
		//begin a timer for the execution time
		auto t_start = std::chrono::high_resolution_clock::now();

		//Run the function normally
		Manipulating_2(imgdetails,0, 0, thread);

		//End the clock and output the execution time in miliseconds 
		auto t_end = std::chrono::high_resolution_clock::now();
		std::cout << "total time required with a single thread" << std::endl;
		std::cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms\n";
	}


	//sort the vector
	std::sort(imgdetails.begin(), imgdetails.end()); 
	int end = imgdetails.size() - 1;

	//three dimensional array for row, width position and it's similarity
	comparedImages bestMatch = { 0, 0, 0 };
	//last item is the bestmatch
	bestMatch = imgdetails[end]; 

	std::cout << "Closest match found was: " << bestMatch.sim << std::endl;
	//posts the best matches
	std::cout << "The location of the match (" << bestMatch.locx << ", " << bestMatch.locy << ")" << std::endl;

	//loop and print the top 5 results
	if (6 > 0)
	{
		std::cout << "Top 5 N best best matches" << std::endl;
		std::cout << "X and Y coordinates: \Similarity:" << std::endl;
		for (int i = end; i > end - 6; i--)
		{
			std::cout << "(" << imgdetails[i].locx << ", " << imgdetails[i].locy << ") \t Value: " << imgdetails[i].sim << std::endl;
		}
	}

	//Adds a thick black square for the best result
	data = ClutteredImage->highlightBestImage(bestMatch.locx, bestMatch.locy);

	//loop through the 4 other results
	for (int i = end; i > end - 6; i--)
		data = ClutteredImage->highlightImage(imgdetails[i].locx, imgdetails[i].locy); 

	//write the finished results to a pgm file
	RW.write_pgm(OutputPgm, data, img_height, img_width, 255);

	//confirm the file name
	std::cout << "\n" << OutputPgm << " Output!" << std::endl; 

	system("pause");


	/*=========================Free memory=============================*/

	//delete the variables and arrays
	delete[] data;

	delete ClutteredImage;
	delete Wally;

	return 0;

}

//funtion for manipulating data
void Manipulating(std::vector<comparedImages> &imageDetails, int posx, int posy)
{
	int endy = 768;
	int endx = 512;
	bool flagx = true;
	bool flagy = true;
	double sim;
	double* SampledData;

	while (flagy)
	{
		//check if the image has hit the boundary for the height
		if ((posy + 49) >= endy)
		{
			flagy = false;
		}

		//resets the x position
		flagx = true;
		posx = 0;

		while (flagx)
		{
			//check if the image has hit the boundary for the width
			if ((posx + 36) >= endx)
				flagx = false;

			//takes a sample from the clutter then puts it in an object then checks the correlation
			SampledData = ClutteredImage->splitImage(posx, posy);
			CompareImg* subImage = new CompareImg(Wally_width, Wally_height, SampledData);
			sim = subImage->compareImage(Wally->convert1D());

			//Release it from the memory to prevent memory leaks
			delete subImage;

			
			//store in the vector
			imageDetails.push_back({ posx, posy, sim });

			//move the image
			posx += 18;

			//checks if the boundry has been met for the width
			if ((posx + 36) > endx)
			{
				posx = (endx - 36);
			}
		}

		//Move the image
		posy += 24;

		//checks if the boundry has been met for the width
		if ((posy + 49) >= endy)
		{
			posy = (endy - 49);
		}
	}
}

void Manipulating_2(std::vector<comparedImages> &imageDetails, int posx, int posy, bool thread)
{
	int endy = 768;
	int endx = 1024;
	bool flagx = true;
	bool flagy = true;
	double sim;
	double* splitData;
	while (flagy)
	{
		//check if the image has hit the boundary for the height
		if ((posy + 49) >= endy)
			flagy = false;

		//resets the x position
		flagx = true;

		//Checks to see if the function is meant to be multithreaded or not and deciding wether it should searching from the start or from halfway                              
		if (thread == false)
		{
			posx = 0;
		}
		else {
			posx = 512;
		}

		while (flagx)
		{
			//check if the image has hit the boundary for the width
			if ((posx + 36) >= endx)
				flagx = false;

			//takes a sample from the clutter then puts it in an object then checks the correlation
			splitData = ClutteredImage->splitImage(posx, posy);
			CompareImg* subImage = new CompareImg(Wally_width, Wally_height, splitData);
			sim = subImage->compareImage(Wally->convert1D());

			delete subImage;

			//store in the vector
			imageDetails.push_back({ posx, posy, sim });

			//Release it from the memory to prevent memory leaks

			//move the image
			posx += 18;

			//checks if the boundry has been met for the width
			if ((posx + 36) > endx)
				posx = (endx - 36);
		}

		//Move the image
		posy += 24;

		//checks if the boundry has been met for the width
		if ((posy + 49) >= endy)
			posy = (endy - 49);

	}
}

// Operator overload to allow std::sort to work on structs of type "comparedImages"
bool operator<(const comparedImages& inputA, const comparedImages& inputB) 
{
	return inputA.sim < inputB.sim;
}
