/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-7
  * @brief   OpenCV 2、3与 OpenCV 1 同时使用
  ******************************************************************************
  * @attention
  * 本程序适用于OPenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
/**namespace********************************************************************/ 
using namespace cv;  // The new C++ interface API is inside this namespace. Import it.
using namespace std;

/**宏定义***********************************************************************/
#define DEMO_MIXED_API_USE 

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main( int argc, char** argv )
{
    const char* imagename = "1.jpg";

#ifdef DEMO_MIXED_API_USE
    Ptr<IplImage> IplI = cvLoadImage(imagename);      // Ptr<T> is safe ref-counting pointer class
    if(IplI.empty())
    {
        cerr << "Can not load image " <<  imagename << endl;
        return -1;
    }
    Mat I(IplI); // Convert to the new style container. Only header created. Image not copied.    
#else
    Mat I = imread("1.jpg");        // the newer cvLoadImage alternative, MATLAB-style function
    if( I.empty() )                   // same as if( !I.data )
    {
        cerr << "Can not load image " <<  "1.jpg"<< endl;
        return -1;
    }
#endif

    // 创建一个名为 "图像显示"窗口    
    namedWindow("图像显示");  
    // 在窗口中显示图像    
    imshow("图像显示", I);  
    // 等待1000 ms后窗口自动关闭    
    waitKey(1000);  
}


