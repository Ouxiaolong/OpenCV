/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   漫水填充
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/       
#include <opencv2/opencv.hpp>    
#include <opencv2/imgproc/imgproc.hpp>    
  
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
    Mat src = imread("1.jpg");  //素材图 
    imshow("【原始图】",src);  
    Rect ccomp;  
    
	//漫水填充处理
	floodFill(src, Point(0,0), Scalar(255, 255,255), &ccomp, Scalar(15, 15, 15),Scalar(18,18,18));  
    imshow("【效果图】",src);  
    
	waitKey(0);  
    
	return 0;      
}    
