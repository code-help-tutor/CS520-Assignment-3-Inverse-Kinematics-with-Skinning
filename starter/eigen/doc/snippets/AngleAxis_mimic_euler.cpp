WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
Matrix3f m;
m = AngleAxisf(0.25*M_PI, Vector3f::UnitX())
  * AngleAxisf(0.5*M_PI,  Vector3f::UnitY())
  * AngleAxisf(0.33*M_PI, Vector3f::UnitZ());
cout << m << endl << "is unitary: " << m.isUnitary() << endl;
