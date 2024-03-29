WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "datatypes.h"    

void d_cnjg(doublecomplex *r, doublecomplex *z) {
    r->r = z->r;
    r->i = -(z->i);
}
