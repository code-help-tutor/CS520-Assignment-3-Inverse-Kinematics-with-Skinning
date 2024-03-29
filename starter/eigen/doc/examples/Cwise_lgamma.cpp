WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <Eigen/Core>
#include <unsupported/Eigen/SpecialFunctions>
#include <iostream>
using namespace Eigen;
int main()
{
  Array4d v(0.5,10,0,-1);
  std::cout << v.lgamma() << std::endl;
}
