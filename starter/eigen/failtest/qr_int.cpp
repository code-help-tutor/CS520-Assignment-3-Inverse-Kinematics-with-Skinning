WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "../Eigen/QR"

#ifdef EIGEN_SHOULD_FAIL_TO_BUILD
#define SCALAR int
#else
#define SCALAR float
#endif

using namespace Eigen;

int main()
{
  HouseholderQR<Matrix<SCALAR,Dynamic,Dynamic> > qr(Matrix<SCALAR,Dynamic,Dynamic>::Random(10,10));
}
