// ref : https://itecnote.com/tecnote/c-opencv-getting-the-slider-to-update-its-position-during-video-playback/
// ref : https://itecnote.com/tecnote/c-opencv-getting-the-slider-to-update-its-position-during-video-playback/

#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace std; 
using namespace cv; 

int g_slider; 
VideoCapture *g_cap = NULL; 

void onTrackBarSlide(int current_frame, void* tmp) 
{
    current_frame = g_slider; 
    g_cap->set(CAP_PROP_POS_FRAMES, current_frame);
}

int main() 
{
    const char* pathSrc = "./videos/seperate_layer.mp4"; 
    g_cap = new VideoCapture(samples::findFile(pathSrc)); 

    if (!g_cap->isOpened()) { 
        printf("Can't open the video\n : %s\n", pathSrc); 
        return -1; 
    }

    int maxFrame = (int)g_cap->get(CAP_PROP_FRAME_COUNT); 
    if (maxFrame == 0) { 
        printf("No frames in the video\n : %S\n", pathSrc); 
        return 0; 
    }

    namedWindow("video"); 
    createTrackbar("Slider", "video", &g_slider, maxFrame, onTrackBarSlide); 

    Mat img; 
    while (1) { 
        *g_cap >> img; 
        if (img.empty()) break; 

        Mat resized; 
        resize(img, resized, Size(360, 640)); 
        imshow("video", resized);
        if (waitKey(25) == 27) { 
            break; 
        }

    }

    delete g_cap; 
    destroyWindow("video");

    return 0; 
}