/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2018-03
  * @brief   毛玻璃滤镜
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <core\core.hpp>  
#include <highgui\highgui.hpp>  
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
/**namespace********************************************************************/
using namespace cv;
using namespace std;

/**【全局函数声明】*************************************************************/
static void ShowHelpText();

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char** argv) 
{  
	//改变console字体颜色
	system("color 4F");

	//显示帮助文字
	ShowHelpText();
	
    Mat imageSource = imread("1.jpg");  
    Mat imageResult = imageSource.clone();  
    RNG rng;  
    int randomNum;  
    int Number = 5;  
  
	for (int i = 0; i < imageSource.rows - Number; i++)
	{
		for (int j = 0; j < imageSource.cols - Number; j++)
		{
			randomNum = rng.uniform(0, Number);
			imageResult.at<Vec3b>(i, j)[0] = imageSource.at<Vec3b>(i + randomNum, j + randomNum)[0];
			imageResult.at<Vec3b>(i, j)[1] = imageSource.at<Vec3b>(i + randomNum, j + randomNum)[1];
			imageResult.at<Vec3b>(i, j)[2] = imageSource.at<Vec3b>(i + randomNum, j + randomNum)[2];
		}
	}
	//创建窗口
	namedWindow("【原图】");
	namedWindow("【毛玻璃效果图】");

	//显示原图和效果图
	imshow("【原图】", imageSource);
	imshow("【毛玻璃效果图】", imageResult);
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
	printf("\n\t【毛玻璃滤镜】程序\n\n");
}
