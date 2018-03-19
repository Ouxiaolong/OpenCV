/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   Harris 角点检测
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
/**namespace********************************************************************/
using namespace cv;  

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char** argv) 
{  
	//以灰度模式载入图像并显示
	Mat srcImage = imread("1.jpg", 0);  
	imshow("原始图", srcImage);  

	//进行Harris角点检测找出角点
	Mat cornerStrength;  
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	//对灰度图进行阈值操作，得到二值图并显示  
	Mat harrisCorner;  
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);  
	imshow("角点检测后的二值效果图", harrisCorner);  

	waitKey(0);  
	return 0;  
} 