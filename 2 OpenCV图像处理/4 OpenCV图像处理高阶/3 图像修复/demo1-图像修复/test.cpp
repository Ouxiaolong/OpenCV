/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2018.3
  * @brief   图片修复-全区域阈值处理+Mask膨胀处理  
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/  
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include <iostream>
/**namespace*******************************************************************/
using namespace cv;

/**【全局函数声明】*************************************************************/
static void ShowHelpText();

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char **argv)
{
	//改变console字体颜色
	system("color 4F");

	//显示帮助文字
	ShowHelpText();	
    Mat imageSource = imread("1.jpg");  
    if (!imageSource.data)  
    {  
        return -1;  
    }  
    imshow("原图", imageSource);  
    Mat imageGray;  
    //转换为灰度图  
    cvtColor(imageSource, imageGray, CV_RGB2GRAY, 0);  
    Mat imageMask = Mat(imageSource.size(), CV_8UC1, Scalar::all(0));  
  
    //通过阈值处理生成Mask  
    threshold(imageGray, imageMask, 240, 255, CV_THRESH_BINARY);  
    Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  
    //对Mask膨胀处理，增加Mask面积  
    dilate(imageMask, imageMask, Kernel);  
  
    //图像修复  
    inpaint(imageSource, imageMask, imageSource, 5, INPAINT_TELEA);  
    imshow("Mask", imageMask);  
    imshow("修复后", imageSource);  
    waitKey();  
}


/**
  * @brief     输出帮助信息
  * @param     None
  * @retval    None
  */
static void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//输出一些帮助信息
	printf("\n\t【图片修复-全区域阈值处理+Mask膨胀处理 】程序\n\n");
}