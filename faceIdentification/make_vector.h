#include <string>
#include <iostream>
#include <sstream>
#include <opencv\cv.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include <fstream>
#include <utility>

using namespace std;
using namespace cv;

template <typename T>
class make_vector {
public:
  typedef make_vector<T> my_type;
  my_type& operator<< (const T& val) {
    data_.push_back(val);
    return *this;
  }
  operator std::vector<T>() const {
    return data_;
  }
private:
  std::vector<T> data_;
};

inline bool fileExists(const string& name) {
    ifstream file(name.c_str());
    if (file.good()) {
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }   
}