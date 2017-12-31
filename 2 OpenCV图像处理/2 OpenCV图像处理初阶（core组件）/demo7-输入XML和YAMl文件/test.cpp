/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-11
  * @brief   输入XML和YAMl文件
  ******************************************************************************
  * @attention
  * 本程序适用于OpenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/     
#include "opencv2/opencv.hpp"  
#include <time.h> 
 /**namespace*******************************************************************/
using namespace cv;  

/**
  * @brief     帮助信息
  * @param     None
  * @retval    None
  */
void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main (int argc, char **argv)  
{  
	//改变console字体颜色
	system("color 5F"); 

	ShowHelpText();

	//初始化
	FileStorage fs("test.yaml", FileStorage::WRITE);  

	//开始文件写入
	fs << "frameCount" << 5;  
	time_t rawtime; time(&rawtime);  
	fs << "calibrationDate" << asctime(localtime(&rawtime));  
	
	Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);  
	Mat distCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);  
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;  
	
	fs << "features" << "[";  
	for( int i = 0; i < 3; i++ )  
	{  
		int x = rand() % 640;  
		int y = rand() % 480;  
		uchar lbp = rand() % 256;  

		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";  
		for( int j = 0; j < 8; j++ )  
			fs << ((lbp >> j) & 1);  
		fs << "]" << "}";  
	}  
	fs << "]";  
	fs.release();  

	printf("\n文件读写完毕，请在工程目录下查看生成的文件~");
	getchar();

	return 0;  
}  
