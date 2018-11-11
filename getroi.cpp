#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
 
using namespace std;
using namespace cv;
 
 
int main (int argc, char **arv)
{
    // Read image
    Mat im = imread("wheatley.jpg");
    resize(im, im, Size(), .5, .5);
     
    // Select ROI
    Rect2d r = selectROI(im);
     
    cout << r;
    
     
    // Display Cropped Image
    imshow("Image", im);
     
    return 0;
}