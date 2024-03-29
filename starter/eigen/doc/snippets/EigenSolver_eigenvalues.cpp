WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
MatrixXd ones = MatrixXd::Ones(3,3);
EigenSolver<MatrixXd> es(ones, false);
cout << "The eigenvalues of the 3x3 matrix of ones are:" 
     << endl << es.eigenvalues() << endl;
