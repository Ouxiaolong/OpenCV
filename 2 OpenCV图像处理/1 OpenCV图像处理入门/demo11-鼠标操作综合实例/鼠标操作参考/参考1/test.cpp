//---------------------------------【头文件、命名空间包含部分】---------------------------
//          描述：包含程序所使用的头文件和命名空间
//-----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
#include <iostream>  
using namespace std;  
using namespace cv;  

//宏定义
//#define IF
#define WINDOW "原图"  

//全局变量
Mat g_srcImage,g_dstImage;  
Point previousPoint;  
bool P = false;  

//函数声明
void On_mouse(int event, int x, int y, int flags, void*);  

//主函数
int main(int argc,char **argv)  
{  
    g_srcImage = imread("1.jpg", 1);  
    imshow(WINDOW, g_srcImage);  
    setMouseCallback(WINDOW, On_mouse, 0);  
  
    waitKey(0);  
    return 0;  
}  


#ifdef IF

void On_mouse(int event, int x, int y, int flags, void*)  
{  
    /*if (event == EVENT_LBUTTONUP ||!( flags&EVENT_FLAG_LBUTTON)) 
    { 
        previousPoint = Point(-1, -1); 
    }*/  
    if (event == EVENT_LBUTTONDOWN)  
    {  
        previousPoint = Point(x, y);  
    }  
    else if (event == EVENT_MOUSEMOVE && (flags&EVENT_FLAG_LBUTTON))  
    {  
        Point pt(x, y);  
        line(g_srcImage, previousPoint, pt, Scalar(0,0,255), 2, 5, 0);  
        previousPoint = pt;  
        imshow(WINDOW, g_srcImage);  
    }  
}

#else
	
void On_mouse(int event, int x, int y, int flags, void*)  
{  
    switch (event)  
    {  
    case EVENT_LBUTTONUP:  
    {
		P = false;  
    }  
        break;  
    case EVENT_LBUTTONDOWN:  
    {
		previousPoint = Point(x, y);          
		P = true;  
    }  
        break;  
  
    case EVENT_MOUSEMOVE :  
    {
		if(P) 
		{
			Point pt(x, y);                     
			line(g_srcImage, previousPoint, pt, Scalar(0,0,255), 2, 5, 0);  
			previousPoint = pt;  
			imshow(WINDOW, g_srcImage);  
		}  
    }  
        break;  
    }  
}

#endif






