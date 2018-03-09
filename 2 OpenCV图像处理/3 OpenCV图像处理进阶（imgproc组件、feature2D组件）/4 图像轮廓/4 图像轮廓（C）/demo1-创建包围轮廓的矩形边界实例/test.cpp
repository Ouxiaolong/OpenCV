/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   创建包围轮廓的矩形边界实例
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
/**namespace********************************************************************/
using namespace cv;
using namespace std;

/**
* @brief     帮助信息
* @param     None
* @retval    None
*/
static void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//输出一些帮助信息
	printf("\n\n\n\t\t\t【矩形包围示例】程序\n\n");
	printf("\n\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】、【Q】、【q】- 退出程序\n\n"
		"\t\t键盘按键任意键 - 重新生成随机点，并寻找包围矩形\n");
}

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char **argv)
{
	Mat srcImage(Size(600, 600), CV_8UC3, Scalar(0));

	RNG &rng = theRNG();

	char key;
	while (1)
	{
		//随机生成一些点  
		//首先就是随机生成点的总数量  
		int g_nPointCount = rng.uniform(3, 30);
		//接下来就是随机生成一些点的坐标  
		vector<Point> points;
		for (int i = 0; i < g_nPointCount; i++)
		{
			Point midPoint;

			midPoint.x = rng.uniform(srcImage.cols / 4, srcImage.cols * 3 / 4);
			midPoint.y = rng.uniform(srcImage.rows / 4, srcImage.rows * 3 / 4);

			points.push_back(midPoint);
		}

		//显示刚刚随机生成的那些点  
		for (int i = 0; i < g_nPointCount; i++)
		{
			circle(srcImage, points[i], 0, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 3);
		}

		//在生成的那些随机点中寻找最小包围矩形  
		//rect变量中得到了矩形  
		Rect rect = boundingRect(points);

		//根据得到的矩形  绘制矩形  
		rectangle(srcImage, rect, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 3);

		imshow("【绘制结束后的图像】", srcImage);

		key = waitKey();
		if (key == 27)
			break;
		else
			srcImage = Scalar::all(0);
	}

	return 0;
}

