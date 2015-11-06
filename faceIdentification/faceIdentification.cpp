#include "make_vector.h"

const string windowNameShowCapture = "Image feed";
const string face_cascade_name = "haarcascade_frontalface_default.xml";
const string eyes_cascade_name = "haarcascade_eye.xml";
const string face_recognition_file = "saved_faces.xml";
const int face_detection_size = 100;
vector<string> facesVideos = make_vector<string>() << "sabin" << "cristi"  << "sorin" << "tudor";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

Ptr<FaceRecognizer> LearnFaces(vector<string> faceVideos)
{
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	if(fileExists(face_recognition_file))
	{
		model->load(face_recognition_file);
		cout << "Loaded saved faces" << endl;
		return model;
	}
	vector<Mat> faces;
	vector<int> labels;
	for(int i=0; i<faceVideos.size(); i++)
	{
		string videoFile ="Face_"+faceVideos[i]+".avi"; 
		if(!fileExists(videoFile))
		{
			cout << "File " << videoFile << " doesn't exists !!!" << endl;
			throw invalid_argument("Unable to find video file for learning process");
		}
		cout << "Prepaired person " << i+1 << "/" << facesVideos.size() << endl;
		VideoCapture sourceVideo;
		sourceVideo.open(videoFile);
		if(!sourceVideo.isOpened())
		{	
			continue;
		}
		while(sourceVideo.get(CV_CAP_PROP_POS_FRAMES)<sourceVideo.get(CV_CAP_PROP_FRAME_COUNT)-1)
		{
			Mat frame;
			Mat graySource;
			vector<Rect> detectedFacesRects;
			sourceVideo >> frame;
			if(frame.empty()) 
			{
				cout << "!";
				continue;
			}
			cvtColor(frame, graySource, CV_BGR2GRAY);
			equalizeHist(graySource, graySource);
			face_cascade.detectMultiScale(graySource, detectedFacesRects, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(face_detection_size, face_detection_size));
			if(1 != detectedFacesRects.size())
			{
				cout << "!";
				continue;
			}
			Mat face = graySource(detectedFacesRects[0]);
			imshow(windowNameShowCapture, face);
			cout << face.type();
			
			vector<Rect> eyes;
			eyes_cascade.detectMultiScale(face, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30));
			if(eyes.size() != 2)
			{
				cout << "!";
				continue;
			}
			
			faces.push_back(face);
			labels.push_back(i);
		}
		sourceVideo.release();
	}

	if(faces.size() <2)
	{
		cout << "Failed to train the face identification engine" << endl;
		throw invalid_argument("No faces found for training the face identification engine");
	}
	model->train(faces, labels);
	model->save(face_recognition_file);
	cout << "Saved the training data to " << face_recognition_file << endl;
	return model;
}

int doTheStuff(VideoCapture cap)
{
	Mat source;
	Mat graySource;
	vector<Rect> faces;
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	namedWindow(windowNameShowCapture, CV_WINDOW_AUTOSIZE);

	Ptr<FaceRecognizer> faceRecognition = LearnFaces(facesVideos);
	for(;;)
	{
		bool showImage = false;
		//cap.read(source);
		cap >> source;
		if(!source.empty())
		{
			cvtColor(source, graySource, CV_BGR2GRAY);
			equalizeHist(graySource, graySource);
			face_cascade.detectMultiScale(graySource, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(face_detection_size, face_detection_size));
			if(1 > faces.size())
			{
				cout << "No face found"<< endl;
				continue;
			}
			vector<pair<int, double>> predictions;
			for(vector<Rect>::size_type i=0; i< faces.size(); i++)
			{
				int predictedLabel = -1;
				double confidence = 0.0;
				Mat face = graySource(faces[i]);
				faceRecognition->predict(face, predictedLabel, confidence);
				pair<int, double> prediction(predictedLabel, confidence);
				predictions.push_back(prediction);
			}
			for(vector<Rect>::size_type i=0; i< faces.size(); i++)
			{
				if(predictions[i].first>-1)
				{
					stringstream text;
					text << facesVideos[predictions[i].first] << " - " << setprecision(3) << predictions[i].second;
					putText(source, text.str(), faces[i].tl()+Point(0,10), CV_FONT_HERSHEY_PLAIN, 1., Scalar(255,0,0));
				}
			}
			imshow(windowNameShowCapture, source);
		}
		switch ((char)waitKey(10)) {
		case 'q':
		case (char)27:
			return 0;
		}
	}
}

void overlapImage(Mat under, Mat upper)
{
	//addWeighted(under, .5, upper, 1., 0., under); 
	try
	{
		//assert(under.size == upper	.size);
		for(int i=0, width = under.rows; i< width; i++)
			for(int j=0, height = under.cols; j < height; j++)
			{
				Vec4b pixel = upper.at<Vec4b>(i,j);
				if(pixel[3] == 0)
					continue;
				under.at<Vec4b>(i,j) = pixel;
			}
	}
	catch(exception ex)
	{
		cout << ex.what() << endl;
	}
}

int main(int argc, char* argv[])
{
	VideoCapture cap;
	cap.open(0);
	if( !cap.isOpened())
	{
		cout << "Unable to get webcam feed!" << endl;
		return 0;
	}
	try
	{
		doTheStuff(cap);
	}
	catch(exception& exc)
	{
		cout << exc.what() << endl;
		waitKey(100000);
	}
	cap.release();
	destroyAllWindows();
}