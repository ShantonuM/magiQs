
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <iostream>

using namespace std ;
using namespace cv ;

int main () {

char charCheckForEscKey ;
CvCapture *p_capture ;
IplImage *p_imgOriginal ;			//pointer to an image sturcture , this is input image fr the veb cam

IplImage *p_imgThreshold ; 			//this is the processed image (intel image processing library , this is the standard structure )

p_capture = cvCaptureFromCAM(0) ;



if (p_capture){

while(1){
    p_imgOriginal = cvQueryFrame(p_capture) ;
    cvSmooth(p_imgOriginal,p_imgOriginal,CV_GAUSSIAN,3,3) ;
    cvShowImage("Original",p_imgOriginal) ;
    IplImage *p_imgGrayscale = cvCreateImage(cvGetSize(p_imgOriginal),8,1) ;
    cvCvtColor(p_imgOriginal,p_imgGrayscale,CV_BGR2GRAY) ;
    //cvShowImage("Grayscale",p_imgGrayscale) ;

    cvThreshold(p_imgGrayscale,p_imgGrayscale,100,255,CV_THRESH_BINARY_INV);
    cvThreshold(p_imgGrayscale,p_imgGrayscale,100,255,CV_THRESH_BINARY_INV);
    cvNamedWindow("Thresholded Image",1);
    cvShowImage("Thresholded Image",p_imgGrayscale);
    charCheckForEscKey = cvWaitKey(10);
		if(charCheckForEscKey == 27) break;
}

}

cvReleaseCapture(&p_capture) ;
cvDestroyAllWindows() ;
return 0 ;

}

