#pragma once
#include <string>
#include "HSVMouseSelector.hpp"

using namespace std;
using namespace ImageUtils;

namespace tracking
{
	extern HSVHolder hsv;
//default capture width and height
	extern const int FRAME_WIDTH;
	extern const int FRAME_HEIGHT ;
	//max number of objects to be detected in frame
	extern const int MAX_NUM_OBJECTS;
	//minimum and maximum object area
	extern const int MIN_OBJECT_AREA ;
	extern const int MAX_OBJECT_AREA ;
	//names that will appear at the top of each window
	extern const string windowName ;
	extern const string windowName1 ;
	extern const string windowName2 ;
	extern const string windowName3 ;
	extern const string trackbarWindowName ;

	string intToString(int);
	void createTrackbars(void);
}