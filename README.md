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

## Implementation Plan

1. Board Representation/Tests

    a. Determine interface for representing the board, with pieces.

    b. Write [Perft](https://www.chessprogramming.org/Perft) tests using that interface

    c. Implement the logic behind the interface.