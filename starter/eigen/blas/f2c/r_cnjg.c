WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "datatypes.h"    

void r_cnjg(complex *r, complex *z) {
    r->r = z->r;
    r->i = -(z->i);
}
