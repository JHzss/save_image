# save_image

需要修改的地方：
1.CMakeLists.txt "OpenCV_DIR"
2.node.cpp   name_rgb name_depth namer_txt named_txt
3.在主文件夹下创建如下文件夹
data
├── depth
└── rgb

文件说明：
rgb图片  ： ～/data/rgb
depth图片： ～/data/depth
rgb图片时间戳  ： ～/data/name_r.txt
depth图片时间戳： ～/data/name_d.txt