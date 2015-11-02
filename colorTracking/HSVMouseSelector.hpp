#pragma once

#include <sstream>
#include <iostream>
#include <vector>

#include "HSVHolder.h"

using namespace cv;
using namespace std;

namespace ImageUtils
{
	class HSVMouseSelector
	{
	public:
		~HSVMouseSelector(void);
		HSVMouseSelector(HSVHolder* currentHSV, Mat* cameraFrame);
		void UpdateFrame(Mat* hsvMat);	
		void OnMouseEvent(int event, int x, int y, int flags);

	private:
		bool isRectangleSelected;
		bool shouldDrawRectangle;
		Point startDragPosition;
		Point currentDragPosition;
		Rect selectedRectangle;
		Mat* cameraFrame;
		HSVHolder* myHSV;
	};
	void MouseCallback(int event, int x, int y, int flags, void *param);
}