#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <iostream>

using namespace std ;
using namespace cv ;

//////////////////////////////////////
int main(int argc , char* argv[])
{
	CvSize size680x480 = cvSize(640 , 480);
	CvCapture* p_capture ;
	IplImage* p_imgOriginal ;			//pointer to an image sturcture , this is input image fr the veb cam
	IplImage* p_imgProcess ;			//this is the processed image (intel image processing library , this is the standard structure )

	CvMemStorage* p_strstorage;			//necessary storage variable to pass
	CvSeq* p_seq_circles ;				//pointer to an opencv sequence , will contain all the circles and will be re
										//returned by cvhough circles();
	float* p_fixedradius ;				//pointer to a three element array of floats
										//[0] -> x position of the detected object
										//[1] -> y position
										//[2] -> radius

	int i;			//loop counter
	char charCheckForEscKey;	 //esc exits from the program (char for checking the escape key)
	p_capture =  cvCaptureFromCAM(0) ;	//0-> use 1st webcam , may have to change to a different number if you have multiple camera
	if(p_capture == NULL)  //if capture was not successful
	{
		printf("error :Capture is NULL \n");
		getchar();			//getchar() to pause for the user to see the message
		return(-1);			//exit program
	}
	cvNamedWindow("Original" , CV_WINDOW_AUTOSIZE);  //original image from webcam
	cvNamedWindow("Processed",CV_WINDOW_AUTOSIZE);		//processed image willl be used for detecting circles


	p_imgProcess = cvCreateImage(size680x480,IPL_DEPTH_8U,1); //640 x 480 pixels(Cvsize struct for earlier)
																//8-bit color depth
																//1channel (gray scale) , if this was a color image , use 3 here intead of 1

	while(1){
		p_imgOriginal = cvQueryFrame(p_capture);				//get frame from webcam									//for each frame ...
		if(p_imgOriginal == NULL)								//if frame was not handled successfully
		{
			printf("Error :frame is null \n");
			getchar();
			break;

		}
		cvInRangeS(p_imgOriginal,CV_RGB(0,100,0), CV_RGB(100,255,100),p_imgProcess);			//function input//min filtering value ( if color is greater than or equal to this)
		p_strstorage = cvCreateMemStorage(0);//allocate necessary memory storage variable to pass into cvcricles()
		cvSmooth(p_imgProcess,p_imgProcess,CV_GAUSSIAN,				//smooth the processed image, this will make it easier for the next function to pick out the circles
				9,9);													//gaussian filter averages the nesr by pixels
		p_seq_circles = cvHoughCircles(p_imgProcess ,
			p_strstorage,CV_HOUGH_GRADIENT,  //two pass algo for detecting circles
			2,p_imgProcess->height /4 ,		//minimum distance in pixels btween the centres of the detected circles								 //size of image /2  = accumulator resolution
			100,10,20,200);		//threshhold(max ,min) , circleradius(min , max)
		for(i=0;i<p_seq_circles->total ;i++)//for each object in sequential cicrles structure(i.e for each radius detected)
		{
			p_fixedradius = (float*)cvGetSeqElem(p_seq_circles,i);
			printf("Ball position x=%f , y = %f , z= %f\n",p_fixedradius[0],p_fixedradius[1],p_fixedradius[2]);
		//draw a small green circle at the centre of the detected object
			cvCircle(p_imgProcess,cvPoint(cvRound(p_fixedradius[0]),cvRound(p_fixedradius[1])),3,CV_RGB(0,255,0),CV_FILLED);
			//draw a red circle around the detected object
			cvCircle(p_imgProcess,cvPoint(cvRound(p_fixedradius[0]),cvRound(p_fixedradius[1])),
				cvRound(p_fixedradius[2]),CV_RGB(255,0,0),3);
		}
		cvShowImage("Original",p_imgOriginal); //original image with detected ball overlay
		cvShowImage("Processed",p_imgProcess); //image after processing
		cvReleaseMemStorage(&p_strstorage);
		charCheckForEscKey = cvWaitKey(10);
		if(charCheckForEscKey == 27) break;//if escape key askii 27 is pressed , jump out of the while

	}//end while
	cvReleaseCapture(&p_capture);
	cvDestroyWindow("original");
	cvDestroyWindow("Processed");
	return(0);
}
