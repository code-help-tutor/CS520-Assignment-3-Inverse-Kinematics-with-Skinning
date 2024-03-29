WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
MatrixXf matA(2,2); 
matA << 2, 0,  0, 2;
matA.noalias() = matA * matA;
cout << matA;
