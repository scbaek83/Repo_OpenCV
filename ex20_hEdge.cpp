#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp" 
#include "opencv2/highgui.hpp" 

void show_wait_destroy(const char* winname, cv::Mat img, int count); 

using namespace std; 
using namespace cv; 

int main() 
{
    int count = 0; 

    const char* pathSrc = "./images/frame2.png"; 
    Mat src = imread(samples::findFile(pathSrc), IMREAD_COLOR); 
    if (src.empty()) { 
        printf("Could not open or find the image!\n"); 
        printf("Usage : %s\n", pathSrc); 
        return -1; 
    }

    printf("src dimension - width: %d, height: %d, channel: %d\n", src.cols, src.rows, src.channels()); 
    show_wait_destroy("src", src, count++); 

    // Crop image 
    Mat crop = src(Range(300,1200), Range(200, 360));
    show_wait_destroy("crop", crop, count++); 

    // Transform source image to gray if it is not already 
    Mat gray; 
    if (crop.channels() == 3) { 
        cvtColor(crop, gray, COLOR_BGR2GRAY); 
    } else { 
        gray = crop; 
    }
    show_wait_destroy("gray", gray, count++); 

    // Edge 
    Mat edge; 
    Canny(gray, edge, 50, 3, 3, false); 
    show_wait_destroy("edge", edge, count++); 
}

void show_wait_destroy(const char* winname, cv::Mat img, int count)
{
    imshow(winname, img); 
    moveWindow(winname, 350*count, 50); 
    waitKey(0); 
}