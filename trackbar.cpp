// ref : https://github.com/scbaek83/Repo_OpenCV/blob/main/trackbar_book.cpp

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std; 

int g_slider_position = 0; 
int g_run = 1, g_dontset = 0; 

cv::VideoCapture g_cap; 

void onTrackbarSlide(int pos, void*) 
{
    if (!g_dontset) { 
        g_run = 1; 
        g_cap.set(cv::CAP_PROP_POS_FRAMES, pos); 
    }
    g_dontset = 0; 
}

int main() 
{
    cv::namedWindow("ExTrackbar", cv::WINDOW_AUTOSIZE); 
    const char* videoPath = "./videos/seperate_layer.mp4"; 
    g_cap.open(videoPath); 

    if (!g_cap.isOpened()) { 
        printf("Failed to open video\n: %s\n", videoPath); 
        return -1; 
    }

    int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT); 
    int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH); 
    int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    printf("Video has %d frames of dimension width: %d, height: %d\n", frames, tmpw, tmph); 

    cv::createTrackbar("Position", "ExTrackbar", &g_slider_position, frames, onTrackbarSlide); 

    cv::Mat frame; 
    for(;;) { 
        if (g_run != 0) {
            g_cap >> frame; 
            if (frame.empty()) break; 

            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES); 
            g_dontset = 1; 

            cv::setTrackbarPos("Position", "ExTrackbar", current_pos); 
            cv::imshow("ExTrackbar", frame); 

            g_run -= 1; 
        }

        char c = (char)cv::waitKey(10); 
        if (c == 's') { 
            g_run = 1; 
            printf("Single step, run = %d\n", g_run); 
        }
        if (c == 'r') { 
            g_run = -1; 
            printf("Run mode, run = %d\n", g_run); 
        }
        if (c == 27) 
            break; 
    }

    return 0; 
}