/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   尺寸放大
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
    //载入原始图     
    Mat srcImage = imread("1.jpg");  //素材图  
    Mat tmpImage,dstImage;//临时变量和目标图的定义  
    tmpImage=srcImage;//将原始图赋给临时变量  
  
    //显示原始图    
    imshow("【原始图】", srcImage);    
    //进行向上取样操作  
    pyrUp( tmpImage, dstImage, Size( tmpImage.cols*2, tmpImage.rows*2 ) );  
    //显示效果图    
    imshow("【效果图】", dstImage);    
  
    waitKey(0);    
  
    return 0;    
}  
