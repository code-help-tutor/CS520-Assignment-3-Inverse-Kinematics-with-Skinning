WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
RowVector4i v = RowVector4i::Random();
cout << "Here is the vector v:" << endl << v << endl;
cout << "Here is v.tail(2):" << endl << v.tail<2>() << endl;
v.tail<2>().setZero();
cout << "Now the vector v is:" << endl << v << endl;
