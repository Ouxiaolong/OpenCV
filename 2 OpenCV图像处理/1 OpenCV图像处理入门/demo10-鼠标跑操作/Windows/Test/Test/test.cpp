/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-7
  * @brief   鼠标操作
  ******************************************************************************
  * @attention
  * 本程序适用于OPenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
/**namespace********************************************************************/ 
using namespace cv;  
using namespace std;  
 
/**【全局函数声明部分】*********************************************************/ 
void OnMouseAction(int event,int x,int y,int flags,void *ustc);  //鼠标回调事件函数  

/**【全局变量】*****************************************************************/
int static times; //记录调用次数  
  
/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc,char*argv[])  
{  
	//输入矩阵（图像）
    Mat image=imread("1.jpg");  
    
	//显示矩阵（图像）
	imshow("image",image);  
    
	//鼠标操作
	setMouseCallback("image",OnMouseAction);  
    
	waitKey();  
    system("pause");  
}  
  
/**
  * @brief     鼠标回调函数
  * @param     event   事件  
               x       横坐标
			   y       纵坐标
			   flags   标志
			   ustc    传递参数
  * @retval    None
  */ 
void OnMouseAction(int event,int x,int y,int flags,void *ustc)  
{     
    times++;  
    cout<<"第 "<<times<<" 次回调鼠标事件"<<endl;  
    if(event==CV_EVENT_MOUSEMOVE)  
    {  
        cout<<"触发鼠标移动事件"<<endl;  
    }  
    if(event==CV_EVENT_LBUTTONDOWN)  
    {  
        cout<<"触发左键按下事件"<<endl;  
    }  
    if(event==CV_EVENT_LBUTTONUP)  
    {  
        cout<<"触发左键抬起事件"<<endl;  
    }  
    if(event==CV_EVENT_RBUTTONDOWN)  
    {  
        cout<<"触发右键按下事件"<<endl;  
    }  
    if(event==CV_EVENT_RBUTTONUP)  
    {  
        cout<<"触发右键抬起事件"<<endl;  
    }  
    if(event==CV_EVENT_LBUTTONDBLCLK)  
    {  
        cout<<"触发左键双击事件"<<endl;  
    }  
    if(event==CV_EVENT_RBUTTONDBLCLK)  
    {  
        cout<<"触发右键双击事件"<<endl;  
    }  
}

