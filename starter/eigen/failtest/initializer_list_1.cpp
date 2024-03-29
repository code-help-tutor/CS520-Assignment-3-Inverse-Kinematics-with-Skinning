WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "../Eigen/Core"

#ifdef EIGEN_SHOULD_FAIL_TO_BUILD
#define ROWS Dynamic
#else
#define ROWS 3
#endif

using namespace Eigen;

int main()
{
  Matrix<int, ROWS, 1> {1, 2, 3};
}
