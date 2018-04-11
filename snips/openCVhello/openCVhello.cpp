#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace cv;

///opt/ros/kinetic/include/opencv-3.1.0-dev/opencv2/opencv.hpp

// g++ -std=c++11 -I/opt/ros/kinetic/include/opencv-3.3.1/  openCVhello.cpp  /opt/ros/kinetic/lib/libopencv_*.so

//not working:
//g++ -std=c++11 `pkg-config --cflags opencv` edgeTest.cpp `pkg-config --libs opencv`


int main(int, char**)
{
	VideoCapture cap(0);
	//VideoCapture cap("/home/charles/ibex2pics/videoJan2016/output.mp4"); // open the default camera
  	if(!cap.isOpened())  // check if we succeeded
	{
    		cout << "outch" << endl;
		return -1;
	}
  	namedWindow("edges",1);
  	for(;;)
  	{

		double blurRadius1 = 10;
		double blurRadius2 = 5;
		double canny1  =4;
		double canny2 = 3;

		Mat frame;
		bool b;
		b = cap.read(frame);  //this also advances the frame

		Mat grey;
		Mat channel[3];
		Mat blur;
		Mat edges;
	//	cvtColor(frame, grey, COLOR_BGR2GRAY);
		split(frame, channel);

		GaussianBlur(channel[1], blur, Size(5,5), blurRadius1, blurRadius2);
		Canny(blur, edges, 0, canny1, canny2);

	//	imshow("IBEX", frame);
	//	imshow("IBEX", edges);
		
		Mat composite;
		double alpha = 0.5;
		double beta = 1-alpha;
		
		addWeighted(channel[1], alpha, edges, beta, 0.0, composite);
		imshow("foo", channel[1]);
		//imshow("foo1", composite);
		imshow("foo2", edges);

		if(waitKey(30) >= 0) 
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}


