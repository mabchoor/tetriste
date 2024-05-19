# Tetriste

## Overview
Tetriste is a C programming project for L2 MIDO 2023-2024. The goal is to develop a game with pieces characterized by shape and color, where the player aims to create repeated patterns of shapes or colors.

## Table of Contents
- [Important Dates](#important-dates)
- [Features](#features)
  - [Basic Features (Tétriste)](#basic-features-tétriste)
  - [Advanced Features (Tépatrice)](#advanced-features-tépatrice)
  - [Expert Features (Técontent)](#expert-features-técontent)
  - [Bonus Features](#bonus-features)
- [Pieces and Board](#pieces-and-board)
- [Commands](#commands)
- [Compilation and Execution](#compilation-and-execution)
  - [Memory Management](#memory-management)
- [File Structure](#file-structure)
- [Images](#images)
- [Notes](#notes)
- [References](#references)


## Features

### Basic Features (Tétriste)
- Display the game in the terminal (ASCII art).
- Insert pieces to the left or right.
- Remove three consecutive pieces with the same shape or color.
- Perfect memory management (checked with Valgrind).

### Advanced Features (Tépatrice)
- All Tétriste features.
- Shift pieces to the left by shape or color.

### Expert Features (Técontent)
- All Tépatrice features.
- Additional challenges and functionalities.

### Bonus Features
- Calculate a more realistic score with combo points.
- Different difficulty levels with varying numbers of colors and shapes.
- An "AI" to suggest the best move for the player.

## Pieces and Board
- **Shapes**: Square (■), Diamond (♦), Circle (●), Triangle (▲)
- **Colors**: Blue, Yellow, Red, Green
- The board is a single line, extendable on both sides.
- Pieces can be inserted on the left or right.
- If three consecutive pieces have the same shape or color, they disappear from the board.

## Commands
- **Left (`g`)**: Place the next piece on the left.
- **Right (`d`)**: Place the next piece on the right.
- **Shift Left (`sl`)**: Shift all pieces with the same shape to the left.
- **Shift Left by Color (`sc`)**: Shift all pieces with the same color to the left.

## Compilation and Execution
