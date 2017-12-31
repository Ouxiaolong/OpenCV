/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   图像反转
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/                                                                                   
#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

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
    Mat image;  
	Mat roi;
    //【1】读入图像 
	image=imread("1.jpg");  
    
	//【2】将掩膜拷贝到ROI
	image.copyTo(roi);

	//【3】图像反转
	bitwise_not(roi, roi);
	
	//【4】显示结果
	namedWindow("image");  
    imshow("image",image);  
    namedWindow("roi");  
    imshow("roi",roi);  
    
	waitKey(0);  
    
	return 0;  
}
