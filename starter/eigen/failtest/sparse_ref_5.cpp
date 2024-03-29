WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "../Eigen/Sparse"

using namespace Eigen;

void call_ref(Ref<SparseMatrix<float> > a) { }

int main()
{
  SparseMatrix<float> a(10,10);
  SparseMatrixBase<SparseMatrix<float> > &ac(a);
#ifdef EIGEN_SHOULD_FAIL_TO_BUILD
  call_ref(ac);
#else
  call_ref(ac.derived());
#endif
}
