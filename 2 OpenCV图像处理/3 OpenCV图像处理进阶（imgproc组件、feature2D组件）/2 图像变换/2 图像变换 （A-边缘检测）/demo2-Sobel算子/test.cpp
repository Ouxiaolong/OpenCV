/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   Sobel算子进行图像变换
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
    //【0】创建 grad_x 和 grad_y 矩阵  
    Mat grad_x, grad_y;  
    Mat abs_grad_x, abs_grad_y,dst;  
  
    //【1】载入原始图    
    Mat src = imread("lena.jpg");  //素材图  
  
    //【2】显示原始图   
    imshow("【原始图】sobel边缘检测", src);   
  
    //【3】求 X方向梯度  
    Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );  
    convertScaleAbs( grad_x, abs_grad_x );  
    imshow("【效果图】 X方向Sobel", abs_grad_x);   
  
    //【4】求Y方向梯度  
    Sobel( src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );  
    convertScaleAbs( grad_y, abs_grad_y );  
    imshow("【效果图】Y方向Sobel", abs_grad_y);   
  
    //【5】合并梯度(近似)  
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );  
    imshow("【效果图】整体方向Sobel", dst);   
  
    waitKey(0);   
    return 0;   
}  