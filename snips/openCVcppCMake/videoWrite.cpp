#include <iostream> // for standard I/O
#include <string>   // for strings
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main()
{
	VideoWriter outputVideo; // For writing the video
	int width = 640; // Declare width here
	int height = 480; // Declare height here
	Size S = Size(width, height); // Declare Size structure
	const string filename = "bar.avi"; // Declare name of file here
	int fourcc = CV_FOURCC('M','J','P','G');
	int fps = 10;
	outputVideo.open(filename, fourcc, fps, S);

  //if ogg bug here, do
  //   mencoder foo.mp4 -ovc lavc -oac mp3lame -o foo.avi
   //and try again in avi -- working
  //VideoCapture cap("/home/charles/foo.avi");
	VideoCapture cap(0);   // dev/video0 webcam; or use a regular filename
	if(!cap.isOpened())  // check if we succeeded
	{
    	cout << "couldnt open video input" << endl;
    	return -1;
  	}
  	cout << "loaded video" << endl;

  	namedWindow("edges",1);
  	for(;;)
  	{
		Mat frame;
    	bool b;
    	b = cap.read(frame);  //this also advances the frame
	    imshow("videoWrite", frame);
	    if(waitKey(30) >= 0)
    	    break;
    }
  	return 0;
}

