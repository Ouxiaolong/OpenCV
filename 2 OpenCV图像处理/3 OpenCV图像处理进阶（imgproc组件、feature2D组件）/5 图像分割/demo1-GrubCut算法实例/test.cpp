/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   GrubCut算法实例
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
/**namespace********************************************************************/
using namespace cv;
using namespace std;

/**【全局函数声明】***********************************************************/
static void ShowHelpText();

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char** argv)
{
	//【0】改变console字体颜色
	system("color 3F");

	//【0】显示帮助文字
	ShowHelpText();

	//【1】载入原图并显示
    Mat img = imread("1.jpg",1); // 读入图像
    Mat bgModel, fgModel, mask;
    Rect rect;
    rect.x = 20;
    rect.y = 30;
    rect.width = img.cols - (rect.x << 1);
    rect.height = img.rows - (rect.y << 1);
    //rectangle(img, rect, Scalar(0, 0, 255), 3, 8, 0);//用矩形画矩形窗  

	//【2】使用grabCut算法分割
    //循环执行3次，这个可以自己设置
    grabCut(img, mask, rect, bgModel, fgModel, 3, GC_INIT_WITH_RECT);
    compare(mask, GC_PR_FGD, mask, CMP_EQ);
    Mat foreground(img.size(), CV_8UC3, Scalar(255, 255, 255));
    img.copyTo(foreground, mask);
    
	//【3】显示分割前后的图像
	imshow("分割前的图像", img);
	imshow("分割后的图像", foreground);

    waitKey(0);

    return 0;
}


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

}
