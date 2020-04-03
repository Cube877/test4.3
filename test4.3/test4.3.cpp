// test4.3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("E:\\Picture\\Camera Roll\\1.jpg");
	Mat grayMat;
	Mat canny1, canny2;
	Mat sobelx, sobely;
	Mat dst1, dst2, dst3;
	cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	//1
	Sobel(srcMat, sobelx, CV_16SC1, 1, 0, 3);
	Sobel(srcMat, sobely, CV_16SC1, 0, 1, 3);
	Canny(sobelx, sobely, canny1, 30, 60);
	Canny(srcMat, canny2, 30, 60);
	//2
	float angle = -10.0, scale = 1;
	Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	const Mat affine_matrix1 = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcMat, dst1, affine_matrix1, srcMat.size());
	//3
	const Point2f src_pt[] = {
		Point2f(200, 200),
		Point2f(250, 200),
		Point2f(200, 100)
	};
	const Point2f dst_pt[] = {
		Point2f(300, 300),
		Point2f(320, 300),
		Point2f(350, 200)
	};
	const Mat affine_matrix2 = getAffineTransform(src_pt, dst_pt);
	warpAffine(srcMat, dst2, affine_matrix2, srcMat.size());
	//4
	const Point2f pst1[] = {
		Point2f(150, 150),
		Point2f(150, 300),
		Point2f(350, 300),
		Point2f(350, 150)
	};
	const Point2f pst2[] = {
		Point2f(200, 150),
		Point2f(200, 300),
		Point2f(340, 270),
		Point2f(340, 180)
	};
	Mat perspective_matrix = getPerspectiveTransform(pst1, pst2);
	warpPerspective(srcMat, dst3, perspective_matrix, srcMat.size());

	imshow("原图", srcMat);
	imshow("边缘检测1", canny1);   
	imshow("边缘检测2", canny2);
	imshow("旋转、缩放", dst1);
	imshow("仿射变换", dst2);
	imshow("投影变换", dst3);
	waitKey();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
