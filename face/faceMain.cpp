#include <string>
#include <iostream>
#include <sstream>
#include <opencv\cv.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace std;
using namespace cv;

const string windowNameShowCaptue = "Image feed";
const string face_cascade_name = "haarcascade_frontalface_default.xml";
const string eyes_cascade_name = "haarcascade_eye.xml";
const string glasses_file = "glasses.png";
const int face_detection_size = 90;
void overlapImage(Mat under, Mat upper);

int doTheStuff(VideoCapture cap)
{
	Mat source, source_out;
	Mat graySource;
	Mat originalGlasses = imread(glasses_file, -1);
	Mat glasses;
	vector<Rect> faces;
	
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	
	for(;;)
	{
		bool showImage = false;
		cap.read(source);
		cvtColor(source, source_out, CV_BGR2BGRA);
		cvtColor(source, graySource, CV_BGR2GRAY);
		equalizeHist(graySource, graySource);
		face_cascade.detectMultiScale(graySource, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(face_detection_size, face_detection_size));
		if(1 > faces.size())
		{
			cout << "No face found"<< endl;
			continue;
		}
		for(vector<Rect>::size_type i=0; i< faces.size(); i++)
		{
			Mat face = graySource(faces[i]);
			vector<Rect> eyes;
			eyes_cascade.detectMultiScale(face, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30));
			if(eyes.size() != 2)
			{
				cout << " missed eyes" << endl;
				continue;
			}
			vector<Point> allCorners;
			for(vector<Rect>::size_type e=0; e< eyes.size(); e++)
			{
				allCorners.push_back(eyes[e].tl());
				allCorners.push_back(eyes[e].br());
			}
			Rect glassesSize = boundingRect(allCorners);
			resize(originalGlasses, glasses, glassesSize.size());
			Rect properCoordinates(faces[i].tl()+glassesSize.tl(), glassesSize.size());
			Mat sourceEyes = source_out(properCoordinates);
			overlapImage(sourceEyes, glasses);
			showImage = true;
		}
		if(showImage)
			imshow(windowNameShowCaptue, source_out);
		switch ((char)waitKey(10)) {
		case 'q':
		case (char)27:
			return 0;
		}
	}
}

void overlapImage(Mat under, Mat upper)
{
	//addWeighted(under, .5, upper, 1., 0., under); 
	try
	{
		//assert(under.size == upper	.size);
		for(int i=0, width = under.rows; i< width; i++)
			for(int j=0, height = under.cols; j < height; j++)
			{
				Vec4b pixel = upper.at<Vec4b>(i,j);
				if(pixel[3] == 0)
					continue;
				under.at<Vec4b>(i,j) = pixel;
			}
	}
	catch(exception ex)
	{
		cout << ex.what() << endl;
	}
}

int main(void)
{
	VideoCapture cap;
	cap.open(0);
	if( !cap.isOpened())
	{
		cout << "Unable to get webcam feed!" << endl;
		return 0;
	}
	doTheStuff(cap);
	cap.release();
	destroyAllWindows();
}