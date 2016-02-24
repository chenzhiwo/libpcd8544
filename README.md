# libpcd8544
a simple library for pcd8544 on raspberry pi
一个简单的驱动pcd8544（Nokia5110）lcd屏的库，用于树莓派。
里面附带着有gfx库，从Adafruit的arduino库移植而来。
首先要使用 pcdInit()来对显示屏进行初始化，参数为各个引脚（使用wiringpi命名方式）。
然后调用gfxInit()，把pcd8544封装好的底层函数作为参数传入。

# 安装
libpcd8544依赖
* wiringPi
demo程序另外依赖
* libtftgfx
libtftgfx图形库可以从我的github中找到，推荐配合libtftgfx使用
依赖解决以后
```
make
make install
make demo
```
就可以运行``./demo``来测试程序了。
demo中的clk,din,dc,ce,rst引脚分别连接到21,22,23,24,25引脚，使用wiringPi引脚号
