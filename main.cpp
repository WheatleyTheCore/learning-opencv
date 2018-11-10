#include "/usr/local/include/opencv2/objdetect.hpp" 
#include "/usr/local/include/opencv2/highgui.hpp" 
#include "/usr/local/include/opencv2/imgproc.hpp" 
#include <iostream> 

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())
	{  // check if we succeeded
        return -1;
	}
	CascadeClassifier cascade;
	double fx = 1;
	cascade.load("/usr/local/include/opencv2/data/haarcascades/haarcascade_frontalface_alt.xml");
    namedWindow("cam",1);
	std::vector<Rect> faces;
	double min_size = 20;
	double max_size = 200;
    for(;;)
    {
        Mat frame, gray, resizedImg;
        cap.grab();
		cap.retrieve(frame);
		cvtColor( frame, gray, COLOR_BGR2GRAY );

    	resize( gray, resizedImg, Size(), fx, fx, INTER_LINEAR );

        equalizeHist( resizedImg, resizedImg );
		 // get a new frame from camera
		cascade.detectMultiScale(gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(min_size, max_size));
		for ( size_t i = 0; i < faces.size(); i++ ) 
        	{
             		Rect r = faces[i]; 
                	Mat smallImgROI; 
               		std::vector<Rect> nestedObjects; 
               		Point center; 
               		Scalar color = Scalar(255, 0, 0); 
            		rectangle( frame, cvPoint(cvRound(r.x), cvRound(r.y)), 
                       		cvPoint(cvRound((r.x + r.width-1)),  
        	        	cvRound((r.y + r.height-1))), color, 3, 8, 0); 
        	}
        imshow("cam", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}