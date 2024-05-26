# real-time-screen-recorder

## Introduction

Record the screen (Windows) in real-time and transfer it to a remote client. 

## Setup

To set up the project, follow these steps:

1. Create python virtual environment and install conan (only once is enough for each computer)
```bash
python -m venv <path-to-venv-with-conan>/.venv
python -m pip install --upgrade pip
pip install conan
```
2. Activate it (for Unix-like systems, use `source <path-to-venv-with-conan>/.venv/bin/activate` instead of `Activate.ps1`)
```bash
<path-to-venv-with-conan>/.venv/Scripts/Activate.ps1
```
3. Install dependencies with conan (if you don't have conan installed before, run `conan profile detect --force` first)
```bash
conan install . --build=missing
conan install . --build=missing --settings=build_type=Debug
```
4. Install CMake extension for Vision Studio and then open the project folder in Visual Studio and it will set up the project for you automatically (if you're not a Visual Studio user, just consider this as a normal CMake project)

