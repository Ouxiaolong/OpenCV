/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   腐蚀
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/  
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
   
/**namespace*******************************************************************/
using namespace std;  
using namespace cv;  
   
/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main (int argc, char **argv)    
{
	//载入原图   
	Mat image = imread("1.jpg"); 
	
	//创建窗口
	namedWindow("【原图】腐蚀操作"); 
	namedWindow("【效果图】腐蚀操作");  

	//显示原图  
	imshow("【原图】腐蚀操作", image);  

	//获取自定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	Mat out;  

	//进行腐蚀操作 
	erode(image,out, element);  

	//显示效果图 
	imshow("【效果图】腐蚀操作", out); 

	waitKey(0); 
	return 0;  
}  
