/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2018-03
  * @brief   马赛克检测
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <cv.h>
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <fstream>
#include <string.h>
#include <time.h>
/**namespace********************************************************************/
using namespace cv;
using namespace std;

/**【宏定义】*******************************************************************/
#define length 10
#define c

/**【全局函数声明】*************************************************************/
static void ShowHelpText();
void cal_cubesnumber(int x);

/**【全局变量声明】*************************************************************/
int Pixel[2000][2000] = { 1 };
int Tongji[40][2] = { 0 };

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

	int start, end;
	Mat src;
	Mat canny;
	double low_thresh = 40.0;
	double hig_thresh = 200.0;
	char name[length];

	//记录起始时间
	//【方法一】
	double time0 = static_cast<double>(getTickCount());
	//【方法二】
	start = clock();

	for (int i = 1; i< length + 1; i++)
	{
		sprintf(name, "%d.jpg", i);
		string fname = name;

		src = imread(fname, 1);
		Canny(src, canny, low_thresh, hig_thresh, 3);

		imwrite("Canny.jpg", canny);
		cal_cubesnumber(i);
	}

	//【方法一】
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "【方法一】运行时间为： " << time0 << "秒" << endl;  //输出运行时间

	//【方法二】
	end = clock();
	double time1 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "【方法二】运行时间为： " << time1 << "秒" << endl;  //输出运行时间

	getchar();

	return(0);
}
/**
  * @brief     检测马赛克函数
  * @param     num     图片
  * @retval    void
  */
void cal_cubesnumber(int num)
{
	int Tongji[40][2] = { 0 };

#ifdef c

	IplImage *c_image = cvLoadImage("Canny.jpg", 1);
	int height = (*c_image).height;
	int width = (*c_image).width;
#else
	Mat cpp_image = imread("Canny.jpg");
	Size size = cpp_image.size();
	int height = size.height;
	int width = size.width;
#endif

#ifdef c

	IplImage *c_gray;
	c_gray = cvCreateImage(cvGetSize(c_image), IPL_DEPTH_8U, 1);
	cvCvtColor(c_image, c_gray, CV_BGR2GRAY);
#else

	Mat cpp_gray;
	cvtColor(cpp_image, cpp_gray, CV_BGR2GRAY);
#endif
	for (int x = 0; x<height; x++)
	{
#ifdef c
		uchar *date = (uchar *)c_gray->imageData + x*c_gray->widthStep;
#else
		uchar *date = cpp_gray.ptr<uchar>(x);
#endif
		for (int y = 0; y<width; y++)
		{
			int intensity = date[y];

			if (intensity>200)
			{
				Pixel[y][x] = 0;
			}
			else
			{
				Pixel[y][x] = 1;
			}
		}
	}

	for (int a = 4; a < width - 4; a++)
	{
		for (int bc = 3; bc < 33; bc++)
		{
			for (int b = 4; b < height - 4; b++)
			{
				if (
					Pixel[a][b] == 0 && Pixel[a][b + 1] == 0
					&& Pixel[a + bc - 2][b - 1] == 0 && Pixel[a + bc - 1][b - 1] == 0
					&& Pixel[a + 1][b + bc - 2] == 0 && Pixel[a + 2][b + bc - 2] == 0
					&& Pixel[a + bc - 1][b + bc - 3] == 0 && Pixel[a + bc - 1][b + bc - 4] == 0
					)             //正方形判断
				{
					Tongji[bc][0] = bc;
					Tongji[bc][1]++;
					Pixel[a][b] = 1;
				}
			}

			if (Tongji[bc][1] >= 5)
			{
				cout << num << "帧有马赛克。" << endl;
				goto A;
			}
		}
	}

A:
#ifdef c
	cvReleaseImage(&c_image);
	cvReleaseImage(&c_gray);
#endif

	remove("Canny.jpg");
	remove("Gray.jpg");
}

/**
  * @brief     输出帮助信息
  * @param     None
  * @retval    None
  */
static void ShowHelpText()
{
#ifdef c
	cout <<"C实现!"<< endl;
#else
	cout << "C++实现！" << endl;
#endif
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//输出一些帮助信息
	printf("\n\t【马赛克检测】程序\n\n");
}
