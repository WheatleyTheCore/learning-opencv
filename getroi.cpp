#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <unistd.h>
 
using namespace std;
using namespace cv;
 
 
int main (int argc, char **arv)
{
    Mat im;
    VideoCapture cap(0);
    usleep(50000);
    cap.grab();
    cap.retrieve(im);
    resize(im, im, Size(), .5, .5);
     
    // Select ROI
    Rect2d r = selectROI(im);
     
    cout << r;
    
     
    // Display Cropped Image
    imshow("Image", im);
     
    return 0;
}