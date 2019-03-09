#pragma once

//All the required include files 
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <math.h>
#include <algorithm>
#include <thread>

//defines for the height and width
#define Wally_width 36
#define Wally_height 49
#define img_width 1024
#define img_height 768

//defines for file names
#define WallyTxt "Wally_grey.txt"
#define ClustTxt "Cluttered_scene.txt"
#define OutputPgm "Matches.pgm"

//details for the matched image like the coordinates and similarity
struct comparedImages
{
	int locx;
	int locy;
	double sim;
};
