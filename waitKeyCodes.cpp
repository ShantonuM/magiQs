#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int in;
    int inPrev;
    char inChar;
    ofstream fout;
    fout.open("out");
    while(1)
    {
        cvNamedWindow("Main", CV_WINDOW_AUTOSIZE);
        in = cvWaitKey();
        inChar = in;
        if (inPrev==in) break; //Press any key twice to exit
        cvDestroyWindow("Main");
        fout<<inChar<<" - "<<in<<endl;
        inPrev=in;
    }
    fout.close();
    return 0;
}
