/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   图像的翻转
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

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main (int argc, char **argv)  
{  
    Mat image;  
	//【1】读入图像
    image=imread("1.jpg");  
    Mat result;
	
	//【2】翻转操作	
    flip(image,result,0);//1表示水平反转  0表示垂直反转  
    
	//【3】显示结果
	namedWindow("My window");  
    imshow("My window",image);  
    namedWindow("output Image");  
    imshow("output Image",result);  
    waitKey(0);  
    return 0;  
}
