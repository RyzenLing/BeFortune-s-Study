#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <cstdio>
using namespace std;
using namespace cv;
using namespace cv::dnn;
int main(int argc, char **argv)
{
    // 加载图像
    Mat img = imread("input.jpg");
    // 设置网络
    Net net = readNetFromCaffe("deploy.prototxt", "model.caffemodel");
    // 图像预处理
    Mat inputBlob = blobFromImage(img, 1.0, Size(224, 224), Scalar(), false);
    // 设置网络输入
    net.setInput(inputBlob);
    // 获取网络输出
    Mat result = net.forward();
    // 结果处理，从网络输出的矩阵中找出最大的概率值，并判断垃圾的类别
    Point maxLoc;
    minMaxLoc(result, 0, 0, 0, &maxLoc);
    int classIdx = maxLoc.x;
    string className = "";
    switch (classIdx)
    {
        case 0:
            className = "可回收垃圾";
            break;
        case 1:
            className = "有害垃圾";
            break;
        case 2:
            className = "湿垃圾";
            break;
        case 3:
            className = "干垃圾";
            break;
        default:
            break;
    }
//这里需要调动API来实现下一步控制电机的动作，代码待定
    return 0;
}
