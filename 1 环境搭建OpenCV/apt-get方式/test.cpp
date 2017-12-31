/**
  ******************************************************************************
  * @file        test.cpp
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       apt-get方式安装OpenCV
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

/**namespace********************************************************************/
using namespace cv;
using namespace std;

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc,char **argv)
{
	Mat image ,image_gray;
	
	//读取图片
	image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
	if(argc != 2 || !image.data)
	{
		cout <<"No image data\n";
		return -1;
	}
	cvtColor(image,image_gray,CV_RGB2GRAY);
	
	//创建显示窗口
	namedWindow("image",CV_WINDOW_AUTOSIZE);
	namedWindow("image gray",CV_WINDOW_AUTOSIZE);  
     
	//显示图片
    imshow("image", image);  
    imshow("image gray", image_gray);  
     
    waitKey(0);  
    return 0;  
}