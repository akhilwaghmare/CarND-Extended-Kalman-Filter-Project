#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
    VectorXd rmse(4);
    rmse << 0,0,0,0;
    
    if ((estimations.size() == 0) || (estimations.size() != ground_truth.size())) {
        cout << "Error when calculating RMSE" << endl;
        return rmse;
    }
    
    for (int i=0; i < estimations.size(); i++) {
        VectorXd residual = estimations[i] - ground_truth[i];
        residual = residual.array()*residual.array();
        rmse += residual;
    }
    
    rmse = rmse/estimations.size();
    rmse = rmse.array().sqrt();
    
    return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
    MatrixXd Hj(3,4);
    
    float px = x_state(0);
    float py = x_state(1);
    float vx = x_state(2);
    float vy = x_state(3);
    
    // Useful constants in calculation
    float c1 = px*px + py*py;
    float c2 = sqrt(c1);
    float c3 = c1*c2;
    float c4 = vx*py - vy*px;
    float c5 = vy*px - vx*py;
    
    if (c1 == 0) {
        cout << "Error when calculating Jacobian" << endl;
        return Hj;
    }
    
    Hj << px/c2, py/c2, 0, 0,
          -py/c1, px/c1, 0, 0,
          py*c4/c3, px*c5/c3, px/c2, py/c2;
    
    return Hj;
}
