// ref : https://docs.opencv.org/3.4/dd/dd7/tutorial_morph_lines_detection.html 

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

void show_wait_destroy(const char* winname, cv::Mat img, int count); 

using namespace std; 
using namespace cv; 

int main() 
{
    int count = 0; 

    const char* pathSrc = "./plasma_cell.png"; 
    Mat src = imread(samples::findFile(pathSrc), IMREAD_COLOR); 
    if (src.empty()) { 
        cout << "Could not open or find the image!\n" << endl; 
        cout << "Usage: " << pathSrc; 
        return -1; 
    }
    printf("width: %d, height: %d, channel: %d\n", src.cols, src.rows, src.channels()); 
    show_wait_destroy("src", src, count++); 

    // Transfrom source image to gray if it is not already 
    Mat gray; 
    if (src.channels() == 3) { 
        cvtColor(src, gray, COLOR_BGR2GRAY); 
    } else { 
        gray = src; 
    }

    show_wait_destroy("gray", gray, count++);

    // Apply adativeThreshold at the bitwise_not of gray, notice the ~ symbol 
    Mat bw; 
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, -2); 
    show_wait_destroy("bw", bw, count++); 

    Mat horizontal = bw.clone(); 

    // Specify size on horizontal axis 
    int horizontal_size = horizontal.cols / 11; 
    
    // Create structure element for extracting horizontal lines through morphology operations 
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1)); 

    // Apply morphology operations 
    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1)); 
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1)); 

    // Show extracted horizontal lines 
    show_wait_destroy("horizontal", horizontal, count++); 

    destroyAllWindows(); 

    return 0; 
}

void show_wait_destroy(const char* winname, cv::Mat img, int count) 
{
    imshow(winname, img); 
    moveWindow(winname, 150 * count, 0); 
    waitKey(0); 
}
