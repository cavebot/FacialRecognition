#include <iostream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;

CascadeClassifier faceCascade;
CascadeClassifier faceCascadeSide;

//definition under main()
void detectAndDisplay(Mat frame);


int main() {

	//load front face pre-trained classifier
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) { cout << "xml file not loaded" << endl; }

	//load side face pre-trained classifier
	faceCascadeSide.load("Resources/haarcascade_profileface.xml");
	if (faceCascadeSide.empty()) { cout << "xml file not loaded" << endl; }

	//select webcam, 0 is system cam, 1 is external cam
	VideoCapture cap(0);
	Mat frame;

	while (cap.isOpened())
	{
		//read frame, pass to classifier+processing function
		cap.read(frame);
		detectAndDisplay(frame);

		// wait for 20 ms between successive frames and break the loop if key q is pressed  
		char exit = waitKey(20);
		if (exit == 'q') {
			break;
		}
	}
	return 0;
}


void detectAndDisplay(Mat frame) {

	Mat grayscaleFrame;
	cvtColor(frame, grayscaleFrame, COLOR_BGR2GRAY);
	equalizeHist(grayscaleFrame, grayscaleFrame);

	vector<Rect> faces;
	vector<Rect> facesSide;

	faceCascade.detectMultiScale(grayscaleFrame, faces);
	//faceCascadeSide.detectMultiScale(grayscaleFrame, facesSide);

	for (int i = 0; i < faces.size(); i++)
	{

		int xTopLeft, yTopLeft;
		xTopLeft = faces[i].x;
		yTopLeft = faces[i].y;
		cout << faces[i].x << ' ' << faces[i].y << endl;
		

		rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(0, 0, 255), 2);
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		//ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
	}
	imshow("Frame", frame);
}


//code to detetct faces in video MP4 file instead of webcam
// Obtain frame size information using get() method
 

//int frame_width = static_cast<int>(cap.get(3));
//int frame_height = static_cast<int>(cap.get(4));
//int fps = cap.get(5);
//int frame_Number = cap.get(CAP_PROP_FRAME_COUNT);
//cout << "fps is " << fps << endl; 
//cout << "number of frames is" << frame_Number << endl;

//int fps = 30;

//Size frame_size(frame_width, frame_height);

//VideoWriter output("Resources/output.mp4", VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, frame_size);

//int j = 1;
