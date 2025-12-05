# FEN Notation Documentation

## Overview

FEN (Forsyth-Edwards Notation) is a standard notation for describing a particular board position in chess. It provides a compact way to represent the complete state of a game, including piece positions, turn to move, castling rights, en passant targets, and move counters.

## FEN Structure

A FEN string consists of six fields separated by spaces:

```
[Piece Placement] [Active Color] [Castling Rights] [En Passant] [Halfmove Clock] [Fullmove Number]
```

### Example: Starting Position
```
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
```

## Field 1: Piece Placement

Describes the position of all pieces on the board, starting from rank 8 (top) to rank 1 (bottom), from file a to file h.

### Piece Symbols

| Piece | White | Black |
|-------|-------|-------|
| King | K | k |
| Queen | Q | q |
| Rook | R | r |
| Bishop | B | b |
| Knight | N | n |
| Pawn | P | p |

**Key Rules:**
- Uppercase letters = White pieces
- Lowercase letters = Black pieces
- Numbers (1-8) = consecutive empty squares
- Forward slash `/` = separates ranks

### Examples

**Full rank with pieces:**
```
rnbqkbnr
```
Black's back rank at the start of the game.

**Rank with empty squares:**
```
8
```
An entirely empty rank (8 consecutive empty squares).

**Mixed rank:**
```
r3k2r
```
Black rook, 3 empty squares, black king, 2 empty squares, black rook.

**Starting position piece placement:**
```
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
```

## Field 2: Active Color

Indicates whose turn it is to move.

- `w` = White to move
- `b` = Black to move

### Examples
```
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w
```
White's turn to move.

```
rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b
```
Black's turn to move.

## Field 3: Castling Availability

Indicates which castling moves are still legal for each player.

### Notation
- `K` = White can castle kingside
- `Q` = White can castle queenside
- `k` = Black can castle kingside
- `q` = Black can castle queenside
- `-` = No castling is available

Multiple letters indicate multiple castling options are available.

### Examples

`KQkq` - All castling options available for both sides

`Kq` - White can castle kingside, Black can castle queenside

`-` - No castling available for either side

`KQ` - White can castle both sides, Black cannot castle

### When Castling Rights Are Lost

Castling rights are lost when:
- The king moves
- A rook moves from its starting position
- A rook is captured from its starting position

## Field 4: En Passant Target Square

Indicates if an en passant capture is possible on the current turn.

### Notation
- Square notation (e.g., `e3`, `c6`) = The square where an en passant capture can be made
- `-` = No en passant capture is possible

### Key Rule
The en passant square is the square **behind** the pawn that just moved two squares forward.

### Examples

After `1.e4`:
```
rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3
```
The pawn moved from e2 to e4, so `e3` is the en passant target square.

After `1.e4 c5`:
```
rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6
```
The pawn moved from c7 to c5, so `c6` is the en passant target square.

After `2.Nf3`:
```
rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq -
```
No pawn moved two squares, so en passant is not available (`-`).

## Field 5: Halfmove Clock

Counts the number of halfmoves (plies) since the last pawn move or capture. Used for the fifty-move rule.

### Purpose
The fifty-move rule states that a player can claim a draw if no capture has been made and no pawn has been moved in the last fifty moves by each player (100 halfmoves total).

### Rules
- Increments by 1 after each move
- Resets to 0 after any pawn move or any capture
- Starts at 0 at the beginning of the game

### Examples

```
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
```
Starting position: 0 halfmoves since last pawn move or capture.

```
rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
```
Still 0 because a pawn just moved (e2-e4).

```
rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2
```
Now 1 because the knight moved (Nf3) without a pawn move or capture.

## Field 6: Fullmove Number

The number of completed moves in the game, starting at 1 and incrementing after Black's move.

### Rules
- Starts at 1 at the beginning of the game
- Increments after Black moves
- Remains the same during White's turn

### Examples

```
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
```
Move 1, White to play.

```
rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
```
Still move 1, Black to play (after 1.e4).

```
rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
```
Move 2, White to play (after 1.e4 c5).

## Complete Examples

### Starting Position
```
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
```
- All pieces in starting positions
- White to move
- All castling available
- No en passant
- 0 halfmoves since pawn move/capture
- Move 1

### After 1.e4
```
rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
```
- White pawn on e4
- Black to move
- All castling still available
- En passant possible on e3
- 0 halfmoves (pawn just moved)
- Still move 1 (Black hasn't moved yet)

### After 1.e4 c5
```
rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
```
- Black pawn on c5
- White to move
- All castling still available
- En passant possible on c6
- 0 halfmoves (pawn just moved)
- Move 2

### After 2.Nf3
```
rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2
```
- White knight on f3
- Black to move
- All castling still available
- No en passant (knight moved, not pawn)
- 1 halfmove (no pawn move or capture)
- Still move 2 (Black hasn't completed turn)

### Mid-Game Position
```
r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 5
```
- Various pieces developed
- White to move
- All castling still available
- No en passant
- 4 halfmoves since last pawn move/capture
- Move 5

### Position After Castling
```
r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 5 5
```
- White has castled kingside (king on g1, rook on f1)
- Black to move
- White lost castling rights (already castled), Black can still castle
- No en passant
- 5 halfmoves since last pawn move/capture
- Still move 5

## Usage and Applications

### Common Uses
1. **Saving game positions** - Store a specific position without the full game history
2. **Position analysis** - Share positions for study or analysis
3. **Chess puzzles** - Define starting positions for tactical problems
4. **Chess engines** - Provide positions for computer analysis
5. **Online chess** - Synchronize positions between client and server

### Reading FEN in Order
To parse a FEN string:
1. Place pieces according to the piece placement field
2. Determine whose turn it is
3. Note available castling options
4. Check for en passant possibilities
5. Record the halfmove clock for draw rules
6. Note the current move number

### Creating FEN from a Position
To create a FEN string:
1. Start from rank 8, scan left to right
2. Record pieces with their symbols, count empty squares
3. Add `/` between ranks
4. Add active color (`w` or `b`)
5. Determine castling rights based on king and rook positions/history
6. Check if the last move allows en passant
7. Count halfmoves since last pawn move/capture
8. Determine the current fullmove number

## Validation Rules

A valid FEN string must satisfy:
- Exactly one white king and one black king
- No pawns on rank 1 or rank 8
- Correct number of pieces (max 16 per side)
- En passant square must be on rank 3 (for black) or rank 6 (for white)
- En passant only valid if opponent has pawn that could capture
- Castling rights consistent with king/rook positions

## Common Errors

**Incorrect rank counting:**
```
rnbqkbnr/pppppppp/8/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 1
```
❌ Only 7 ranks (missing one `/`)

**Invalid piece placement:**
```
rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNP w KQkq - 0 1
```
❌ Missing white king (has pawn instead)

**Wrong en passant square:**
```
rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e4 0 1
```
❌ En passant square should be e3 (behind the pawn), not e4

## Summary

FEN notation provides a complete snapshot of a chess position in a compact, human-readable format. Understanding each of the six fields allows you to:
- Recreate any chess position
- Share positions for analysis
- Set up positions in chess software
- Understand the complete game state at a glance