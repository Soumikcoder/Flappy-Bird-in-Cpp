
# Flappy Bird Clone

This is a simple Flappy Bird clone game developed in C++ using the SDL2 library. The game replicates the mechanics and gameplay of the popular mobile game "Flappy Bird," where the player controls a bird and tries to navigate it through gaps between pipes without colliding with them.

![Flappy Bird Clone Screenshot](screenshot.png)

## Features

- Simple and addictive gameplay
- Smooth bird movement
- Randomly generated pipe gaps
- Scoring system
- Game over detection
- Restart functionality

## Requirements

- C++ compiler (supporting C++14 or higher)
- SDL2 library
- SDL2_image extension
- SDL2_ttf extension
- SDL2_mixer extension


## Installation

1. Clone or download the repository: `git clone https://github.com/Soumikcoder/Flappy-Bird-in-Cpp.git`
2. Navigate to the project directory: `cd flappy-bird-clone`
3. Compile the source code using a C++ compiler: `g++ -c src/*.cpp -std=c++14 -Wall -O3 -m64  -I include  && g++ *.o icons.res -o bin/release/main -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image  -lSDL2_test -lSDL2_ttf -lSDL2_mixer -mwindows`(for windows)
4. Run the executable: `bin/release/main.exe`

## Usage

- Press the spacebar or left mouse button to make the bird flap and ascend.
- Avoid colliding with the pipes.
- The game ends when the bird collides with a pipe or touches the ground.
- Press *Continue* or *Menu* button to restart the game after it ends.

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request. 

## Credits

This project is inspired by the original Flappy Bird game created by Dong Nguyen.


## Acknowledgments

- The creators and contributors of the SDL2 library for providing a powerful framework for game development.
- Dong Nguyen for creating the original Flappy Bird game that served as the inspiration for this clone.
- The online tutorials and resources that assisted in the development of this project.




