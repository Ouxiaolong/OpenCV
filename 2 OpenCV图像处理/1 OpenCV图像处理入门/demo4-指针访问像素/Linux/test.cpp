/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-7
  * @brief   指针访问像素
  ******************************************************************************
  * @attention
  * 本程序适用于OPenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
/**namespace********************************************************************/ 
using namespace std;
using namespace cv;

/*【函数声明部分】**************************************************************/
void colorReduce(Mat& inputImage, Mat& outputImage, int div);  
void ShowHelpText();

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char** argv)
{  
	//【1】创建原始图并显示
	Mat srcImage = imread("1.jpg");  
	imshow("原始图像",srcImage);  

	//【2】按原始图的参数规格来创建创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//效果图的大小、类型与原图片相同 

	ShowHelpText();

	//【3】记录起始时间
	double time0 = static_cast<double>(getTickCount());  

	//【4】调用颜色空间缩减函数
	colorReduce(srcImage,dstImage,32);  

	//【5】计算运行时间并输出
	time0 = ((double)getTickCount() - time0)/getTickFrequency();
	cout<<"\t此方法运行时间为： "<<time0<<"秒"<<endl;  //输出运行时间

	//【6】显示效果图
	imshow("效果图",dstImage);  
	waitKey(0);  
}  

/**
  * @brief     使用【指针访问：C操作符[ ]】方法版的颜色空间缩减函数
  * @param     inputImage    输入矩阵（图像）
               outputImage   输出矩阵（图像）
               div           
  * @retval    None
  */
void colorReduce(Mat& inputImage, Mat& outputImage, int div) 
{  
	//参数准备
	outputImage = inputImage.clone();  //拷贝实参到临时变量
	int rowNumber = outputImage.rows;  //行数
	int colNumber = outputImage.cols*outputImage.channels();  //列数 x 通道数=每一行元素的个数

	//双重循环，遍历所有的像素值
	for(int i = 0;i < rowNumber;i++)  //行循环
	{  
		uchar* data = outputImage.ptr<uchar>(i);  //获取第i行的首地址
		for(int j = 0;j < colNumber;j++)   //列循环
		{  	
			// ---------【开始处理每个像素】-------------     
			data[j] = data[j]/div*div + div/2;  
			// ----------【处理结束】---------------------
		}  //行处理结束
	}  
}  

/**
  * @brief     帮助信息
  * @param     None
  * @retval    None
  */
void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
	printf("\n\n  ---------------------------------------------------\n");
}


