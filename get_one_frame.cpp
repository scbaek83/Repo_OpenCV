#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp" 

#include <fstream> 

using namespace std; 

int main() 
{
    cv::namedWindow("Example2_4", cv::WINDOW_AUTOSIZE); 

    cv::VideoCapture cap; 
    string videoPath = "./videos/plasma.MP4"; 
    cap.open(videoPath); 

    if (!cap.isOpened()) {
        printf("Video open failed\n: %s\n", videoPath.c_str()); 
        return -1; 
    }

    cap.set(cv::CAP_PROP_POS_FRAMES, 2); 

    cv::Mat frame; 
    cap >> frame; 

    cv::imwrite("./frame2.png", frame);

    return 0; 
}