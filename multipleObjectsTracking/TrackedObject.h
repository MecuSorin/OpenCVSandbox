#pragma once

#include <string>
#include "HSVMouseSelector.hpp"

using namespace std;
using namespace cv;
using namespace ImageUtils;

namespace tracking
{
	class TrackedObject
	{
	public:
		TrackedObject(void);
		TrackedObject(string type);
		~TrackedObject(void);
		void SetPosition(int x, int y);

		Point getPosition();
		string getType();
		string getPositionAsString();

		void setHSV(HSVHolder hsv);
		HSVHolder getHSV();
	private:
		HSVHolder hsv;
		string type;
		Point position;
	};

}