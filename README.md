# Master-Engine

## Setup

Run the following commands in Powershell to get started.

```
cd <location>

git clone https://github.com/Microsoft/vcpkg.git

cd vcpkg

.\bootstrap-vcpkg.bat

.\vcpkg integrate install

.\vcpkg integrate powershell

.\vcpkg install glm:x64-windows glew:x64-windows glfw3:x64-windows opengl:x64-windows soil:x64-windows sfml:x64-windows
```
