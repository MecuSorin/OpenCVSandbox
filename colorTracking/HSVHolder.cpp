#include "HSVHolder.h"

using namespace std;
using namespace cv;

namespace ImageUtils
{
	HSVHolder::HSVHolder() {
		Reset();
	}

	void HSVHolder::Reset() {
		h=s=v=0;
		H=S=V=255;
	}

	Scalar HSVHolder::ToMax() {
		return Scalar(H,S,V);
	}
	Scalar HSVHolder::ToMin() {
		return Scalar(h,s,v);
	}
}