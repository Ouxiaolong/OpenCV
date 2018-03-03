/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2018-03
  * @brief   模板匹配
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
/**namespace********************************************************************/
using namespace cv;

/**【宏定义】*******************************************************************/
#define WINDOW_NAME1 "【原始图片】"        //为窗口标题定义的宏 
#define WINDOW_NAME2 "【匹配窗口】"        //为窗口标题定义的宏 

/**【全局变量声明】*************************************************************/
Mat g_srcImage; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

/**【全局函数声明】*************************************************************/
void on_Matching( int, void* );
static void ShowHelpText( );

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main (int argc, char **argv) 
{
	//【0】改变console字体颜色
	system("color 1F"); 

	//【0】显示帮助文字
	ShowHelpText();

	//【1】载入原图像和模板块
	g_srcImage = imread( "1.jpg", 1 );
	g_templateImage = imread( "2.jpg", 1 );

	//【2】创建窗口
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	namedWindow( WINDOW_NAME2, CV_WINDOW_AUTOSIZE );

	//【3】创建滑动条并进行一次初始化
	createTrackbar( "方法", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching );
	on_Matching( 0, 0 );

	waitKey(0);
	return 0;

}

/**
  * @brief     回调函数
  * @param     int
               None
  * @retval    NOne
  */
void on_Matching( int, void* )
{
	//【1】给局部变量初始化
	Mat srcImage;
	g_srcImage.copyTo( srcImage );

	//【2】初始化用于结果输出的矩阵
	int resultImage_cols =  g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create( resultImage_cols, resultImage_rows, CV_32FC1 );

	//【3】进行匹配和标准化
	matchTemplate( g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod );
	normalize( g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat() );

	//【4】通过函数 minMaxLoc 定位最匹配的位置
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	Point matchLocation;
	minMaxLoc( g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	//【5】对于方法 SQDIFF 和 SQDIFF_NORMED, 越小的数值有着更高的匹配结果. 而其余的方法, 数值越大匹配效果越好
	if( g_nMatchMethod  == CV_TM_SQDIFF || g_nMatchMethod == CV_TM_SQDIFF_NORMED )
	{ matchLocation = minLocation; }
	else
	{ matchLocation = maxLocation; }

	//【6】绘制出矩形，并显示最终结果
	rectangle( srcImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );
	rectangle( g_resultImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );

	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, g_resultImage );

}

/**
  * @brief     帮助信息函数
  * @param     None
  * @retval    None
  */
static void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//输出一些帮助信息
	printf("\t【模板匹配】程序~\n"); 
	printf("\n\n\t请调整滑动条观察图像效果\n\n");
	printf(  "\n\t滑动条对应的方法数值说明: \n\n" 
		"\t\t方法【0】- 平方差匹配法(SQDIFF)\n" 
		"\t\t方法【1】- 归一化平方差匹配法(SQDIFF NORMED)\n" 
		"\t\t方法【2】- 相关匹配法(TM CCORR)\n" 
		"\t\t方法【3】- 归一化相关匹配法(TM CCORR NORMED)\n" 
		"\t\t方法【4】- 相关系数匹配法(TM COEFF)\n" 
		"\t\t方法【5】- 归一化相关系数匹配法(TM COEFF NORMED)\n" );  
}
