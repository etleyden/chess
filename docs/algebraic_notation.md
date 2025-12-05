# Chess Algebraic Notation Documentation

## Overview

Algebraic notation is the standard system for recording chess moves. Each move is written using a combination of piece identifiers, board coordinates, and special symbols to create a clear, unambiguous record of the game.

## Board Coordinate System

The chessboard uses a grid coordinate system:

- **Files (columns)**: Labeled a through h, from left to right (White's perspective)
- **Ranks (rows)**: Numbered 1 through 8, from bottom to top (White's perspective)

Every square has a unique coordinate. For example, "e4" refers to the square at file e, rank 4.

## Piece Identification

Pieces are represented by uppercase letters:

| Piece  | Symbol | Notes |
|--------|--------|-------|
| King   | K      | |
| Queen  | Q      | |
| Rook   | R      | |
| Bishop | B      | |
| Knight | N      | Uses N because K is taken by King |
| Pawn   | (none) | Pawns have no letter prefix |

## Basic Move Notation

### Standard Moves

**Format**: `[Piece][destination square]`

Examples:
- `e4` - Pawn moves to e4
- `Nf3` - Knight moves to f3
- `Bc4` - Bishop moves to c4
- `Qd8` - Queen moves to d8

### Captures

**Format**: `[Piece]x[destination square]`

The `x` symbol indicates a capture.

Examples:
- `Nxe5` - Knight captures on e5
- `Bxf7` - Bishop captures on f7
- `exd5` - Pawn on the e-file captures on d5

For pawn captures, the originating file must be specified (e.g., `exd5` means a pawn from the e-file captured on d5).

### Disambiguation

When two identical pieces can move to the same square, additional information is required:

**By file**: `Nbd7` - Knight from the b-file moves to d7
**By rank**: `R1e2` - Rook from rank 1 moves to e2
**By both**: `Qh4e1` - Queen from h4 moves to e1 (rarely needed)

Examples:
- `Rad1` - Rook from the a-file moves to d1
- `N5f3` - Knight from rank 5 moves to f3
- `Nexd4` - Knight from the e-file captures on d4

## Special Moves

### Castling

- `O-O` - Kingside castling (short castling)
- `O-O-O` - Queenside castling (long castling)

### Pawn Promotion

**Format**: `[destination square]=[new piece]`

Examples:
- `e8=Q` - Pawn moves to e8 and promotes to Queen
- `a1=N` - Pawn moves to a1 and promotes to Knight
- `axb8=R` - Pawn captures on b8 and promotes to Rook

### En Passant

Notated as a normal pawn capture:
- `exd6` - Pawn on e5 captures en passant on d6

The en passant nature is usually clear from context, but "e.p." may be added for clarity.

## Status Indicators

Special symbols are appended to the end of a move:

| Symbol | Meaning |
|--------|---------|
| `+`    | Check |
| `#`    | Checkmate |
| `!`    | Good move |
| `!!`   | Brilliant move |
| `?`    | Mistake |
| `??`   | Blunder |
| `!?`   | Interesting move |
| `?!`   | Dubious move |

Examples:
- `Qxf7#` - Queen captures on f7, checkmate
- `Nf6+` - Knight to f6, check
- `Rxh7+!` - Rook captures on h7, check, good move

## Move Numbering

### Standard Format

**White's move**: `[number].[move]`
**Black's move**: `[number]...[move]`

Examples:
```
1.e4 e5
2.Nf3 Nc6
3.Bb5 a6
```

Can also be written inline:
```
1.e4 e5 2.Nf3 Nc6 3.Bb5 a6
```

### Black Move Only

When showing only Black's move:
```
1...e5
```
The ellipsis (...) indicates Black's move.

## Complete Examples

### Basic Game Opening
```
1.e4 c5
2.Nf3 d6
3.d4 cxd4
4.Nxd4 Nf6
5.Nc3 a6
```

### Game with Captures and Check
```
1.e4 e5
2.Nf3 Nc6
3.Bc4 Bc5
4.Bxf7+ Kxf7
5.Nxe5+ Nxe5
```

### Castling and Promotion
```
1.e4 e5
2.Nf3 d6
3.d4 Nf6
4.Nc3 exd4
5.Nxd4 g6
6.Be3 Bg7
7.O-O O-O
```

## Common Abbreviations

In notation, you may also see:
- `!?` - Interesting but unclear move
- `?!` - Dubious but playable move
- `±` - White has a slight advantage
- `∓` - Black has a slight advantage
- `+-` - White has a winning advantage
- `-+` - Black has a winning advantage
- `=` - Position is equal

## Notes

- Algebraic notation is the official FIDE (World Chess Federation) standard
- Always write moves from White's perspective (a1 is White's queenside corner)
- When reading game scores, assume moves alternate White-Black unless otherwise indicated
- Spaces between move elements are optional but improve readability