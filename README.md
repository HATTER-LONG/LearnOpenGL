# OpenGL测试项目

这是一个基于OpenGL的简单测试项目，用于演示OpenGL窗口的创建和基本设置。

## 项目描述

该项目创建了一个基本的OpenGL窗口，配置了OpenGL 3.3核心模式环境。项目使用CMake作为构建系统，支持跨平台开发。

## 依赖库

项目依赖以下库：

- **OpenGL**：图形渲染API
- **GLFW3**：提供窗口创建和输入处理功能
- **GLAD**：OpenGL函数加载库，用于加载OpenGL函数指针

## 环境要求

- CMake 3.10+
- 支持C++17的编译器
- OpenGL兼容显卡及驱动

## 构建说明

### Windows平台

1. 克隆仓库：
```
git clone <repository-url>
cd opengl_test
```

2. 创建并进入构建目录：
```
mkdir build
cd build
```

3. 配置并构建项目：
```
cmake ..
cmake --build . --config Release
```

### 其他平台（Linux/macOS）

1. 克隆仓库：
```
git clone <repository-url>
cd opengl_test
```

2. 安装依赖库：
```
# Ubuntu/Debian
sudo apt install libglfw3-dev

# macOS (使用Homebrew)
brew install glfw
```

3. 创建并进入构建目录：
```
mkdir build
cd build
```

4. 配置并构建项目：
```
cmake ..
make
```

## 项目结构

```
opengl_test/
├── include/          # 头文件目录
├── src/              # 源代码目录
│   ├── main.cpp      # 主程序入口
│   └── glad.c        # GLAD源文件
├── build/            # 构建输出目录
├── CMakeLists.txt    # CMake构建配置
└── .clang-tidy       # 代码检查配置
```

## 使用说明

编译完成后，在build目录下运行生成的可执行文件：

```
# Windows
MyCppProject.exe

# Linux/macOS
./MyCppProject
```

## 代码说明

当前项目实现了：
- 创建800x600像素的OpenGL窗口
- 配置OpenGL 3.3核心模式上下文
- 基本的渲染循环结构
- 窗口大小变化响应
- ESC键退出程序

## 扩展开发

要在此基础上进行开发，可以：

1. 在渲染循环中添加绘制代码
2. 添加着色器加载和编译
3. 实现模型加载和渲染
4. 添加用户输入处理