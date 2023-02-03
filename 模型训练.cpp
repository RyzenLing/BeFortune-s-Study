#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <iostream>
#include <cstdio>
using namespace std;
using namespace cv;
using namespace cv::dnn;
int main(int argc, char **argv)
{
    // 加载训练数据集
    vector<Mat> imgs;
    vector<int> labels;
    for (int i = 0; i < numImgs; i++)
    {
        imgs.push_back(imread(format("img_%d.jpg", i)));
        labels.push_back(imgLabels[i]);
    }
    // 设置网络结构
    Net net = dnn::readNetFromCaffe("deploy.prototxt");
    // 设置训练参数
    SolverParameter solverParam;
    solverParam.train_net = "train.prototxt";
    solverParam.base_lr = 0.0001 ;
//这个是学习率，是神经网络学习的重要参数，我们小组打算使用余弦退火算法获取学习率。
    solverParam.momentum = 0.9;
    solverParam.weight_decay = 0.0005;
    solverParam.lr_policy = "step";
    solverParam.stepsize = 10000;
    solverParam.gamma = 0.1;
    solverParam.max_iter = 100000;
    solverParam.snapshot = 1000;
//这里一定要设置小一点的数值，防止训练突然中止导致数据损失过多。
    solverParam.snapshot_prefix = "model";
    solverParam.solver_mode = SolverParameter_SolverMode_GPU;
    // 训练网络
    SGDSolver<float> solver(solverParam);
    solver.net = net;
    solver.test_nets.push_back(net);
    solver.step(1);
    while (solver.iter() < solverParam.max_iter)
    {
        int i = solver.iter() % numImgs;
        solver.net->setInput(blobFromImage(imgs[i], 1.0, Size(224, 224), Scalar(), false));
        solver.net->setLabel(lab
