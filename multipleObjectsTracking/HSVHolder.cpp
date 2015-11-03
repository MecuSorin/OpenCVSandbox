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
		//return Scalar(H,S,V);
		return Scalar(H,255,255);
	}
	Scalar HSVHolder::ToMin() {
		//return Scalar(h,s,v);
		return Scalar(h,0,0);
	}

	string HSVHolder::ToString() {
		stringstream rez;
		rez << "h:" << setw(4) << setfill(' ') << h << "H:" << setw(4) << setfill(' ') << h << endl;
		rez << "s:" << setw(4) << setfill(' ') << s << "S:" << setw(4) << setfill(' ') << S << endl;
		rez << "v:" << setw(4) << setfill(' ') << v << "V:" << setw(4) << setfill(' ') << V << endl;
		return rez.str();
	}
}