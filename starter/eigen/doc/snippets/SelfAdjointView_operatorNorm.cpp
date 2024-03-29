WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
MatrixXd ones = MatrixXd::Ones(3,3);
cout << "The operator norm of the 3x3 matrix of ones is "
     << ones.selfadjointView<Lower>().operatorNorm() << endl;
