# 🚀smart-home
## 初期环境搭建
* 如何烧入Linux系统到全志开发板【香橙派开发文档详解】
* 网络搭建，可以通过一个路由器实现ftp服务，也就是通过filezilla，同时也可以使用虚拟机中`PUTTY`服务实现与开发板相连接，既然可以通过`putty`那么是不是也可以使用**scp**命令去传输开发文件。![image-20231222225445697](./img/连接.png)

* 同时要记得一直`wiringOP`这个库，因为树莓派是专用的，其他开发板没有这个硬件信息，所以移植`wiringPi`这个库没有用。

* 编译选项

  ````
  gcc *.c -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt
  //  *.c 所有.c文件
  //  需要链接库
  sudo ./a.out
  ````

## 问题

* 发现一个问题，就是通过`filezilla`传输**wiringOP**库的时候会出现不能运行的问题，这可能是x86架构和arm架构下的权限问题还是什么，反转就是不能正常运行。那么通过在开发板中在`github`上克隆下来的可以正常运行。