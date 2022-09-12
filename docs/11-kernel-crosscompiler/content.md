---
layout: default
title: Lesson 11 - Content
nav_order: 99
parent: Lesson 11
---

*您可能需要事先搜索的概念：交叉编译器*


**目标：创建一个开发环境来构建内核**

注解将针对windows用户  
最下面将是给你们的说明，原文部分用处不大

如果您使用的是Mac，则需要立即执行此过程。否则，它可能会等待多上几节课。

无论如何，一旦我们跳转到更高层次的开发，您将需要一个交叉编译器

语言，即C语言[阅读原因](http://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F)

我将在OSDev维基上修改说明(http://wiki.osdev.org/GCC_Cross-Compiler).

所需的软件包

-----------------


首先，安装所需的软件包。在linux上，使用您的软件包发行版。在Mac上，[安装brew](http://brew.sh/) 如果您没有在第00课中这样做，并使用“brew安装”获取这些软件包`


-gmp

-mpfr

-libmpc

-gcc


是的，我们将需要“gcc”来构建交叉编译的“gcc”，特别是在Mac上，因为gcc已经被弃用为“clang”`


安装后，找到打包的gcc的位置（记住，不是clang）并将其导出。例如：


```

export CC=/usr/local/bin/gcc-4.9

export LD=/usr/local/bin/gcc-4.9

```


我们需要构建binutils和交叉编译的gcc，并将它们放入`/usr/local/i386elfgcc`，因此

现在让我们导出一些路径。您可以根据自己的喜好随意更改。


```
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
```


Binutils

--------


记住：在粘贴来自互联网的文本墙之前一定要小心。我建议逐行复制。


```sh
mkdir/tmp/src
cd/tmp/src
curl http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz #如果链接404了，请查找更新版本
tar xf binutils-2.24.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.24/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log

```


gcc

---

```sh
cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-4.9.1/gcc-4.9.1.tar.bz2
tar xf gcc-4.9.1.tar.bz2
mkdir gcc-build
cd gcc-build
../gcc-4.9.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
make all-gcc 
make all-target-libgcc 
make install-gcc 
make install-target-libgcc 
```


就这样！您应该在`/usr/local/i386elfgcc/bin`处设置所有GNU binutils和编译器，并以` i386 elf-`作为前缀，以避免

与系统的编译器和binutils发生冲突。


您可能需要将“$PATH”添加到“.bashrc”中。从现在开始，在本教程中，我们将在使用

交叉编译的gcc。

---
# Windows :

奥到我了    
实际上啃wiki更加全面且权威，就是更加枯燥，不过有些时候我们别无选择  
很遗憾，你无法直接在Windows下配置交叉编译器，你需要一个类Unix的环境，以下是几个选择：  
- [MinGW](https://wiki.osdev.org/MinGW)  
- [Cygwin](https://wiki.osdev.org/Cygwin)  
您没有其他选择，bunitils几乎只支持这两个编译器  
那么我选择了Cygwin
1. 安装Unix环境（安装Cygwin，注意请在引导安装界面就选择上第二步中需要安装的包）
2. 安装编译依赖  
    GCC、G++、Make、Flex、Bison、Diffutils、libintl-devel、libgmp-devel、libmpfr-devel、libmpc-devel、Texinfo   
    几乎每一个软件包都可以通过 `sudo apt install <包名>` 来安装，极个别不行可以上网查询  
    安装Cygwin会有选择安装哪些包的提示      
3. 开始构建  
    运行这些个命令：  
    ```sh
    export PREFIX="$HOME/opt/cross"
    export TARGET=i686-elf
    export PATH="$PREFIX/bin:$PATH"
    ```
    ~~关于i686-elf和i386-elf的问题，osdev使用6，os-tutorial使用3，具体区别正在研究~~
    然后前往[这个页面](https://ftp.gnu.org/gnu/binutils/)（是官网，别担心）找到最新的版本
    例如我的2.39，我们找到这个版本的 `.tar.gz` 文件，右键复制链接
    来到Cygwin，运行
    `curl <你复制的链接-o binutils.tar.gz`
    ~~Cygwin的curl下载东西的时候需要给定输出文件名~~
    然后运行这些个命令来创建合适的目录并放入压缩包并解压
    ```sh
    rm -r ~/src #删除无用的/home/<user>/src目录，如果你的src目录有用，不要复制这一条
    mkdir ~/src #创建/home/<user>/src目录
    mv ./binutils.tar.gz ~/src #移动压缩包到src
    cd ~/src #移动到src
    tar -xvf binutils.tar.gz #解压
    ```
    运行 `ls` 查看解压完的目录名，如 `binutils-11.45.14` 记住他
    ```sh
    cd ~/src
    mkdir build-binutils #创建build文件夹
    cd build-binutils #进入
    ../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror #运行这个以前请确保运行过了上面的三个export，并把x.y.z替换为你的binutils版本
    make && make install
    ```
    完成后binutils应该就安装好了
    接下来是gcc
    前往 [官网的镜像列表](https://gcc.gnu.org/mirrors.html) 找一个镜像网站
    我选的japan，进入 `release` （发行版）目录
    往下翻找到最新版，进入并复制 `.tar.gz` 的链接，使用curl再次下载并解压
    ```sh
    cd ~/src
    curl <复制的链接> -o gcc.tar.gz
    tar -xvf gcc.tar.gz
    ```
    运行以下的指令来安装gcc
    ```sh
    cd ~/src
    mkdir build-gcc
    cd build-gcc
    ../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers #还是把x.y.z替换为你的版本号，运行这个以前请确保运行过了上面的三个export
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
    ```
    这个指令运行时间比较长，可以将make开头的指令用 `&&` 连接起来，自动执行
    `make all-gcc && make all-target-libgcc && make install-gcc && make install-target-gcc`
4. 其他
    此时你的gcc应该已经编译完成了，运行以下指令检查
    `$HOME/opt/cross/bin/$TARGET-gcc --version`
    如果没有报错则为成功
    [出现问题请亲自前往osdevwiki查看troubleshooting](https://wiki.osdev.org/GCC_Cross-Compiler#Troubleshooting)

    （选修）
    现在我们可以使用gcc了，但是手动打一长串地址不够优雅，所以我们要将指令地址添加到bashrc中，运行：
    ```vi ~/.bashrc```
    cygwin似乎只提供了vi编辑器，对vi不熟悉的人可以紧跟我走
    **注意，如果哪一步操作错误请按下Esc，按下q，输入冒号q感叹号按下回车来不保存退出**
    进入vi编辑器以后按住箭头下，来到最下面，光标应该在一行注释的行首
    按下i，输入 `export PATH="$HOME/opt/cross/bin:$PATH"`
    此时你的最后一行应该像这样
    `export PATH="$HOME/opt/cross/bin:$PATH"#some comment`
    按下Esc，按下q，输入冒号wq，按下回车，即可
    现在你可以直接运行 `i686-elf-gcc --version` 等命令了
