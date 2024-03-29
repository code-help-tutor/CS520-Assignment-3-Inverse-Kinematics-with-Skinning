WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
Matrix3f m;
m.row(0) << 1, 2, 3;
m.block(1,0,2,2) << 4, 5, 7, 8;
m.col(2).tail(2) << 6, 9;		    
std::cout << m;
