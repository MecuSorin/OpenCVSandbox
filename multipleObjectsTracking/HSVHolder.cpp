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

	string HSVHolder::ToString() {
		stringstream rez;
		rez << "h:" << setw(4) << setfill(' ') << h << endl;
		rez << "h:" << setw(4) << setfill(' ') << h << endl;
		rez << "s:" << setw(4) << setfill(' ') << s << endl;
		rez << "S:" << setw(4) << setfill(' ') << S << endl;
		rez << "v:" << setw(4) << setfill(' ') << v << endl;
		rez << "V:" << setw(4) << setfill(' ') << V << endl;
		return rez.str();
	}
}