WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com

find_package(Tvmet)
if (TVMET_FOUND)
  include_directories(${TVMET_INCLUDE_DIR})
  btl_add_bench(btl_tvmet main.cpp OFF)
endif (TVMET_FOUND)
