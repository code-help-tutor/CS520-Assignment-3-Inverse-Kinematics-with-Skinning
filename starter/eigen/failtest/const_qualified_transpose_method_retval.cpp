WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "../Eigen/Core"

#ifdef EIGEN_SHOULD_FAIL_TO_BUILD
#define CV_QUALIFIER const
#else
#define CV_QUALIFIER
#endif

using namespace Eigen;

void foo(CV_QUALIFIER Matrix3d &m){
    Transpose<Matrix3d> b(m.transpose());
}

int main() {}
