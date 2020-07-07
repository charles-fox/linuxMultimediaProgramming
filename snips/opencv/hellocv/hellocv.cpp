#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace cv;

int main(int, char**)
{
	VideoCapture cap(0); //to use local webcam
	//VideoCapture cap("myfile.mp4"); // to use a file
  	if(!cap.isOpened()) {
    		cout << "outch" << endl;
		return -1;
	}
  	namedWindow("edges",1);

  	for(;;)  {
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
		split(frame, channel);

		GaussianBlur(channel[1], blur, Size(5,5), blurRadius1, blurRadius2);
		Canny(blur, edges, 0, canny1, canny2);

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
  	return 0;
}


