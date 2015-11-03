#include "ColorFormats.h"

namespace tracking
{
	TrackedColorFormat::TrackedColorFormat()
		: name("Hsv default"), BGR2Format(COLOR_BGR2HSV)
	{}
	TrackedColorFormat::TrackedColorFormat(string textToShow, int BGR2FormatCovertor)
		: name(textToShow), BGR2Format(BGR2FormatCovertor)
	{}
	TrackedColorFormat::~TrackedColorFormat(void){}
		
	Scalar TrackedColorFormat::ToMin(HSVHolder holder)
	{
		return holder.ToMin();
	}
	Scalar TrackedColorFormat::ToMax(HSVHolder holder)
	{
		return holder.ToMax();
	}
	int TrackedColorFormat::getFormat(void)
	{
		return BGR2Format;
	}
	string TrackedColorFormat::getText(void)
	{
		return name;
	}

	TrackedColorHSV::TrackedColorHSV(void)
		: TrackedColorFormat("HSV", COLOR_BGR2HSV)
	{}

	Scalar TrackedColorHSV::ToMin(HSVHolder holder)
	{
		return Scalar(holder.h, 0, 0);
	}

	Scalar TrackedColorHSV::ToMax(HSVHolder holder)
	{
		return Scalar(holder.H, 0, 0);
	}

	TrackedColorLab::TrackedColorLab(void)
		: TrackedColorFormat("Lab", COLOR_BGR2Lab)
	{}

	Scalar TrackedColorLab::ToMin(HSVHolder holder)
	{
		return Scalar(0, holder.s, holder.v);
	}

	Scalar TrackedColorLab::ToMax(HSVHolder holder)
	{
		return Scalar(255, holder.S, holder.V);
	}

	TrackedColorLabDefault::TrackedColorLabDefault(void)
		: TrackedColorFormat("Lab default", COLOR_BGR2Lab)
	{}

	Scalar TrackedColorLabDefault::ToMin(HSVHolder holder)
	{
		return Scalar(holder.h, holder.s, holder.v);
	}

	Scalar TrackedColorLabDefault::ToMax(HSVHolder holder)
	{
		return Scalar(holder.H, holder.S, holder.V);
	}

	ColorFormats::ColorFormats(void)
		:currentColorIndex(0)
	{
		colorFormats = vector<TrackedColorFormat>(0);
		TrackedColorHSV hsvFormat;
		TrackedColorLab labFormat;
		TrackedColorLabDefault labFormatDefault;
		TrackedColorFormat hsvDefaultFormat;
		colorFormats.push_back(hsvDefaultFormat);
		colorFormats.push_back(hsvFormat);
		colorFormats.push_back(labFormatDefault);
		colorFormats.push_back(labFormat);
	}


	ColorFormats::~ColorFormats(void)
	{}

	TrackedColorFormat ColorFormats::CurrentColorFormat()
	{
		return colorFormats[currentColorIndex];
	}

	int ColorFormats::CurrentColorFormatConvertor()
	{
		return colorFormats[currentColorIndex].getFormat();
	}

	void ColorFormats::GoToNextColor(void)
	{
		++currentColorIndex;
		currentColorIndex = currentColorIndex % colorFormats.size();
		cout << "Changed to: " << CurrentColorFormat().getText() << endl;
	}
}