#include "TrackedObject.h"
using namespace std;
using namespace cv;

namespace tracking 
{

	TrackedObject::TrackedObject(void)
	{
	}

	TrackedObject::TrackedObject(string name)
	{
		type = name;
	}


	TrackedObject::~TrackedObject(void)
	{
	}

	void TrackedObject::SetPosition(int x, int y)
	{
		position = Point(x,y);
	}

	
	Point TrackedObject::getPosition()
	{
		return position;
	}

	string TrackedObject::getPositionAsString()
	{
		stringstream result;
		result << setw(0) << setfill(' ') << position.x << "," << setw(4) << setfill(' ') << position.y << ' ';
		return result.str();
	}

	string TrackedObject::getType()
	{
		return type;
	}

	void TrackedObject::setHSV(HSVHolder holder)
	{
		hsv = holder;
	}

	HSVHolder TrackedObject::getHSV(){
		return hsv;
	}
}