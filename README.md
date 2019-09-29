# OpenCV Example 工程使用指南

## 从GitHub仓库下载

1. 打开浏览器，进入[OpenCV_examples](https://github.com/Baiyun-u-smartAI/OpenCV_examples)的仓库<br/>![](https://ae01.alicdn.com/kf/Hde48b6c40fdb48bcbc9e4922b8737d92Q.png)<br/>

2. 在网页上（见上图），点击<font color="green">Clone and download</font>>><font color="blue">Download ZIP</font>，将GitHub仓库下载到本地。

## 解压并修改CMakeLists.txt

1. <span name="path">解压</span><br/>![](https://ae01.alicdn.com/kf/Hb2de70e3a1db4dcabdf9957732dc7982p.png)<br/>

2. 找到CMakeLists.txt 文件<br/>![](https://ae01.alicdn.com/kf/Hff63f79c7645434cb5c120035198dd19U.png)<br/>

3. 替换OpenCV路径：<br/>利用替换，搜索**D:\\\\opencv411\\\\build\\\\install**<br/>替换成本电脑OpenCV所在目录的build\\\install路径，注意一定要把 **\\** 写成 <font color="red"><b>\\\\</b></font> <br/>![](https://ae01.alicdn.com/kf/Hf4a96e42070e47ab9fa63615efc9610fJ.png)<br/>（下图在Notepad++上编辑的界面）<br/>![](https://ae01.alicdn.com/kf/Hcdf374ed9a5b4c9bad97ea7de41ff3f23.png)<br/>

## 从CLion导入GitHub仓库工程

1. 导入模块的方法：<br/>
![](https://ae01.alicdn.com/kf/H114d316377af49e68dba41cdf23d3ab46.png)<br/>（在之前没打开过任何工程的时候>>import project from sources）<br/>
![](https://ae01.alicdn.com/kf/H7dc5681118ee4fb1b238e7d3e0b9f971l.png)<br/>（在之前有打开过任何工程的时候）

2. 输入之前[解压后GitHub仓库的路径](#path)<br/>
![](https://ae01.alicdn.com/kf/He17347e6bdb64eb6b17d06098242386dt.png)

## 测试课本程序运行

1. 修改<font color="blue">main.cpp</font>文件<br/>![](https://ae01.alicdn.com/kf/Ha4ef95afc9e941038e9327b522d83e5ba.png)<br/>
原<font color="blue">main.cpp</font>文件内容：<br/>
```cpp
#include "OpenCV_example.hpp"
#include <iostream>


int main() {


    return 0;
}
```

2. 运行一个程序案例：<br/>假设要运行课本案例的<font color="blue">Logo.cpp</font>，在<font color="blue">main.cpp</font>文件的<font color="red">main函数</font>里写上一行：`run_logo();`

3. 设置运行参数（run>>Edit Configurations），讲working directory设置为当前工程的路径：<br/>

![](https://ae01.alicdn.com/kf/He54ec77f7b914b089cc8fda37ea002abA.png)<br/>
![](https://ae01.alicdn.com/kf/Hd8a96a7130f442f48d368332e1c366fcK.png)<br/>
![](https://ae01.alicdn.com/kf/H91ed51fc020c491180faf8620198c691Y.png)<br/>
3. 重新编译配置：<br/>
![](https://ae01.alicdn.com/kf/H3e8f3160a8b1465aafdd6245f0b3af1aw.png)<br/>
4. 运行，结果如下：<br/>
![](https://ae01.alicdn.com/kf/H9bb321335dfd41838ae6805c10372b6aw.png)<br/>
![](https://ae01.alicdn.com/kf/H481d2ad454eb40c9a39057eb67d6b6deT.png)<br/>
![](https://ae01.alicdn.com/kf/Hae694e815c3c4fb894b3c758dd5417ffb.png)<br/>

## *查看GitHub内各c++文件被我修改的内容

![](https://ae01.alicdn.com/kf/H67ac481c13ba4a11a845a736ac56122e4.png)<br/>
![](https://ae01.alicdn.com/kf/Ha8d571253ce0475faa09374320d6601br.png)<br/>
![](https://ae01.alicdn.com/kf/Hf2a469fe4517492aa926fc4957e3c4dey.png)<br/>