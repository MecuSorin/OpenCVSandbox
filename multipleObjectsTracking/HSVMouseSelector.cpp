#include "HSVMouseSelector.hpp"

using namespace cv;

namespace ImageUtils
{
	HSVMouseSelector::HSVMouseSelector(HSVHolder* currentHSV, Mat* cameraFeed)
		: isRectangleSelected(false), shouldDrawRectangle(false)
	{
		cameraFrame = cameraFeed;
		myHSV = currentHSV;
	}

	HSVMouseSelector::~HSVMouseSelector(void)
	{
		cameraFrame = NULL;
		myHSV = NULL;
	}

	void MouseCallback(int event, int x, int y, int flags, void *param)
	{
		((HSVMouseSelector*)param)->OnMouseEvent(event, x, y, flags);
	}

	void HSVMouseSelector::OnMouseEvent(int event, int x, int y, int flags)
	{
		if (event == CV_EVENT_RBUTTONDOWN){
			myHSV->Reset();
			return;
		}

		if (event == CV_EVENT_LBUTTONDOWN && !shouldDrawRectangle)
		{
			startDragPosition = Point(x, y);
			shouldDrawRectangle = true;
		}

		if (event == CV_EVENT_MOUSEMOVE && shouldDrawRectangle)
		{
			currentDragPosition = Point(x, y);
		}

		if (event == CV_EVENT_LBUTTONUP && shouldDrawRectangle)
		{
			shouldDrawRectangle = false;
			isRectangleSelected = true;
			selectedRectangle = Rect(startDragPosition, currentDragPosition);
		}
	}

	void HSVMouseSelector::UpdateFrame(Mat* hsv_frame){
		if (shouldDrawRectangle) {
			rectangle(*cameraFrame, startDragPosition, currentDragPosition, cv::Scalar(0, 255, 0), 1, 8, 0);
			return;
		}
		if(!isRectangleSelected) {
			return;
		}
		if (selectedRectangle.width<1 || selectedRectangle.height<1)
		{
			cout << "Please drag a rectangle, not a line" << endl;
			return;
		}

		isRectangleSelected = false;
		vector<int> H_ROI, S_ROI, V_ROI;
		for (int i = selectedRectangle.x; i<selectedRectangle.x + selectedRectangle.width; i++){
			for (int j = selectedRectangle.y; j<selectedRectangle.y + selectedRectangle.height; j++){
				Vec3b pixel = hsv_frame->at<Vec3b>(j,i);
				H_ROI.push_back((int)pixel[0]);
				S_ROI.push_back((int)pixel[1]);
				V_ROI.push_back((int)pixel[2]);
			}
		}

		if (H_ROI.size()>0){
			myHSV->h = *std::min_element(H_ROI.begin(), H_ROI.end());
			myHSV->H = *std::max_element(H_ROI.begin(), H_ROI.end());
			cout << "MIN 'H' VALUE: " << myHSV->h << endl;
			cout << "MAX 'H' VALUE: " << myHSV->H << endl;
		}
		if (S_ROI.size()>0){
			myHSV->s = *std::min_element(S_ROI.begin(), S_ROI.end());
			myHSV->S = *std::max_element(S_ROI.begin(), S_ROI.end());
			cout << "MIN 'S' VALUE: " << myHSV->s << endl;
			cout << "MAX 'S' VALUE: " << myHSV->S << endl;
		}
		if (V_ROI.size()>0){
			myHSV->v = *std::min_element(V_ROI.begin(), V_ROI.end());
			myHSV->V = *std::max_element(V_ROI.begin(), V_ROI.end());
			cout << "MIN 'V' VALUE: " << myHSV->v << endl;
			cout << "MAX 'V' VALUE: " << myHSV->V << endl;
		}
	}
}