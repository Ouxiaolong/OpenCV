/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   膨胀与腐蚀
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/   
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

/**namespace*******************************************************************/
using namespace std;
using namespace cv;


/**【全局变量声明部分】********************************************************/
Mat g_srcImage, g_dstImage;//原始图和效果图
int g_nTrackbarNumer = 0;//0表示腐蚀erode, 1表示膨胀dilate
int g_nStructElementSize = 3; //结构元素(内核矩阵)的尺寸


/**【全局函数声明部分】********************************************************/
void Process();//膨胀和腐蚀的处理函数
void on_TrackbarNumChange(int, void *);//回调函数
void on_ElementSizeChange(int, void *);//回调函数

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main (int argc, char **argv)  
{
	//改变console字体颜色
	system("color 5E");  

	//载入原图
	g_srcImage = imread("1.jpg");
	if( !g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！ \n"); return false; }
	
	//显示原始图
	namedWindow("【原始图】");
	imshow("【原始图】", g_srcImage);
	
	//进行初次腐蚀操作并显示效果图
	namedWindow("【效果图】");
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));
	erode(g_srcImage, g_dstImage, element);
	imshow("【效果图】", g_dstImage);

	//创建轨迹条
	createTrackbar("腐蚀/膨胀", "【效果图】", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "【效果图】", &g_nStructElementSize, 21, on_ElementSizeChange);

	//输出一些帮助信息
	cout<<endl<<"\t嗯。运行成功，请调整滚动条观察图像效果~\n\n"
		<<"\t按下“q”键时，程序退出~!\n"
		<<"\n\n\t\t\t\t";

	//轮询获取按键信息，若下q键，程序退出
	while(char(waitKey(1)) != 'q') {}

	return 0;
}

/**
  * @brief     自定义的腐蚀和膨胀操作
  * @param     None
  * @retval    None
  */
void Process() 
{
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));

	//进行腐蚀或膨胀操作
	if(g_nTrackbarNumer == 0) {    
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	//显示效果图
	imshow("【效果图】", g_dstImage);
}

/**
  * @brief     腐蚀和膨胀之间切换开关的回调函数
  * @param     int
               void
  * @retval    None
  */
/*******************************************************************************
  *【on_TrackbarNumChange( )函数】
  * 描述：
  ******************************************************************************/
void on_TrackbarNumChange(int, void *) 
{
	//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}

/**
  * @brief     腐蚀和膨胀操作内核改变时的回调函数
  * @param     int
               void
  * @retval    None
  */
void on_ElementSizeChange(int, void *)
{
	//内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}