# Ethan's Chess Implementation

## Repository Guide

| subdirectory | what's in it |
|--------------|--------------|
| `board`      | basic game logic |
| `test`       | perft tests | 

## Use/Run

| Task | Command |
|------|---------|
| **Initial Build (Windows using g++)** | `cmake -S . -B build -G "MinGW Makefiles"` |
| **Simple Build** | `cmake --build build` |
| **Build and run tests:** | `cmake --build build --target run_tests` |
|**Install the library \[untested\]:** | `cmake --install build --prefix /usr/local`|
|**Clean up build artifacts:** | `cmake --build build --target clean`|

## Current Implementation Plan

- Initialize the Board from FEN notation
- Write tests for FEN notation -> board
- Write tests for movement generators for each piece. This will use the FEN notation board generation. (mock underlying logic)
- Write movement generators. Movement generators must come in two varieties: a. return a bitmask of valid moves, b. return a string list of valid moves (i.e. "e1 e4")
- Write Perft tests
- Implement text-based gameplay interface
- Implement graphical gameplay interface
- Other cool stuff probably