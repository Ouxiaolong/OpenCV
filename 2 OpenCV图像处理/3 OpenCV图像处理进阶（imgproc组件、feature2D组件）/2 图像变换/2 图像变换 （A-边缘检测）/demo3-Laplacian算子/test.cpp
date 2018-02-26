/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   Laplace算子进行图像变换
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
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
    //【0】变量的定义  
    Mat src,src_gray,dst, abs_dst;  
  
    //【1】载入原始图    
    src = imread("lena.jpg");  //素材图  
  
    //【2】显示原始图   
    imshow("【原始图】图像Laplace变换", src);   
  
    //【3】使用高斯滤波消除噪声  
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );  
  
    //【4】转换为灰度图  
    cvtColor( src, src_gray, CV_RGB2GRAY );  
  
    //【5】使用Laplace函数  
    Laplacian( src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );  
  
    //【6】计算绝对值，并将结果转换成8位  
    convertScaleAbs( dst, abs_dst );  
  
    //【7】显示效果图  
    imshow( "【效果图】图像Laplace变换", abs_dst );  
  
    waitKey(0);   
  
    return 0;   
}  
 