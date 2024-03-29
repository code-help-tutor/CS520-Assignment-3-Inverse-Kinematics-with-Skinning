WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
MatrixXf A(2,2), B(3,2);
B << 2, 0,  0, 3, 1, 1;
A << 2, 0, 0, -2;
A = (B * A).cwiseAbs();
cout << A;