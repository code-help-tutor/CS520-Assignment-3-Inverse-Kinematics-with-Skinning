WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <Eigen/Core>
#include <iostream>
#include <random>

using namespace Eigen;

int main() {
  std::default_random_engine generator;
  std::poisson_distribution<int> distribution(4.1);
  auto poisson = [&] () {return distribution(generator);};

  RowVectorXi v = RowVectorXi::NullaryExpr(10, poisson );
  std::cout << v << "\n";
}
