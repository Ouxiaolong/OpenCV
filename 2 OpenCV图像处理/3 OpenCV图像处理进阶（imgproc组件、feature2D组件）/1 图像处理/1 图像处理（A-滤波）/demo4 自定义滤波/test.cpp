/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2018-01
  * @brief   自定义滤波
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
/**namespace*******************************************************************/
using namespace std;
using namespace cv;

/*【全局函数声明】***************************************************************/
void showhelp();

/**
* @brief      主函数
* @param      None
* @retval     int
*/
int main(int argc, char * argv[])  
{  
	//改变console字体颜色
	system("color 4F"); 
	//帮助信息
	showhelp();

	//声明变量
	Mat src,self_dst, smooth_dst;
	Mat self_kernel,smooth_kernel;
	
	Point anchor;
	double delta;
	int ddepth;
	int kernel_size;
	int c;

	//载入图像
	src = imread("pic.jpg");

	if (!src.data)
	{
		return -1;
	}

	//创建窗口
	namedWindow("【原图】");
	namedWindow("【自定核的效果图】");
	namedWindow("【平滑滤波的效果图】");

	//初始化滤波器参数
	anchor = Point(-1, -1);
	delta = 0;
	ddepth = -1;

    //【1】自定义核
	//构造矩阵核  	
	self_kernel = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);//自定义核

	//自定义核实现滤波
	filter2D(src, self_dst, src.depth(), self_kernel);

	//显示图像 
	imshow("【原图】", src);
	imshow("【自定核的效果图】", self_dst);
	// 等待关闭窗口    
	waitKey(0);

	//【2】用不同的核对图像进行平滑滤波
	//循环 - 每隔0.5秒，用一个不同的核来对图像进行滤波
	int ind = 0;
	while (true)
	{
		c = waitKey(500);
		//按'ESC'可退出程序
		if ((char)c == 27)
		{
			break;
		}

		//更新归一化块滤波器的核大小
		kernel_size = 3 + 2 * (ind % 5);
		smooth_kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);

		//使用滤波器
		filter2D(src, smooth_dst, ddepth, smooth_kernel, anchor, delta, BORDER_DEFAULT);

		//显示图片
		imshow("【平滑滤波的效果图】", smooth_dst);
		ind++;
	}
}

/*******************************************************************************
  *【showhelp( )函数】
  * 描述：输出帮助信息
  ******************************************************************************/
void showhelp()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\t欢迎使用本程序\n"); 
	printf("\t当前使用的OpenCV版本为：" CV_VERSION "\n");
	printf( "\t按键说明: \n" 
        "\tESC - 退出程序！\n"         
        "\n");  
}