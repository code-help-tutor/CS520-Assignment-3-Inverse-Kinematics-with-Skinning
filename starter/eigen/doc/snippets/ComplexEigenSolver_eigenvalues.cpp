WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
MatrixXcf ones = MatrixXcf::Ones(3,3);
ComplexEigenSolver<MatrixXcf> ces(ones, /* computeEigenvectors = */ false);
cout << "The eigenvalues of the 3x3 matrix of ones are:" 
     << endl << ces.eigenvalues() << endl;
