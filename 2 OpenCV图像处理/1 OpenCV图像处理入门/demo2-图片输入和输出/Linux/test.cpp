/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-7
  * @brief   图片的输入和输出
  ******************************************************************************
  * @attention
  * 本程序适用于OPenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
/**namespace********************************************************************/ 
using namespace cv;  
using namespace std; 

/**
  * @brief     主函数
  * @param     None
  * @retval    int
  */
int main()
{  
    //载入图片  
    Mat img = imread("pic.jpg");  
    // 创建一个名为 "图像显示"窗口    
    namedWindow("图像显示");  
    // 在窗口中显示图像    
    imshow("图像显示", img);  
    // 等待1000 ms后窗口自动关闭    
    waitKey(1000);  
}

