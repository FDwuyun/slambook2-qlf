#include <Eigen/Core>
#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
    double ar = 1.0, br = 2.0, cr = 1.0;   // 真实参数值
    double ae = 2.0, be = -1.0, ce = 5.0;  // 估计参数值
    int N = 100;                           // 数据点
    double w_sigma = 1.0;                  // 噪声Sigma值
    double inv_sigma = 1.0 / w_sigma;
    cv::RNG rng;  // OpenCV随机数产生器

    vector<double> x_data, y_data;  // 数据
    for (int i = 0; i < N; i++) {
        double x = i / 100.0;
        x_data.push_back(x);
        /*生成一个服从均值为0，标准差为w_sigma * w_sigma的高斯分布随机数*/
        y_data.push_back(exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma * w_sigma));
    }

    // 开始Gauss-Newton迭代
    int iterations = 100;           // 迭代次数
    double cost = 0, lastCost = 0;  // 本次迭代的cost和上一次迭代的cost

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (int iter = 0; iter < iterations; iter++) {
        Matrix3d H = Matrix3d::Zero();  // Hessian = J^T W^{-1} J in Gauss-Newton
        Vector3d b = Vector3d::Zero();  // bias
        cost = 0;

        for (int i = 0; i < N; i++) {
            double xi = x_data[i], yi = y_data[i];  // 第i个数据点
            double error = yi - exp(ae * xi * xi + be * xi + ce);
            Vector3d J;                                          // 雅可比矩阵
            J[0] = -xi * xi * exp(ae * xi * xi + be * xi + ce);  // de/da
            J[1] = -xi * exp(ae * xi * xi + be * xi + ce);       // de/db
            J[2] = -exp(ae * xi * xi + be * xi + ce);            // de/dc
            /*更新Hessian矩阵*/
            H += inv_sigma * inv_sigma * J * J.transpose();
            b += -inv_sigma * inv_sigma * error * J;

            cost += error * error;
        }

        // 求解线性方程 Hx=b
        /*
        H.ldlt() ：表示对矩阵H进行LDL^T分解（Cholesky 分解的一种特例），将矩阵H分解为一个单位下三角矩阵L、D是一个对角线矩阵和其转置矩阵的乘积，即H = LDL^T。 
        solve(b) ：表示使用LDLT分解的结果来解决线性方程组H * dx = b，得到dx。
        */
        Vector3d dx = H.ldlt().solve(b);
        if (isnan(dx[0])) {
            cout << "result is nan!" << endl;
            break;
        }

        if (iter > 0 && cost >= lastCost) {
            cout << "cost: " << cost << ">= last cost: " << lastCost << ", break." << endl;
            break;
        }

        ae += dx[0];
        be += dx[1];
        ce += dx[2];

        lastCost = cost;

        cout << "total cost: " << cost << ", \t\tupdate: " << dx.transpose() << "\t\testimated params: " << ae << "," << be << "," << ce << endl;
    }
    /*
    total cost: 101.937,            update:   3.4312e-06 -4.28555e-06  1.08348e-06          estimated params: 0.890912,2.1719,0.943629
    total cost: 101.937,            update: -2.01204e-08  2.68928e-08 -7.86602e-09          estimated params: 0.890912,2.1719,0.943629
    cost: 101.937>= last cost: 101.937, break.
    */
    
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

    cout << "estimated abc = " << ae << ", " << be << ", " << ce << endl;
    return 0;
}
