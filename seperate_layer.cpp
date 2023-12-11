#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>

// ref : https://docs.opencv.org/3.4/d9/db0/tutorial_hough_lines.html

using namespace std; 
using namespace cv; 

int main() 
{
    Mat src, cropped, dst; 
    Mat color_img, color_crop, color_crop2;

    const char* path_src = "./plasma_cell.png"; 

    color_img = imread(samples::findFile(path_src));

    src = imread(samples::findFile(path_src), IMREAD_GRAYSCALE); 
    printf("width: %d, height: %d\n", src.cols, src.rows); 
    cropped = src(Range(10, 250), Range(2, 40)); 
    color_crop = color_img(Range(10, 250), Range(2, 40)); 
    color_crop2 = color_crop.clone(); 

    Canny(cropped, dst, 1, 100, 3, false); 
    
    // namedWindow("cropped", WINDOW_NORMAL); 
    // imshow("cropped", cropped);
    // imshow("src", src);
    // imshow("canny", dst);
    // imshow("color", color_img);
    
    // waitKey(); 

    // Standard Hough Line Trnasform 
    vector<Vec2f> lines;        // will hold the results of detection 
    HoughLines(dst, lines, 1, 2, 10, 50, 10, 1, 3); 
    printf("lines.size(): %d\n", lines.size()); 

    // Draw the lines 
    for (size_t i=0; i<lines.size(); i++) { 
        float rho = lines[i][0], theta = lines[i][1]; 
        printf("%d 's theta: %f\n", i, theta);
        if (theta > CV_PI/2) {
            Point pt1, pt2; 
            double a = cos(theta), b = sin(theta); 
            double x0 = a*rho, y0 = b*rho; 
            pt1.x = cvRound(x0 + 100*(-b)); 
            pt1.y = cvRound(y0 + 1000*(a)); 
            pt2.x = cvRound(x0 - 1000*(-b)); 
            pt2.y = cvRound(y0 - 1000*(a)); 
            line(color_crop, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA); 
        }
        
    }

    // Probabilistic Line Transform 
    vector<Vec4i> linesP;       // will hold the results of the detection 
    // HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10); 
    HoughLinesP(dst, linesP, 1, 100, 50, 50, 10); 
    // Draw the lines 
    for (size_t i=0; i<linesP.size(); i++) {
        Vec4i l = linesP[i]; 
        line(color_crop2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA); 
    }

    imshow("cropped src", color_img); 
    imshow("canny", dst);
    imshow("Standard", color_crop); 

    imshow("Probabilistic", color_crop2); 
    waitKey(); 
    destroyAllWindows();
    
    return 0; 
}