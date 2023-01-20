# linux 搭建OpenCVSharp（x86-64 debian）

1. 下载dotnet软件，[官方链接]([.NET 下载(Linux、macOS 和 Windows) (microsoft.com)](https://dotnet.microsoft.com/zh-cn/download/dotnet))

   ```bash
   wget https://download.visualstudio.microsoft.com/download/pr/d3e46476-4494-41b7-a628-c517794c5a6a/6066215f6c0a18b070e8e6e8b715de0b/dotnet-sdk-6.0.402-linux-x64.tar.gz
   ```

2. 解压，配置环境：

   ```bash
   tar vxf dotnet-sdk-6.0.402-linux-x64.tar.gz
   export DOTNET_ROOT=[dotnet文件所在路径]
   export PATH=$PATH:$DOTNET_ROOT
   dotnet new --list #测试dotnet
   ```

3. 新建工程：

   ```bash
   mkdir ../dotnet_project
   cd ../dotnet_project
   dotnet new console --name test
   cd test
   ```

4. 运行工程：

   ```bash
   dotnet run --project=./
   ```

5. 配置OpenCVSharp环境：

   ```bash
   dotnet add package OpenCvSharp4 --version 4.3.0.20200524
   dotnet add package OpenCvSharp4.runtime.debian.10-amd64 --version 4.3.0.20200424
   ```

6. 查看so文件依赖：

   ```bash
   ldd ./bin/Debug/net6.0/runtimes/linux-x64/nativelibOpenCvSharpExtern.so | grep found
   ```
   如果出现**libdc1394.so.22 => not found**，需要编译安装`libdc1394-2.2.3`

   ```bash
   mkdir $home/dc1394
   cd $home/dc1394
   wget http://files.alex4ai.top/libdc1394-2.2.3.tar.gz
   tar libdc1394-2.2.3.tar.gz
   cd libdc1394-2.2.3
   ./configure --prefix=$home/dc1394/build
   make -j 4
   make install
   cd $home/dc1394/build/lib
   sudo cp -f libdc1394.22* /usr/lib/x86_64-linux-gnu/
   cd $home/test
   ldd ./bin/Debug/net6.0/runtimes/linux-x64/nativelibOpenCvSharpExtern.so | grep found #如果这个命令没有输出，证明依赖已经解决
   ```

7. 修改cs源码，并测试