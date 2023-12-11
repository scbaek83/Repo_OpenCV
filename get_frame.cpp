// ref: https://diyver.tistory.com/57

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std; 
using namespace cv; 

int main() 
{
    const char* pathSrc = "./videos/seperate_layer.mp4"; 
    VideoCapture cap(samples::findFile(pathSrc)); 

    if (!cap.isOpened()) { 
        printf("Can't open the video\n : %s", pathSrc); 
        return -1; 
    }

    // Origin video frame size : 720 x 1280
    double w = cap.get(CAP_PROP_FRAME_WIDTH); 
    double h = cap.get(CAP_PROP_FRAME_HEIGHT); 
    printf("Origin's width: %.1f, height: %.1f\n", w, h); 

    // Change frame size 
    if (!cap.set(CAP_PROP_FRAME_WIDTH, w / 2.0)) { 
        printf("Failed to set frame width\n"); 
    }
    if (!cap.set(CAP_PROP_FRAME_HEIGHT, h / 2.0)) { 
        printf("Failed to set frame height\n"); 
    }

    // Changed video frame size 
    w = cap.get(CAP_PROP_FRAME_WIDTH); 
    h = cap.get(CAP_PROP_FRAME_HEIGHT); 
    printf("Changed width: %.1f, height: %.1f\n", w, h); 

    Mat img; 

    while (1) { 
        cap >> img; 
        if (img.empty()) { 
            printf("empty image!"); 
            return 0; 
        }

        Mat resize_frame; 
        resize(img, resize_frame, Size(360, 640));

        imshow("video image", resize_frame); 
        if (waitKey(25) == 27)
            break; 
    }
}