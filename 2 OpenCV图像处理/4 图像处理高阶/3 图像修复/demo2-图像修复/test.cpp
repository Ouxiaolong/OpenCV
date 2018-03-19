/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2018.3
  * @brief   图片修复-鼠标圈定区域阈值处理+Mask膨胀处理
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

/**【全局变量】*****************************************************************/
Point ptL, ptR; //鼠标画出矩形框的起点和终点  
Mat imageSource, imageSourceCopy;
Mat ROI; //原图需要修复区域的ROI  

/**【全局函数声明】****************************************************************/
void OnMouse(int event, int x, int y, int flag, void *ustg);
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

	imageSource = imread("1.jpg");
	if (!imageSource.data)
	{
		return -1;
	}
	imshow("原图", imageSource);
	setMouseCallback("原图", OnMouse);
	waitKey();
}

/**
  * @brief     回调函数
  * @param     event
               x
			   y
			   flag
			   ustg
  * @retval    void
  */
void OnMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		ptL = Point(x, y);
		ptR = Point(x, y);
	}
	if (flag == CV_EVENT_FLAG_LBUTTON)
	{
		ptR = Point(x, y);
		imageSourceCopy = imageSource.clone();
		rectangle(imageSourceCopy, ptL, ptR, Scalar(255, 0, 0));
		imshow("原图", imageSourceCopy);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		if (ptL != ptR)
		{
			ROI = imageSource(Rect(ptL, ptR));
			imshow("ROI", ROI);
			waitKey();
		}
	}
	//单击鼠标右键开始图像修复  
	if (event == CV_EVENT_RBUTTONDOWN)
	{
		imageSourceCopy = ROI.clone();
		Mat imageGray;
		cvtColor(ROI, imageGray, CV_RGB2GRAY); //转换为灰度图  
		Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));

		//通过阈值处理生成Mask  
		threshold(imageGray, imageMask, 235, 255, CV_THRESH_BINARY);
		Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imageMask, imageMask, Kernel);  //对Mask膨胀处理  
		inpaint(ROI, imageMask, ROI, 9, INPAINT_TELEA);  //图像修复  
		imshow("Mask", imageMask);
		imshow("修复后", imageSource);
	}
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
	printf("\n\t【图片修复-鼠标圈定区域阈值处理+Mask膨胀处理】程序\n\n");
	printf("\n\t 点击鼠标左键进行框选修复区域！\n\n");
	printf("\n\t 单击鼠标右键进行修复！\n\n");
}