# Ping Pong

# Setting up raylib for ping-pong-raylib

This guide will walk you through setting up the raylib library. 

## Step 1: Clone raylib repository

Clone the raylib repository from GitHub:

```bash
git clone https://github.com/raysan5/raylib.git
```

## Step 2: Navigate to raylib source directory:

Change directory to the `src` folder inside the cloned raylib repository:

```bash
cd ./raylib/src/
```

## Step 3: Build raylib:

Build the raylib library using `make`:

```bash
make
```

## Step 4: Copy library and header files:

Copy the built `libraylib.a`, `raylib.h`, and `raymath.h` files to your project directory named "ping-pong-raylib" (replace `<your-path>` with the path to your project directory):


```bash
cp libraylib.a <your-path>/ping-pong-raylib
cp raylib.h <your-path>/ping-pong-raylib
cp raymath.h <your-path>/ping-pong-raylib
```

# Compiling the Ping Pong Game using MacOS

To compile the Ping Pong game using MacOS, you can use the following command:

```bash
g++ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -std=c++11 libraylib.a pingpong.cpp -o pingpong
```

# Running the Game

To start the Ping Pong game, simply run the compiled executable:

```bash
./pingpong
```
