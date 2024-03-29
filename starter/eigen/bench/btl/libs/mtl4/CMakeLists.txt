WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com

find_package(MTL4)
if (MTL4_FOUND)
  include_directories(${MTL4_INCLUDE_DIR})
  btl_add_bench(btl_mtl4 main.cpp)
endif (MTL4_FOUND)
