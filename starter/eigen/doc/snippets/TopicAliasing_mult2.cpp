WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
MatrixXf matA(2,2), matB(2,2); 
matA << 2, 0,  0, 2;

// Simple but not quite as efficient
matB = matA * matA;
cout << matB << endl << endl;

// More complicated but also more efficient
matB.noalias() = matA * matA;
cout << matB;
