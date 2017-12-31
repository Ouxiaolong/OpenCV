//---------------------------------【头文件、命名空间包含部分】---------------------------
//          描述：包含程序所使用的头文件和命名空间
//-----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
#include <iostream>  

using namespace std;  
using namespace cv;  
  
Rect select;  
bool select_flag = false;  
Mat img, showImg;  
  
void A_on_Mouse(int event, int x, int y, int flags, void*param)//实现画矩形框  
{  
    Point p1, p2;  
    if (event == EVENT_LBUTTONDOWN)  
    {  
        select.x = x;  
        select.y = y;  
        select_flag = true;  
    }  
    else if (select_flag &&event == EVENT_MOUSEMOVE)  
    {  
        img.copyTo(showImg);  
        p1 = Point(select.x, select.y);  
        p2 = Point(x, y);  
        rectangle(showImg, p1, p2, Scalar(0, 255, 0), 2);  
        imshow("img", showImg);  
    }  
    else if (select_flag && event == EVENT_LBUTTONUP)  
    {  
        select_flag = false;  
    }  
}  
void B_on_Mouse(int event, int x, int y, int flags, void*param)//实现画矩形框并截图  
{  
  
    Point p1, p2;  
    switch (event)  
    {  
  
    case  EVENT_LBUTTONDOWN:  
    {
		select.x = x;  
		select.y = y;  
		select_flag = true;  
    }  
        break;  
    case EVENT_MOUSEMOVE:  
    {
		if (select_flag)  
		{
			img.copyTo(showImg); 
			p1 = Point(select.x, select.y);
			p2 = Point(x, y); 
			rectangle(showImg, p1, p2, Scalar(0, 255, 0), 2);
			imshow("img", showImg);
		}                        
    }   
        break;  
    case EVENT_LBUTTONUP:  
    {
		//显示框出的ROI  
		//改成Rect roi = Rect(p1, p2);为什么不对？  
		Rect roi = Rect(Point(select.x, select.y), Point(x, y));  
		if (roi.width && roi.height)//点一下时会没有反应 
		{
			Mat roiImg = img(roi); 
			imshow("roi", roiImg);
		}  
		select_flag = false;  
                                 
    }  
        break;  
    }  
}  
  
int main()  
{  
    img = imread("1.jpg", 1);  
    showImg = img.clone();  
    select.x = select.y = 0;  
    imshow("img", showImg);  
  
      
    while (1)  
    {  
        int key = waitKey(10);  
		switch (key)  
		{  
			case 'a': 
				setMouseCallback("img", A_on_Mouse, 0);  
			break;  
			case 'b':  
				setMouseCallback("img", B_on_Mouse, 0);  
			break;  
		}  
		if (key == 27||key=='q')  
		break;  
    }  
    waitKey(0);  
    return 0;  
}







