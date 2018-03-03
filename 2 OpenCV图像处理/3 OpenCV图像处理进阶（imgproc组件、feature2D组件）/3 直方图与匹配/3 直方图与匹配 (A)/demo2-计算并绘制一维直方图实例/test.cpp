/**
******************************************************************************
* @file    test.cpp
* @author  Bruceou
* @version V1.0
* @date    2018-03
* @brief   计算并绘制一维直方图实例
******************************************************************************
* @attention
* 本程序适用于OpenCV2和OpenCV3版本。
******************************************************************************
*/
/**Includes*********************************************************************/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
/**namespace********************************************************************/
using namespace cv;
using namespace std;

/**
* @brief     帮助信息函数
* @param     None
* @retval    None
*/
void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

/**
* @brief     主函数
* @param     argc 命令行参数个数
argv 命令行参数
* @retval    int
*/
int main(int argc, char **argv)
{
	//【1】载入原图并显示
	Mat srcImage = imread("1.jpg", 1);
	//若图片是彩色图片则用一下方式读取
	//imread("1.jpg", 0);
	
	imshow("原图", srcImage);
	if (!srcImage.data)
	{
		cout << "fail to load image" << endl;
		return 0;
	}

	system("color 1F");
	ShowHelpText();

	//【2】定义变量
	MatND dstHist;       // 在cv中用CvHistogram *hist = cvCreateHist
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	int channels = 0;

	//【3】计算图像的直方图
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);    // cv 中是cvCalcHist
	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
	//【4】获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);  //  在cv中用的是cvGetMinMaxHistValue

	//【5】绘制出直方图
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);           //   注意hist中是float类型    而在OpenCV1.0版中用cvQueryHistValue_1D
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("一维直方图", dstImage);
	waitKey(0);
	return 0;
}