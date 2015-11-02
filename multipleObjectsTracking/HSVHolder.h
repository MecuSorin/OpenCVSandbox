#pragma once
#include <string>
#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

namespace ImageUtils
{
	struct HSVHolder
	{
		int h,H, s, S, v, V;

		void Reset(void);
		Scalar ToMin(void);
		Scalar ToMax(void);
		string ToString();
		HSVHolder();
	};
}