#include <sstream>
#include <string>
#include <iostream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include "HSVMouseSelector.hpp"
#include "utils.h"

using namespace cv;
using namespace ImageUtils;
namespace tracking
{
	HSVHolder hsv;
	//default capture width and height
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS=50;
	//minimum and maximum object area
	const int MIN_OBJECT_AREA = 40*40;
	const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
	//names that will appear at the top of each window
	const string windowName = "Original Image";
	const string windowName1 = "HSV Image";
	const string windowName2 = "Thresholded Image";
	const string windowName3 = "After Morphological Operations";
	const string trackbarWindowName = "Trackbars";


	string intToString(int number){


		std::stringstream ss;
		ss << number;
		return ss.str();
	}

	void on_trackbar( int, void* )
	{//This function gets called whenever a
		// trackbar position is changed
	}

	void createTrackbars(){
		//create window for trackbars


		namedWindow(trackbarWindowName,0);
		//create memory to store trackbar name on window
		char TrackbarName[50];
		sprintf_s(TrackbarName, "H_MIN", hsv.h);
		sprintf_s(TrackbarName, "H_MAX", hsv.H);
		sprintf_s(TrackbarName, "S_MIN", hsv.s);
		sprintf_s(TrackbarName, "S_MAX", hsv.S);
		sprintf_s(TrackbarName, "V_MIN", hsv.v);
		sprintf_s(TrackbarName, "V_MAX", hsv.V);
		//create trackbars and insert them into window
		//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
		//the max value the trackbar can move (eg. H_HIGH), 
		//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
		//                                  ---->    ---->     ---->      
		createTrackbar("H_MIN", trackbarWindowName, &hsv.h, 255, on_trackbar);
		createTrackbar("H_MAX", trackbarWindowName, &hsv.H, 255, on_trackbar);
		createTrackbar("S_MIN", trackbarWindowName, &hsv.s, 255, on_trackbar);
		createTrackbar("S_MAX", trackbarWindowName, &hsv.S, 255, on_trackbar);
		createTrackbar("V_MIN", trackbarWindowName, &hsv.v, 255, on_trackbar);
		createTrackbar("V_MAX", trackbarWindowName, &hsv.V, 255, on_trackbar);


	}

}