*Concepts you may want to Google beforehand: cross-compiler*

**Goal: Create a development environment to build your kernel**

If you're using a Mac, you will need to do this process right away. Otherwise, it could have waited
for a few more lessons. Anyway, you will need a cross-compiler once we jump to developing in a higher
language, that is, C. [Read why](http://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F)

I'll be adapting the instructions [at the OSDev wiki](http://wiki.osdev.org/GCC_Cross-Compiler). 


Required packages
-----------------

First, install the required packages. On linux, use your package distribution. On a Mac, [install brew](http://brew.sh/) if
you didn't do it on lesson 00, and get those packages with `brew install`

- gmp
- mpfr
- libmpc
- gcc

Yes, we will need `gcc` to build our cross-compiled `gcc`, especially on a Mac where gcc has been deprecated for `clang`

Once installed, find where your packaged gcc is (remember, not clang) and export it. For example:

```
export CC=/usr/local/bin/gcc-4.9
export LD=/usr/local/bin/gcc-4.9
```

We will need to build binutils and a cross-compiled gcc, and we will put them into `/usr/local/i386elfgcc`, so
let's export some paths now. Feel free to change them to your liking.

```
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
```

binutils
--------

Remember: always be careful before pasting walls of text from the internet. I recommend copying line by line.

```sh
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz # If the link 404's, look for a more recent version
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

That's it! You should have all the GNU binutils and the compiler at `/usr/local/i386elfgcc/bin`, prefixed by `i386-elf-` to avoid
collisions with your system's compiler and binutils.

You may want to add the `$PATH` to your `.bashrc`. From now on, on this tutorial, we will explicitly use the prefixes when using
the cross-compiled gcc.

*您可能需要事先搜索的概念：交叉编译器*


**目标：创建一个开发环境来构建内核**

> 注解将针对windows用户  
> 最下面将是给你们的说明，原文部分用处不大

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

> 奥到我了    
> 实际上啃wiki更加全面且权威，就是更加枯燥，不过有些时候我们别无选择  
> 很遗憾，你无法直接在Windows下配置交叉编译器，你需要一个类Unix的环境，以下是几个选择：  
> - [MinGW](https://wiki.osdev.org/MinGW)  
> - [Cygwin](https://wiki.osdev.org/Cygwin)  
> 您没有其他选择，bunitils几乎只支持这两个编译器  
> 1. 安装Unix环境  
> 2. 安装编译依赖  
>   GCC、G++、Make、Flex、Bison、Diffutils、libintl-devel、libgmp-devel、libmpfr-devel、libmpc-devel、Texinfo   
>   几乎每一个软件包都可以通过 `sudo apt install <包名>` 来安装，极个别不行可以上网查询  
>   安装Cygwin会有选择安装哪些包的提示      
> 3. 开始构建  
>   运行这些个命令：  
>   ```
>   export PREFIX="$HOME/opt/cross"
>   export TARGET=i686-elf
>   export PATH="$PREFIX/bin:$PATH"
>   ```
>   然后。。。  
>   ```
>   cd $HOME/src
> 
>   mkdir build-binutils
>   cd build-binutils
>   ../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
>   make
>   make install
>   ```