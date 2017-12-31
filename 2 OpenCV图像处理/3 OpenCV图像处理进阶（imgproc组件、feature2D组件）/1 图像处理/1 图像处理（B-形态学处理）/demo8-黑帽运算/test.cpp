/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   黑帽运算
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/    
#include <opencv2/opencv.hpp>  
#include <opencv2/highgui/highgui.hpp>  
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
       //载入原始图    
       Mat image = imread("1.jpg");  //素材图  
       //创建窗口    
       namedWindow("【原始图】黑帽运算");   
       namedWindow("【效果图】黑帽运算");   
       //显示原始图   
       imshow("【原始图】黑帽运算", image);   
       //定义核  
       Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
       //进行形态学操作  
       morphologyEx(image,image, MORPH_BLACKHAT, element);  
       //显示效果图   
       imshow("【效果图】黑帽运算", image);   
   
       waitKey(0);   
   
       return 0;   
}  
