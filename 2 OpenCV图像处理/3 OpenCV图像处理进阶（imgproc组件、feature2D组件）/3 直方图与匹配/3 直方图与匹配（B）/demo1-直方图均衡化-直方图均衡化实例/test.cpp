/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   直方图均衡化实例
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
/**namespace*******************************************************************/
using namespace cv;
using namespace std;

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main (int argc, char **argv)  
{
	// 【1】加载源图像
	Mat srcImage, dstImage;
	srcImage = imread( "lena.jpg", 1 );
	if(!srcImage.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n"); return false; } 

	imshow( "原始图", srcImage );
	// 【2】转为灰度图并显示出来
	cvtColor( srcImage, srcImage, CV_BGR2GRAY );
	

	// 【3】进行直方图均衡化
	equalizeHist( srcImage, dstImage );

	// 【4】显示结果
	imshow( "经过直方图均衡化后的图", dstImage );

	// 等待用户按键退出程序
	waitKey(0);
	return 0;

}