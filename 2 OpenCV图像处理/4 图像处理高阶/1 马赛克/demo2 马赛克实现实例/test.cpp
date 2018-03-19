/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2018-03
  * @brief   马赛克实现
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

/**【全局变量声明】*************************************************************/
Mat imageSourceCopy; //原始图像  
Mat imageSource; //原始图像拷贝  
int neightbourHood = 9; //马赛克上每个方框的像素大小  

RNG rng;
int randomNum; //邻域内随机值  

Point ptL; //左键按下时坐标  
Point ptR;  //右键按下时坐标 

/**【全局函数声明】*************************************************************/
static void ShowHelpText();
void onMouse(int event, int x, int y, int flag, void *ustg);//鼠标回调函数

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

	imageSourceCopy = imread("1.jpg");
	imageSource = imageSourceCopy.clone();

 
	imshow("原图", imageSourceCopy);
	
	namedWindow("原图");
	setMouseCallback("原图", onMouse);

	waitKey(0);
	return 0;
}

/**
  * @brief     回调函数
  * @param     event
               x
			   y
			   flag
			   ustg
  * @retval    None
  */
void onMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		ptL = Point(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		//对鼠标画出的矩形框超出图像范围做处理，否则会越界崩溃  
		x > imageSource.cols - 2 * neightbourHood ? x = imageSource.cols - 2 * neightbourHood : x = x;
		y > imageSource.rows - 2 * neightbourHood ? y = imageSource.rows - 2 * neightbourHood : y = y;

		//对鼠标从右下往右上画矩形框的情况做处理  
		ptR = Point(x, y);
		Point pt = ptR;
		ptR.x < ptL.x ? ptR = ptL, ptL = pt : ptR = ptR;
		for (int i = 0; i < ptR.y - ptL.y; i += neightbourHood)
		{
			for (int j = 0; j < ptR.x - ptL.x; j += neightbourHood)
			{
				randomNum = rng.uniform(-neightbourHood / 2, neightbourHood / 2);
				Rect rect = Rect(j + neightbourHood + ptL.x, i + neightbourHood + ptL.y, neightbourHood, neightbourHood);
				Mat roi = imageSourceCopy(rect);
				Scalar sca = Scalar(
					imageSource.at<Vec3b>(i + randomNum + ptL.y, j + randomNum + ptL.x)[0],
					imageSource.at<Vec3b>(i + randomNum + ptL.y, j + randomNum + ptL.x)[1],
					imageSource.at<Vec3b>(i + randomNum + ptL.y, j + randomNum + ptL.x)[2]);
				Mat roiCopy = Mat(rect.size(), CV_8UC3, sca);  
				roiCopy.copyTo(roi);  
			}  
		}  
	}  
	imshow("马赛克生成图", imageSourceCopy);
	waitKey(0);
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
	printf("\n\t【马赛克实现】程序\n\n");
}
