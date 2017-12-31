/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-7
  * @brief   常用数据结构和函数
  ******************************************************************************
  * @attention
  * 本程序适用于OPenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>  
/**namespace********************************************************************/ 
using namespace std;
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
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR );
    if (argc != 2 || !image.data)
    {
        cout << "No image data\n";
        return -1;
    }
    Mat edge,grayimage;

    //创建与image同等大小的矩阵
    grayimage.create(image.size(),image.type());
    cvtColor(image,grayimage,CV_BGR2GRAY);

    //滤波处理
    blur(grayimage,edge,Size(3,3));
    
	//边缘提取
	Canny(edge,edge,3,9,3);

	//输出图像
    imwrite("edge.jpg",edge);
    waitKey(0);//按下任意键结束

    return 0;
}

