#pragma once
#include <string>
#include <vector>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "HSVHolder.h"

using namespace std;
using namespace cv;
using namespace ImageUtils;

namespace tracking
{
	class TrackedColorFormat
	{
	public:
		TrackedColorFormat();
		TrackedColorFormat(string textToShow, int BGR2FormatCovertor);
		~TrackedColorFormat(void);
		
		virtual Scalar ToMin(HSVHolder);
		virtual Scalar ToMax(HSVHolder) ;
		int getFormat(void);
		string getText(void);
	private:
		string name;
		int BGR2Format;
	};

	class TrackedColorHSV: public TrackedColorFormat
	{
	public:
		TrackedColorHSV(void);
		virtual Scalar ToMin(HSVHolder);
		virtual Scalar ToMax(HSVHolder);
	};

	class TrackedColorLab: public TrackedColorFormat
	{
	public:
		TrackedColorLab(void) ;
		virtual Scalar ToMin(HSVHolder);
		virtual Scalar ToMax(HSVHolder);
	};

	class TrackedColorLabDefault: public TrackedColorFormat
	{
	public:
		TrackedColorLabDefault(void) ;
		virtual Scalar ToMin(HSVHolder);
		virtual Scalar ToMax(HSVHolder);
	};
	class ColorFormats
	{
	public:
		ColorFormats(void);
		~ColorFormats(void);

		TrackedColorFormat CurrentColorFormat(void);
		int CurrentColorFormatConvertor(void);
		void GoToNextColor(void);
	private:
		int currentColorIndex;
		vector<TrackedColorFormat> colorFormats;
	};
}
