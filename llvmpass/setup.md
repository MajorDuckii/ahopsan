## AHopSan 开发环境安装和配置

### Part 1: clang+llvm编译器的安装和使用

1. 获取源代码并检出版本12.0
```shell
$git clone https://github.com/llvm/llvm-project.git
$git checkout -b llvm12rc3 llvmorg-12.0.0-rc3
$git branch
* llvm12rc3         ##Now branch llvm12rc3 is active
main
END
```

2. 编译LLVM debug版本
为了便于调试，编译出调试版本

```shell
$pwd
/home/RD/Projects/llvm-project
$mkdir build-debug
$cd build-debug
$cmake -DLLVM_ENABLE_PROJECTS="clang;compiler-rt"  -G Ninja ../llvm -DLLVM_ENABLE_ASSERTIONS=On -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD=X86
$ninja 		## or "ninja -j8" if your PC has less than 32G RAM
```

3.  使用llvm和clang

   A: 编译C++程序

```shell
$pwd
/home/RD/Tests/clang/hello
$clang++   main.cpp -o main -g -O0
$./main
hello world
```

   B: 生成字节码文件1 (human readable)

```shell
$clang++ -S -emit-llvm main.cpp -o main.ll -g -O0
$vim main.ll
$gedit main.ll
```

   C: 生成字节码文件2 (human un-readable)
```shell
$clang++ -C -emit-llvm main.cpp -o main.bc -g -O0
```



### Part 2: LLVM Pass 开发与调试
1. 可以在llvm-project源代码内开发llvm pass, 但进行编译会消耗很多时间. 建议在源外开发编译.

```shell
$pwd 
/home/RD/Projects/ahopsan/llvmpass
$tree -L 1
.
├── CMakeCache.txt
├── CMakeFiles
├── cmake_install.cmake
├── CMakeLists.txt
├── Makefile
├── ptrtrack
└── setup.md

$make   #generate /home/RD/Projects/ahopsan/llvmpass/ptrtrack/libptrtrack.so
```

2. 用llvm opt加载llvm pass

```shell
# 创建到llvm opt的符号链接
$ln -sf /home/RD/Projects/llvm-project/build-debug/bin/opt .
$ll opt
opt -> /home/RD/Projects/llvm-project/build-debug/bin/opt

# 加载libptrtrack.so pass
./opt  -load /home/RD/Projects/ahopsan/llvmpass/ptrtrack/libptrtrack.so -testpp < /home/RD/Tests/clang/hello/main.bc > /dev/null
```

3. 调式llvm pass

```shell
$pwd 
/home/RD/Projects/ahopsan/llvmpass/ptrtrack

$gdb -ex 'set args -load /home/RD/Projects/ahopsan/llvmpass/ptrtrack/libptrtrack.so -testpp < /home/RD/Tests/clang/hello/main.bc' ./opt
```


