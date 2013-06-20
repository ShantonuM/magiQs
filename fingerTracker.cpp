#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
	CvCapture* capture = cvCaptureFromCAM(0);

	if (!capture) {
		cout<<"ERROR: capture is NULL \nPress any key to exit.";
		cvWaitKey();
		return -1;
	}

	cvNamedWindow("Main", CV_WINDOW_AUTOSIZE);

	while (1) {
		IplImage* frame = cvQueryFrame( capture );
		if (!frame) {
			cout<<"ERROR: frame is NULL \nPress any key to exit.";
			cvWaitKey();
			break;
		}

		cvShowImage("Main", frame);

		// Do not release the frame!
		// If ESC key pressed (key=27)
		if (cvWaitKey(10)==27) break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Main");

	return 0;
}
