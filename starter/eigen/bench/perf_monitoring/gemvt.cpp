WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "gemv_common.h"

EIGEN_DONT_INLINE
void gemv(const Mat &A, Vec &B, const Vec &C)
{
  B.noalias() += A.transpose() * C;
}

int main(int argc, char **argv)
{
  return main_gemv(argc, argv, gemv);
}
