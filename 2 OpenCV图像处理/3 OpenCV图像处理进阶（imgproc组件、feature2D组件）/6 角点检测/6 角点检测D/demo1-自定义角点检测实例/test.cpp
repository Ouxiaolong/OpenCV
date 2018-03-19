/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   自定义角点检测实例
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
/**namespace********************************************************************/
using namespace cv;
using namespace std;

/**【宏定义】*******************************************************************/
#define myHarris_WINDOW "【myHarris角点检测】"            //为窗口标题定义的宏 
#define myShiTomasi_WINDOW "【myShiTomass角点检测】"        //为窗口标题定义的宏 

/**【全局函数声明】*************************************************************/
static void ShowHelpText();                     //帮助信息
void myShiTomasi_function(int, void*);
void myHarris_function(int, void*);

/**【全局变量声明】*************************************************************/
Mat src, src_gray;
Mat myHarris_dst; Mat myHarris_copy; Mat Mc;
Mat myShiTomasi_dst; Mat myShiTomasi_copy;

int myShiTomasi_qualityLevel = 50;
int myHarris_qualityLevel = 50;
int max_qualityLevel = 100;

double myHarris_minVal; 
double myHarris_maxVal;

double myShiTomasi_minVal; 
double myShiTomasi_maxVal;

RNG rng(12345);

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char** argv)
{
	//【0】改变console字体颜色
	system("color 6F");

	//【0】显示帮助文字
	ShowHelpText();

	//【1】载入图像并灰度化  
	src = imread("1.jpg", 1);
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//【2】 设置参数  
	int blockSize = 3; int apertureSize = 3;

	//【3】使用cornerEigenValsAndVecs()函数检测角点  
	myHarris_dst = Mat::zeros(src_gray.size(), CV_32FC(6));
	Mc = Mat::zeros(src_gray.size(), CV_32FC1);

	cornerEigenValsAndVecs(src_gray, myHarris_dst, blockSize, apertureSize, BORDER_DEFAULT);

	//【4】 特征点选择  
	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{		
			// 两个特征值  
			//【方法一】
			//float lambda_1 = myHarris_dst.at<Vec6f>(j, i)[0];
			//float lambda_2 = myHarris_dst.at<Vec6f>(j, i)[1];
			//Mc.at<float>(j, i) = lambda_1*lambda_2 - 0.04*pow((lambda_1 + lambda_2), 2);

			//【方法二】
			float* lambda = myHarris_dst.ptr<float>(j, i);
			float lambda1 = lambda[0];
			float lambda2 = lambda[1];
			Mc.at<float>(j, i) = lambda1*lambda2 - 0.04*pow((lambda1 + lambda2), 2);

		}
	}

	minMaxLoc(Mc, &myHarris_minVal, &myHarris_maxVal, 0, 0, Mat());

	//【5】创建窗口和滑动条  
	namedWindow(myHarris_WINDOW, CV_WINDOW_AUTOSIZE);
	createTrackbar(" Quality Level:", myHarris_WINDOW, &myHarris_qualityLevel, max_qualityLevel,
		myHarris_function);
	myHarris_function(0, 0);

	//【3】使用cornerMinEigenVal()函数检测角点  
	myShiTomasi_dst = Mat::zeros(src_gray.size(), CV_32FC1);
	cornerMinEigenVal(src_gray, myShiTomasi_dst, blockSize, apertureSize, BORDER_DEFAULT);

	minMaxLoc(myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_maxVal, 0, 0, Mat());

	//【5】创建窗口和滑动条  
	namedWindow(myShiTomasi_WINDOW, CV_WINDOW_AUTOSIZE);
	createTrackbar(" Quality Level:", myShiTomasi_WINDOW, &myShiTomasi_qualityLevel, max_qualityLevel,
		myShiTomasi_function);
	myShiTomasi_function(0, 0);

	waitKey(0);
	return(0);
}

/**
  * @brief     myShiTomasi角点检测函数实现函数
  * @param     int
               void
  * @retval    None
  */
void myShiTomasi_function(int, void*)
{
	myShiTomasi_copy = src.clone();

	if (myShiTomasi_qualityLevel < 1) { myShiTomasi_qualityLevel = 1; }

	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			if (myShiTomasi_dst.at<float>(j, i) > myShiTomasi_minVal + (myShiTomasi_maxVal -
				myShiTomasi_minVal)*myShiTomasi_qualityLevel / max_qualityLevel)
			{
				circle(myShiTomasi_copy, Point(i, j), 4, Scalar(rng.uniform(0, 255),
					rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
			}
		}
	}
	imshow(myShiTomasi_WINDOW, myShiTomasi_copy);
	cout << "Harris Quality Level: " << myShiTomasi_qualityLevel << endl;
}

/**
  * @brief     myHarris角点检测函数实现函数
  * @param     int
               void
  * @retval    None
  */
void myHarris_function(int, void*)
{
	myHarris_copy = src.clone();

	if (myHarris_qualityLevel < 1) { myHarris_qualityLevel = 1; }

	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			if (Mc.at<float>(j, i) > myHarris_minVal + (myHarris_maxVal - myHarris_minVal)
				*myHarris_qualityLevel / max_qualityLevel)
			{
				circle(myHarris_copy, Point(i, j), 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
					rng.uniform(0, 255)), -1, 8, 0);
			}
		}
	}
	imshow(myHarris_WINDOW, myHarris_copy);
	cout << "Harris Quality Level: " << myHarris_qualityLevel << endl;
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
	printf("\n\t【自定义角点检测】程序\n\n");	
	printf("\n\t请调整滑动条观察图像效果\n\n");
}