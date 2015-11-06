#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

int main(int argc, char* argv[])
{
	bool recording = false;
	bool startNewRecording = false;
	bool saveSnapshot = false;
	VideoCapture cap;
	cap.open(0);
	//cap.open("http://www.livetrafficlondon.com/VideoClips/16/qvc_16_1_2015_11_03_08_04.mp4?version=635821348279637745"); // open the video camera no. 0
	//cap.open("c:\\Users\\sorin.mecu\\Documents\\Visual Studio 2010\\Projects\\motionTracking\\myVideoWriter\\Debug\\out002.avi"); // open the video camera no. 0
	//cap.open("bouncingBall.avi");
	cv:VideoWriter writer;
	int videoNumber = 0;
	//char* outputFileTemplate = "out%3d.avi";
	std::stringstream filename;
	
	int fourCC_org_codex = CV_FOURCC('D', 'I','V','3');
	int fps = 40;
	cv::Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
		return -1;
	}

	char* windowName = "Webcam Feed";
	namedWindow(windowName,CV_WINDOW_AUTOSIZE); //create a window to display our webcam feed


	while (1) {
		if(startNewRecording == true) {
			startNewRecording = false;
			recording = true;
			videoNumber++;
			filename.str(std::string());
			filename <<"out" << setw(3) << setfill('0') << videoNumber<< ".avi";
			writer = VideoWriter(filename.str(), fourCC_org_codex, fps, frameSize);
			if(!writer.isOpened())
			{
				cout << "CANNOT OPEN FILE FOR WRITE"<<endl;
				return 1;
			}
		}

		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from camera feed

		if (!bSuccess) //test if frame successfully read
		{
			cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
			break;
		}
		if( saveSnapshot) {
			saveSnapshot = false;
			imwrite("snapshot.png", frame);
		}			

		if (recording == true) {
			writer.write(frame);
			putText(frame, "REC", Point(10,10), CV_FONT_HERSHEY_PLAIN, 2, Scalar(12, 12, 255));
		}

		imshow(windowName, frame); //show the frame in "MyVideo" window

		//listen for 10ms for a key to be pressed
		switch((char)waitKey(10)){

		case (char)27:
			//'esc' has been pressed (ASCII value for 'esc' is 27)
			//exit program.
			return 0;

	
		case 'r':
			recording = !recording;
			break;
		case 'n':
			startNewRecording = true;
			break;
		case 's':
			saveSnapshot = true;
			break;
		}
	}

	return 0;

}
////////////////////////////////////////////////////////////////////////////////////////////