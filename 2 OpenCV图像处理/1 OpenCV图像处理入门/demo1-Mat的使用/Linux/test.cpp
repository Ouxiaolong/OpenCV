/**
  ******************************************************************************
  * @file    test.cpp
  * @author  Bruceou
  * @version V1.0
  * @date    2017-7
  * @brief   Mat的使用
  ******************************************************************************
  * @attention
  * 本程序适用于OPenCV2和OpenCV3版本。
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
/**namespace********************************************************************/ 
using namespace std;
using namespace cv;

#define OPENCV3

/**
  * @brief     输出帮助信息
  * @param     None
  * @retval    None
  */
static void help()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------\n");
	//输出一些帮助信息
	printf("\n\n\t程序说明：\n\n\t此示例程序用于演示Mat类的格式化输出功能，输出风格可为：");
	printf("\n\n\t【1】OpenCV默认风格");
	printf("\n\n\t【2】Python风格");
	printf("\n\n\t【3】逗号分隔风格");
	printf("\n\n\t【4】Numpy风格");
	printf("\n\n\t【5】C语言风格");
	printf("\n\n\t【6】matlab风格\n\n");
	printf("\n  -------------------------------------------------------------\n");
}

/**
  * @brief     主函数
  * @param     argc 命令行参数个数
               argv 命令行参数
  * @retval    int
  */
int main(int argc, char** argv)
{

#ifdef VS12
	/*VS可调用*/
	//改变控制台的前景色和背景色
	system("color 8F"); 
	//显示帮助文字
	help();
	
#else	
	/*树莓派-Linux可调用*/
	//显示帮助文字
	CommandLineParser parser(argc, argv, "{help h||}");
    if (parser.has("help"))
    {
        help();
        return 0;
    }

#endif	
	
	Mat I = Mat::eye(4, 4, CV_64F);
	I.at<double>(1,1) = CV_PI;
	cout << "\nI = " << I << ";\n" << endl;

	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

#ifdef OPENCV3
	cout << "r (OpenCV默认风格) = " << r << ";" << endl << endl; 
    cout << "r (Python风格) = " << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    cout << "r (Numpy风格) = " << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;
    cout << "r (逗号分隔风格) = " << format(r, Formatter::FMT_CSV) << ";" << endl << endl;
    cout << "r (c语言风格) = " << format(r, Formatter::FMT_C) << ";" << endl << endl;
	cout << "r (matlab风格) = " << format(r, Formatter::FMT_MATLAB) << ";" << endl << endl;
#else
	cout << "r (OpenCV默认风格) = " << r << ";" << endl << endl;
	cout << "r (Python风格) = " << format(r,"python") << ";" << endl << endl;
	cout << "r (Numpy风格) = " << format(r,"numpy") << ";" << endl << endl;
	cout << "r (逗号分隔风格) = " << format(r,"csv") << ";" << endl<< endl;
	cout << "r (C语言风格) = " << format(r,"C") << ";" << endl << endl;
	cout << "r (matlab风格) =" << format(r, "MATLAB") << ";" << endl << endl;
	
#endif	
	
	Point2f p(6, 2);
	cout << "【2维点】p = " << p << ";\n" << endl;

	Point3f p3f(8, 2, 0);
	cout << "【3维点】p3f = " << p3f << ";\n" << endl;

	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	cout << "【基于Mat的vector】shortvec = " << Mat(v) << ";\n"<<endl;

	vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f((float)(i * 5), (float)(i % 7));

	cout << "【二维点向量】points = " << points<<";";

	getchar();//按任意键退出
	return 0;
}
