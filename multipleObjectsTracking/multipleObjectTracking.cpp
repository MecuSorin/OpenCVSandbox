#include "multipleObjectTracking.h"

#include <vector>

using namespace cv;
using namespace ImageUtils;
//initial min and max HSV filter values.
//these will be changed using trackbars
namespace tracking
{
	void drawObject(vector<TrackedObject> objs,Mat &frame){
		for(int i=0; i<objs.size(); i++) {
			TrackedObject obj = objs[i];
			circle(frame, obj.getPosition(),10, Scalar(0,0,255));
			cv::putText(frame, obj.getPositionAsString(), obj.getPosition()+Point(0,20),1,1,Scalar(0,255,0));
		}
	}

	void morphOps(Mat &thresh){
		//create structuring element that will be used to "dilate" and "erode" image.
		//the element chosen here is a 3px by 3px rectangle
		Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
		//dilate with larger element so make sure object is nicely visible
		Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));
		erode(thresh,thresh,erodeElement);
		erode(thresh,thresh,erodeElement);
		dilate(thresh,thresh,dilateElement);
		dilate(thresh,thresh,dilateElement);
	}

	void trackFilteredObject(Mat threshold,Mat HSV, Mat &cameraFeed){

		int x,y;
		
		vector<TrackedObject> trackedObjs;

		Mat temp;
		threshold.copyTo(temp);
		//these two vectors needed for output of findContours
		vector< vector<Point> > contours;
		vector<Vec4i> hierarchy;
		//find contours of filtered image using openCV findContours function
		findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
		//use moments method to find our filtered object
		double refArea = 0;
		bool objectFound = false;
		if (hierarchy.size() > 0) {
			int numObjects = hierarchy.size();
			//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
			if(numObjects<MAX_NUM_OBJECTS){
				for (int index = 0; index >= 0; index = hierarchy[index][0]) {

					Moments moment = moments((cv::Mat)contours[index]);
					double area = moment.m00;

					//if the area is less than 20 px by 20px then it is probably just noise
					//if the area is the same as the 3/2 of the image size, probably just a bad filter
					//we only want the object with the largest area so we safe a reference area each
					//iteration and compare it to the area in the next iteration.
					if(area>MIN_OBJECT_AREA){
						TrackedObject trackedObj;
						trackedObj.SetPosition(moment.m10/area, moment.m01/area);
						trackedObjs.push_back(trackedObj);
						objectFound = true;
					}
				}
				//let user know you found an object
				if(objectFound ==true){
					//draw object location on screen
					drawObject(trackedObjs,cameraFeed);}

			}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
		}
	}

	int main(int argc, char* argv[])
	{
		//if we would like to calibrate our filter values, set to true.
		bool calibrationMode = true;

		//Matrix to store each frame of the webcam feed
		Mat cameraFeed;
		Mat threshold;
		Mat HSV;
		vector<HSVHolder> knownColors;
		ColorFormats formats;
		if(calibrationMode){
			//create slider bars for HSV filtering
			createTrackbars();
		}
		//video capture object to acquire webcam feed
		VideoCapture capture;
		//open capture object at location zero (default location for webcam)
		capture.open(0);
		//set height and width of capture frame
		capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

		cv::namedWindow(windowName);
		capture.read(cameraFeed);
		HSVMouseSelector hsvMouseSelector(&hsv, &cameraFeed);
		setMouseCallback(windowName, ImageUtils::MouseCallback, &hsvMouseSelector);
		//start an infinite loop where webcam feed is copied to cameraFeed matrix
		//all of our operations will be performed within this loop
		while(1){
			//store image to matrix
			capture.read(cameraFeed);
			//convert frame from BGR to HSV colorspace
			cvtColor(cameraFeed,HSV, formats.CurrentColorFormatConvertor());
			hsvMouseSelector.UpdateFrame(&HSV);
			if(calibrationMode==true){
				//if in calibration mode, we track objects based on the HSV slider values.
				inRange(HSV, hsv.ToMin(), hsv.ToMax(), threshold);
				morphOps(threshold);
				trackFilteredObject(threshold,HSV,cameraFeed);
				
				imshow(windowName1, HSV);
				imshow(windowName2,threshold);
			} 
			else
			{
				destroyWindow(windowName1);
				destroyWindow(windowName2);
				destroyWindow(trackbarWindowName);

				for(int i=0; i<knownColors.size(); i++)
				{
					HSVHolder color = knownColors[i];
					inRange(HSV, color.ToMin(), color.ToMax(), threshold);
					morphOps(threshold);
					trackFilteredObject(threshold,HSV,cameraFeed);
				}
			}

			//show frames 
			//imshow(windowName2,threshold);
			putText(cameraFeed, formats.CurrentColorFormat().getText() ,Point(0,430),1,2,Scalar(0,0,255),2);
			imshow(windowName,cameraFeed);
			//imshow(windowName1,HSV);


			//delay 30ms so that screen can refresh.
			//image will not appear without this waitKey() command
			switch(	waitKey(30)) {
			case 27: return 0;
			case 97:
				knownColors.push_back(hsv);
				cout<<hsv.ToString();
					break;
			
			case 99:
				calibrationMode = !calibrationMode;
				cout << "calibrationmode:" << calibrationMode << endl;
				break;
			case 115:
				for(int i=0; i<knownColors.size(); i++){
					cout<< "Color " << setw(2) << setfill(' ') << i+1 << ":" << endl;
					cout << knownColors[i].ToString();
				}
				break;
			case 112:
			case 80:
				formats.GoToNextColor();
				break;
			case 120:
				knownColors.clear();
				cout << "Cleared the tracked colors" << endl;
			}
		}
		return 0;
	}
}

int main(int argc, char* argv[])
{
	return tracking::main(argc, argv);
}