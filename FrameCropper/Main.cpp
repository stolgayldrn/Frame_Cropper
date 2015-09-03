//////////////////////////////////////////////////////////////////////////
///This code generates frames from video source with given parameters
//////////////////////////////////////////////////////////////////////////

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "helpers_fc.h"
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);		///@param argv[1] open the video file with this path
	if (!cap.isOpened())			///@details if not success, exit program
	{
		cout << "Cannot open the video " << endl;
		return -1;
	}
	string writePath = argv[2];		///@param argv[2] take folder path for frames to write
	pathControl(writePath);			////@details control the path for existence, if it is not exist then create folder
	int CROP_FRAME_WIDTH, CROP_FRAME_HEIGHT, CROP_FPS;
	if(argc>3) // if params are given
	{
		CROP_FRAME_WIDTH	= atoi(argv[3]);		///@param argv[3] Cropping width 
		CROP_FRAME_HEIGHT	= atoi(argv[4]);		///@param argv[4] Cropping height
		CROP_FPS 			= atoi(argv[5]);		///@param argv[5] Cropping height
	}
	else			// if params are not given
	{
		CROP_FRAME_WIDTH	= __TY_VIDEO_SEARCH___FRAME_WIDTH;
		CROP_FRAME_HEIGHT 	= __TY_VIDEO_SEARCH___FRAME_HEIGHT;
		CROP_FPS			= __TY_VIDEO_SEARCH___FPS_PROCESS;
	}
	
	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);			///@desc get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);		///@details the height of frames of the video
	double dFPS = cap.get(CAP_PROP_FPS);					///@details get the frame per seconds of the video 
	double dFrameCount = cap.get(CAP_PROP_FRAME_COUNT);		///@details get the total frame count of the video

	cout << "Frame size  : " << dWidth << " x " << dHeight << endl;
	cout << "Frame count : " << dFrameCount << endl;
	cout << "FPS         : " << dFPS << endl;

	int FrameNumber = 0;
	float fS = dFPS / (CROP_FPS + 1 );
	int frameStep = fS + 0.5;			// rounding
	Mat frame;

	float scaleW = dWidth*0.8/CROP_FRAME_WIDTH;
	float scaleH = dHeight*0.7/CROP_FRAME_HEIGHT;

	while (FrameNumber<(dFrameCount - frameStep-1)) 
	{		
		for(int i = 0 ; i < frameStep; i++)
		{
			bool bSuccess = cap.read(frame); // read a new frame from video
			FrameNumber++;
			if (!bSuccess) // if not success, break loop
			{
				cout << "Cannot read a frame from video stream" << endl;
				break;
			}			
		}
 		string Frame2Write = writePath + "\\" + int2string(FrameNumber) + ".jpg";  // create the path for frame to write
		Mat frameMid = frame(Rect(dWidth*0.1,dHeight*0.05,dWidth*0.8,dHeight*0.7)); // selecting (cropping for process) %80 of image
		/// \brief  A rectangle with sizes  __TY_VIDEO_SEARCH___FRAME_WIDTH x __TY_VIDEO_SEARCH___FRAME_HEIGHT 
		///< is cropped from raw image 
		///< TODO: daha detaylı anlat (%90, rectangle)
		Mat frameDS;
		// frame
		if(scaleH > scaleW)
		{
			resize(frameMid, frameDS, Size(CROP_FRAME_WIDTH*scaleW/scaleH, CROP_FRAME_HEIGHT), 1.0/(scaleH), 1.0/(scaleH),1); // DOWNSAMPLING		
		}
		else
		{
			resize(frameMid, frameDS, Size(CROP_FRAME_WIDTH, CROP_FRAME_HEIGHT*scaleH/scaleW), 1.0/(scaleW), 1.0/(scaleW),1); // DOWNSAMPLING		
		}
		imwrite(Frame2Write, frameDS);			// A JPG FILE IS BEING SAVED
		if(FrameNumber % 200 == 0 )	printf("\rProcessTime: %.2f%%",100.0*FrameNumber/dFrameCount);
	}
	cap.release();
	return 0;
}