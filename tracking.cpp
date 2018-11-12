#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include "/usr/local/include/opencv2/objdetect.hpp"
#include <unistd.h>
 
using namespace cv;
using namespace std;
 
int main(int argc, char **argv)
{
    CascadeClassifier cascade;
    cascade.load("/usr/local/include/opencv2/data/haarcascades/haarcascade_frontalface_alt.xml");
    std::vector<Rect> faces;
    // Create a tracker
	double min_size = 20;
	double max_size = 200;
    Ptr<Tracker> tracker;
 
    tracker = TrackerKCF::create();
    // Read video
    VideoCapture video(0);
    usleep(100000);
     
    // Exit if video is not opened
    if(!video.isOpened())
    {
        cout << "Could not read video file" << endl; 
        return 1; 
    } 
    
    // Read first frame 
    Mat ok, gray;
    Rect2d roi; 
    video.grab();
    video.retrieve(ok);
    cvtColor(ok, gray, COLOR_BGR2GRAY);
    cascade.detectMultiScale(gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(min_size, max_size));
    for ( size_t i = 0; i < faces.size(); i++ ) 
        	{
             		Rect r = faces[i];
                    roi = r;
               		Scalar color = Scalar(255, 0, 0); 
            		rectangle( ok, cvPoint(cvRound(r.x), cvRound(r.y)), 
                       		cvPoint(cvRound((r.x + r.width-1)),  
        	        	cvRound((r.y + r.height-1))), color, 3, 8, 0); 
        	}
 
 
    imshow("Tracking", ok); 
    tracker->init(ok, roi);
     
    for(;;)
    {     
        // Start timer
        double timer = (double)getTickCount();
        Mat frame;
        video.grab();
        video.retrieve(frame);
        // Update the tracking result
        bool ok = tracker->update(frame, roi);
         
        if (ok)
        {
            // Tracking success : Draw the tracked object
            rectangle(frame, roi, Scalar( 255, 0, 0 ), 2, 1 );
        }
        else
        {
            // Tracking failure detected.
            putText(frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
        }
         
        // Display tracker type on frame
        putText(frame, "KCF Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
 
        // Display frame.
        imshow("Tracking", frame);
         
        // Exit if ESC pressed.
        int k = waitKey(1);
        if(k == 27)
        {
            break;
        }
 
    }
}