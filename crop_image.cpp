#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std; 
using namespace cv; 

int main() 
{
    const char* path_src = "./plasma_buffy.png"; 

    Mat src = imread(samples::findFile(path_src), IMREAD_GRAYSCALE); 

    printf("width: %d, height: %d\n", src.cols, src.rows);

    Mat cropped = src(Range(100, 400), Range(50, 70)); 

    // namedWindow("cropped", WINDOW_NORMAL); 
    imshow("cropped", cropped); 

    // namedWindow("src", WINDOW_NORMAL); 
    imshow("src", src); 

    waitKey(); 
    destroyAllWindows();

    return 0; 
}