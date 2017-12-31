/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   图像混合
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

/**【全局函数声明部分】********************************************************/
bool  ROI_AddImage();
bool  LinearBlending();
bool  ROI_LinearBlending();

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main (int argc, char **argv)  
{
	system("color 5E");

	if(ROI_AddImage( )&& LinearBlending( )&&ROI_LinearBlending( ))
	{
		cout<<endl<<"嗯。好了，得出了你需要的图像~! : )";
	}

	waitKey(0);
	return 0;
}

/**
  * @brief     利用感兴趣区域ROI实现图像叠加
  * @param     None
  * @retval    bool
  */ 
bool  ROI_AddImage()
{
	// 【1】读入图像
	Mat srcImage1= imread("pa.jpg");
	Mat logoImage= imread("logo.jpg");
	if( !srcImage1.data ) { printf("读取srcImage1错误~！ \n"); return false; }
	if( !logoImage.data ) { printf("读取logoImage错误~！ \n"); return false; }

	// 【2】定义一个Mat类型并给其设定ROI区域
	Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));

	// 【3】加载掩模（必须是灰度图）
	Mat mask= imread("logo.jpg",0);

	// 【4】将掩膜拷贝到ROI
	logoImage.copyTo(imageROI,mask);

	// 【5】将一个Mat图像输出到图像文件
	imwrite("srcImage1.jpg",srcImage1);
	
	// 【6】显示结果
	namedWindow("<1>利用ROI实现图像叠加示例窗口");
	imshow("<1>利用ROI实现图像叠加示例窗口",srcImage1);

	return true;
}

/**
  * @brief     图像混合
  * @param     None
  * @retval    bool
  */
bool  LinearBlending()
{
	//【0】定义一些局部变量
	double alphaValue = 0.5; 
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// 【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if( !srcImage2.data ) { printf("读取srcImage2错误~！ \n"); return false; }
	if( !srcImage3.data ) { printf("读取srcImage3错误~！ \n"); return false; }

	// 【2】进行图像混合加权操作
	betaValue = ( 1.0 - alphaValue );
	addWeighted( srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// 【3】创建并显示原图窗口
	namedWindow("<2>线性混合示例窗口【原图】 ", 1);
	imshow( "<2>线性混合示例窗口【原图】 ", srcImage2 );
	
	// 【4】将一个Mat图像输出到图像文件
	imwrite("dstImage.jpg",dstImage);
	
	// 【5】显示结果
	namedWindow("<3>线性混合示例窗口【效果图】", 1);
	imshow( "<3>线性混合示例窗口【效果图】", dstImage );

	return true;
}

/**
  * @brief     线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义
  *            感兴趣区域ROI，实现自定义区域的线性混合
  * @param     None
  * @retval    bool
  */
bool  ROI_LinearBlending()
{
	//【1】读取图像
	Mat srcImage4= imread("pa.jpg",1);
	Mat logoImage= imread("logo.jpg");

	if( !srcImage4.data ) { printf("读取srcImage4错误~！ \n"); return false; }
	if( !logoImage.data ) { printf("读取logoImage错误~！ \n"); return false; }

	//【2】定义一个Mat类型并给其设定ROI区域
	Mat imageROI;
	//方法一
	imageROI= srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));
	//方法二
	//imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

	//【3】将logo加到原图上
	addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);
	
	//【4】将一个Mat图像输出到图像文件
	imwrite("srcImage4.jpg",srcImage4);
	
	//【5】显示结果
	namedWindow("<4>区域线性图像混合示例窗口");
	imshow("<4>区域线性图像混合示例窗口",srcImage4);
	
	return true;
}

