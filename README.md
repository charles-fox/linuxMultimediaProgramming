Linux Multimedia Programming

Graphics, Audio, Video

Curator: Charles Fox

Creative Commons Wikipedia Licence

1 Introduction

TODO could I write a little book on this + my linux audio paper? 

theres a pakt 2017 linux sound book here, https://www.safaribooksonline.com/library/view/linux-sound-programming/9781484224960/

Need a snips folder and way to include the prog files as text automatically

idea: select the best of breed of everything and present together. Not a detailed tech manual. Can refer reader to web APIs etc.

hence what we choose to miss out is aslo improtant. eg dont cover OSS. Only latest, one of everything. Find tools that work toghehter. One view of how to do it.

do it as creative commons? then we can keep it updated, and make heavy use of wikipedia and other tutorial bits.

talk about IOX, this was written during it.

use github so can accept patches from others at discresion.

We need to use C so we can see the bits and bytes and understand what's going on.

CMake intro as best practice

http://www.oreilly.com/openbook/

Part I Graphics

2 Graphics architecture

memory mapped

graphics card

OS + window system (eg some render using GL, others don't)

hence need for GLUT/SDL etc.

3 OpenGL

4 SDL

vs GLUT. Unlike GLUT does not take control, up to user to call it in own loop. Easy to use full screen mode and to access keyboard and controllers, eg for games. Also has 2D graphics not using GL.

5 CAD

5.1 Collada (dae) format

5.2 OpenSceneGraph (uses dae)

6 OpenCV

6.1 Reading and writing

mhm

\begin{VerbatimOut}{snips/openCVcppCMake/videoWrite.cpp}

khj

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

	VideoCapture cap(0);   // dev/video0 webcam

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





6.2 Basic manipulations

7 Files and formats

24 bit color = 1 bytes for each of R,G,B. 32bit adds alpha byte too.

BGR format for historical reasons.

Various color depths.

7.1 Bitmap (BMP)

Windows standard. Header then raw RGB array data.



7.2 ROS Image message

header includes timestamps etc as well as img size and depth.

7.3 Portable Network Graphics (PNG)

compressed, like JPG. File made of chunks of labelled types.

7.4 Postscript vector graphics

as programming language. as used in IOX.

7.5 Portable Document Fomat (pdf)

7.6 Fonts

8 GPU/CUDA as graphics programming?

how graphics cards work (from lincoln)

9 Applications

GIMP

FreeCAD

Part II Audio

10 How sound cards work

11 ALSA (kernel module)

11.1 input

11.2 output

11.3 MIDI

live

files

12 JACK

13 LADSPA

14 File formats

14.1 wav

header + raw bytes.

14.2 vorbis (ogg)

15 Music synthesis

16 Speech synthesis

festival

17 Speech recognitions

kaldi?

18 Applications

list best LADSPA plugins?

LMMS

Ardour

ZynAddSubFX

musichastie?

Part III Video

19 Video architecture

Multimedia comes in various kinds of streams. Streams may contain video or audio or other things. These may be compressed with codecs, eg h264,theora. Combining streams eg audio+video is multiplexing. Demupliplexing is seprate from decoding. Streams can be passed over realtime protocols such as RTP or stored in container files such as mp4,ogg. problem with compressing video is that it introduces lateny, some compressions require knowledge of future frames, eg MP4. Others are designed for live use eg H264. 

20 Video4Linux (V4L)

is a standard API for video devices such as webcams, plus some drivers implementing it.

API devices appear as files at ls /sys/class/video4linux/ which can be accessed eg. via pythonCV: cv2.videoCapture(3) 

v4l2-ctl: gives low level info and setting for USB camera hardware typically GUI tools are calling into it to change camera settings

has many useful help options, see --help 

get current settings: v4l2-ctl --device=/dev/video0 --get-fmt-video

eg to set image size and codec: v4l2-ctl --device=/dev/video0 --set-fmt-video=width=800,height=600,pixelformat=1

logitech C920 has onboard codecs: YUYV -- splits up luma (Y) and croma (Cr and Cb red and blue diffs) and downsamples chroma a bit (YUV 4:4:2) MPEG H264

ask for available frame rates: v4l2-ctl --device=/dev/video0 --list-frameintervals=width=640,height=480,pixelformat=YUYV

20.1 Loopback

Loopback is a system which allows you to create virtual video devices in V4L, so that other applications may access them just as if they were real devices. Like real devices they appears in /dev/videoX.

enable kernel module.

create loopback.

21 Real-time transport protocol (RTP) streaming

RTP is a dedicated http-like protocol, running over UDP, for real time media (a media stream format is bit like a container file) 

(RTSP is a higher-level session control protol sometimes used together with RTP, e.g. to give rewind/fast-forward type commands.)

via VLC 

cvlc -vvv v4l2:///dev/video0 --sout '#transcode{vcodec=mp2v,vb=800,acodec=none}:rtp{sdp=rtsp://:8554/}' 

cvlc -vvv v4l2:///dev/video0 --sout '#transcode{vcodec=h264,vb=800,acodec=none}:rtp{sdp=rtsp://:8554/}' https://sandilands.info/sgordon/live-webca-streaming-using-vlc-command-line

to read client: 

vlc -vvv --network-caching 200 rtsp://127.0.0.1:8554/

:sout=#transcode{vcodec=h264,acodec=mpga,ab=128,channels=2,samplerate=44100}:rtp{dst=127.0.0.1,port=5004,mux=ts,sap,name=stream} :sout-keep

multicast?

22 GStreamer

linux system for media streams, based on PIPELINEs of modules. (Competitor to ffmpeg in some ways). Requires modules to go in the pipelines (eg good/bad/ugly sets, own code). Like "ROS for video" ? We are using version 1.0 for everything (0.10 also exists) Modules are binary (Cpp) executables, implementing standard API. (Like LADSPA - but not as real time? eg including buffering).

includes reading and writing to/from v4l devices. eg. stream things into new virtual v4l devices for others to read. also UDP data stream sources and sinks. v4l is a minority sport though as gstreamer has its own internal appsrc and appsinks.

can give commands to jump to points in streams

it would be a good habit to get used to using gstreamer instead of ffmpeg for genreal conversion use. it is more powerful for realtime use and worth knowing.

("!" makes the pipe, like unix "|" but called a "pad" rather than "pipe")

#basic copy a source file to a sink file: gst-launch-1.0 filesrc location=~/data/qb/NorwichLeeds1280.mp4 ! filesink location=~/out.mp4

#play mp3 gst-launch-1.0 filesrc location=~/test.mp3 ! decodebin ! autoaudiosink

#play mp4 video gst-launch-1.0 filesrc location=~/test.mp4 ! decodebin ! autovideosink

#extract a segment of a file, recode, and send to another file (not working) gst-launch-0.10 gnlfilesource location=$PWD/source.mp3 start=0 duration=5000000000 media-start=10000000000 media-duration=5000000000 ! audioconvert ! vorbisenc ! oggmux ! filesink location=destination.ogg

#decode a file and stream raw video to a file, gst-launch-1.0 filesrc location=~/test.mp4 ! decodebin ! filesink location=~/out.mp4

#stream to RTP over UDP port gst-launch-1.0 filesrc location=~/test.mp4 ! decodebin ! x264enc ! rtph264pay ! udpsink host=127.0.0.1 port=9001

#stream from Ibex robot webcam, to h264 over RTP/UDP. (the comments tell the other modules about formats which exist at points) gst-launch-1.0 v4l2src ! 'video/x-raw, width=640, height=480, framerate=10/1' ! videoconvert ! x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! udpsink host=192.168.0.220 port=1234

#streaming to a virtual divce is called loopback and it needs to be enabled: sudo apt-get install v4l2loopback-dkms sudo modprobe v4l2loopback #(creates /sys/class/video4linux/video1 and /dev/video1 )

In Ibex, use gstreamer loopback to read an incoming VLC video stream from the robot eg in RTP format, and create a gstreamer stream here into V4L. Then python/CV doesn't care what the source was, it just looks like another webcam. (ffmpeg can also do this?)

We can also do this to stream a video file into gstreamer/loopback(?). eg. to enable multiple processes to read the same stream and process it in parallel. gst-launch-0.10 filesrc location=~/Documents/my_video.ogv ! decodebin2 ! ffmpegcolorspace ! videoscale ! ffmpegcolorspace ! v4l2sink device=/dev/video1 (maybe is a bug in gstreamer here)

gst-launch-1.0 -v videotestsrc ! tee ! v4l2sink device=/dev/video1 

#this works to stream a file over UDP, and read and view it on client: gst-launch-1.0 filesrc location=~/data/qb/NorwichLeeds1280.mp4 ! decodebin ! x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! udpsink host=127.0.0.1 port=9001

gst-launch-1.0 udpsrc port=9001 ! "application/x-rtp, payload=127" ! rtph264depay ! avdec_h264 ! videoconvert ! xvimagesink

#to read from a V4L port on the same client: (eg then view in VLC) gst-launch-1.0 udpsrc port=9001 ! "application/x-rtp, payload=127" ! rtph264depay ! avdec_h264 ! videoconvert ! videorate ! video/x-raw, framerate=25/5 ! v4l2sink device=/dev/video1

*this works to stream a file into a V4L device: (after activiating loopback)

sudo modprobe v4l2loopback gst-launch-1.0 filesrc location=~/data/qb/NorwichLeeds1280.mp4 ! decodebin ! v4l2sink device=/dev/video1

or with some conversions:

gst-launch-1.0 filesrc location=~/data/qb/NorwichLeeds1280.mp4 ! decodebin ! videoconvert ! videorate ! video/x-raw, framerate=25/5 ! v4l2sink device=/dev/video1

PYTHON GSTREAMER API https://github.com/rubenrua/GstreamerCodeSnippets good tutorials

23 ffmpeg

get video file info ffprobe -show_streams -i ~/data/qb/NorwichLeeds1280.mp4

speedup playback of video ffmpeg -r:v "480/1" -i sprayingVideo.mp4 -an -r:v "12/1" output.mp4

split avi into frames: ffmpeg -i corinthian_raw_images.avi -f image2 frames/frame-%3d.png 

extract section: ffmpeg -ss 00:00:05.123 -i in.mp4 -t 00:01:00.00 -c copy out.mp4 #start time and duration args; can be 00:00:00.000 format, or seconds as 00.000. NB only splits to nearest keyframes (unless omit copy to transcode)

downsample resolution: ffmpeg -i in.avi -c:a copy -c:v libx264 -crf 23 -s:v 640x360 output.mp4

24 File formats

24.1 theora (ogg)

25 ROS

ROS video streams ROS, CV have differerent img formats, use cvbridge node to convert them: http://wiki.ros.org/cv_bridge/Tutorials/ConvertingBetweenROSImagesAndOpenCVImagesPython

26 (C)VLC

STREAMING FROM VLC is maybe easier than gstreamer! To stream a file as RTP over UDP:

cvlc ~/data/qb/NorwichLeeds1280.mp4 :sout=#transcode{vcodec=h264}:"rtp{dst=127.0.0.1,port=9001,mux=ts}"

then read from CV with (few seconds delay needed) -- but only by one client :-( cap = cv2.VideoCapture("udp://@127.0.0.1:9001")

multicast: cvlc -vvv ~/data/qb/NorwichLeeds1280.mp4 :norm=ntsc :v4l2-width=320 :v4l2-height=240 :v4l2-standard=45056 :channel=1 --no-sout-audio --sout '#transcode{vb="1600",vcodec=mpgv,acodec=mpga,venc=ffmpeg}:rtp{proto=udp,mux=ts,dst=127.0.0.1,port=9001}' --loop --ttl 

Part IV Multimedia

27 Containers and streams

arbitary data streams mixed in. eg robot commands and sensors. Also subtitles, foreign language audio tracks...

28 rosbag as a container

29 H264 (skype, DVDs, mp4s, CCTV cams)

30 H323 (ekiga streams)

30.1 Session Initial Protocol (SIP)

to set up calls

31 Augmented reality (GL+CV)

is surprisingly hard / nonstandard

32 Parallel programming

ROS image format diff frm cv, cvbridge to convert requires ROS stack overhead ROS kinetic all uses python2, with opencv3 (dont change system pyton to 3 - kills ROS!) serialise/deserialise and pipe implem,entaion : serialise is slow. ROS nodelets:allow several nodes to run as a single process, no msgs.

MPI (network layer 5) wraps all of SYSV/TCPIP/Infiniband python example message passing, not shmem (some shmem in MPI2?) eg. at each frame, map (img,dM) across Pool functions to do stuff.

SYSV-python wrapper shmem - after serialisation

GStreamer / V4L app source and sinks stuck on how to get it into opencv/py

RTP/UDP sockets from GStreamer or vlc via GStreamer (http://stackoverflow.com/questions/13564817/python-send-and-receive-rtp-packets)

multiprocessing pipes semaphores shared arrays and map

filelock stuck on a lock

Thrift (over TCP)

33 DSP microprocessors (Texas instruments)

34 FPGA DSP (verilog, Chisel)
