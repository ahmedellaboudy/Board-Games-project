# Board Games Collection

A comprehensive C++ implementation of 13 classic and variant board games featuring AI opponents, smart input validation, and an elegant object-oriented architecture.

## Team Members

- **Ahmed Mostafa Ellaboudy** - [GitHub](https://github.com/ahmedellaboudy)
- **Mohamed Safwat**
- **Abdelrahman Gamal**
- **Abdelrahman Yasser**

## Repository

🔗 **GitHub Repository**: [https://github.com/ahmedellaboudy/Board-Games-project](https://github.com/ahmedellaboudy/Board-Games-project)

## Overview

This project is a modular board game framework built with C++ that demonstrates advanced object-oriented programming principles. The framework provides a reusable foundation for implementing various board games with minimal code duplication.

### Key Features

- **13 Unique Games**: Classic and variant Tic-Tac-Toe games plus strategic challenges
- **AI Opponents**: Smart AI players using heuristic evaluation and minimax algorithms
- **Input Validation**: Custom `ValidatedUI` class ensuring robust user input handling
- **OOP Architecture**: Clean inheritance hierarchy with abstract base classes
- **Template-Based Design**: Generic framework supporting different data types
- **Doxygen Documentation**: Complete API documentation with detailed class descriptions

## Architecture

### Core Framework Components

The project is built on a generic framework defined in `BoardGame_Classes.h`:

#### Base Classes

- **`Board<T>`**: Abstract base class representing game boards
  - Generic template supporting various cell types (char, int, string)
  - Virtual methods for game logic (update, win/lose/draw conditions)
  - 2D vector-based board representation

- **`Player<T>`**: Represents players (human or AI)
  - Stores player name, symbol, and type
  - Maintains reference to game board

- **`Move<T>`**: Encapsulates a single game move
  - Coordinates (x, y) and symbol/value

- **`UI<T>`**: Abstract user interface base class
  - Handles display and input operations
  - Extensible for game-specific needs

- **`GameManager<T>`**: Controls game flow
  - Manages turn-based gameplay
  - Coordinates board updates and win detection

#### Enhanced Components

- **`ValidatedUI<T>`**: Extended UI with robust input validation
  - Range validation for numeric inputs
  - Position validation with boundary checks
  - Menu choice validation
  - Buffer clearing and error recovery
  - Inherited by all game-specific UI classes

### Design Patterns

- **Template Method Pattern**: Base classes define algorithm structure
- **Strategy Pattern**: Different player types (Human, Computer, AI)
- **Factory Pattern**: Player creation through UI classes
- **Open/Closed Principle**: Extend via inheritance, not modification

## Games Included

### 1. SUS Game
Strategic letter placement game where players score by forming "S-U-S" sequences.
- **Board**: 3×3 grid
- **Players**: One uses 'S', other uses 'U'
- **Winning**: Most S-U-S sequences when board is full
- **AI**: Smart heuristic-based AI with position weighting

### 2. Four-in-a-Row (Connect Four)
Classic vertical Connect Four on a grid.
- **Board**: 6×7 grid
- **Players**: 'X' and 'O'
- **Winning**: Four in a row (horizontal, vertical, diagonal)
- **AI**: Minimax with alpha-beta pruning

### 3. 5×5 Tic-Tac-Toe
Extended Tic-Tac-Toe with scoring system.
- **Board**: 5×5 grid
- **Players**: 'X' and 'O'
- **Winning**: Most three-in-a-row sequences after 24 moves

### 4. Word Tic-Tac-Toe
Form valid English words on the board.
- **Board**: 3×3 grid with letter placement
- **Players**: Place letters strategically
- **Winning**: First to form a valid 3-letter word
- **Features**: Dictionary validation from `dic.txt`

### 5. Misère Tic-Tac-Toe
Inverse Tic-Tac-Toe where you try to avoid winning.
- **Board**: 3×3 grid
- **Players**: 'X' and 'O'
- **Winning**: Force opponent to get three-in-a-row

### 6. Diamond Tic-Tac-Toe
Diamond-shaped board variant.
- **Board**: 5×5 diamond arrangement
- **Players**: 'X' and 'O'
- **Winning**: Simultaneously complete 3-mark and 4-mark lines

### 7. 4×4 Tic-Tac-Toe
Token movement game on 4×4 grid.
- **Board**: 4×4 grid with preset starting positions
- **Players**: Move existing tokens to adjacent cells
- **Winning**: Align three tokens in a row

### 8. Pyramid Tic-Tac-Toe
Pyramid-shaped board game.
- **Board**: Pyramid structure (1-3-5 cells)
- **Players**: 'X' and 'O'
- **Winning**: Three in a row on pyramid

### 9. Numerical Tic-Tac-Toe *(Group Project)*
Mathematical variant with number placement.
- **Board**: 3×3 grid
- **Players**: P1 uses odd (1,3,5,7,9), P2 uses even (2,4,6,8)
- **Winning**: Three numbers in a row summing to 15

### 10. Obstacles 6×6 Tic-Tac-Toe *(Group Project)*
Dynamic obstacle placement game.
- **Board**: 6×6 grid
- **Players**: 'X' and 'O'
- **Mechanics**: Random obstacles appear every round
- **Winning**: Four in a row while avoiding obstacles

### 11. Infinity Tic-Tac-Toe *(Group Project)*
Time-based vanishing marks.
- **Board**: 3×3 grid with temporary marks
- **Mechanics**: Oldest marks disappear after 3 moves
- **Winning**: Three in a row before marks vanish

### 12. Ultimate Tic-Tac-Toe *(Bonus)*
Meta-game with nested boards.
- **Board**: 3×3 main grid of 3×3 sub-boards
- **Winning**: Win three sub-boards in a row on main grid

### 13. Memory Tic-Tac-Toe *(Bonus)*
Hidden marks challenge players' memory.
- **Board**: 3×3 grid with invisible marks
- **Mechanics**: Marks hidden after placement
- **Winning**: Three in a row (revealed at end)

## AI Implementation

### SUS Game AI
**Algorithm**: Multi-criteria heuristic evaluation

**Strategy Components**:
1. **Pattern Completion** (100 pts): Prioritize completing S-U-S sequences
2. **Opponent Blocking** (80 pts): Prevent opponent patterns
3. **Position Value** (5-15 pts): Weight strategic positions
   - Center: 15 points (both diagonals)
   - Corners: 8 points (one diagonal)
   - Edges: 5 points
4. **Future Potential** (2-3 pts): Count setup opportunities
5. **Adaptive Strategy** (50 bonus pts): Adjust based on score difference

**Performance**: O(9) - evaluates all cells once, instant response

### Four-in-a-Row AI
**Algorithm**: Minimax with alpha-beta pruning

**Features**:
- Search depth: 6 moves
- Position evaluation with pattern recognition
- Immediate win/block detection
- Center column preference
- Window evaluation (4-cell segments)

**Performance**: Evaluates 10,000-50,000 positions per move, < 2 seconds response

## Project Structure

```
Board-Games-project/
├── BoardGame_Classes.h       # Core framework (Board, Player, Move, UI, GameManager)
├── ValidatedUI.h             # Input validation utilities
├── SUS_AI_Player.h           # Smart AI for SUS game
├── FourInARow_AI_Player.h    # Minimax AI for Connect Four
├── sus.h / sus.cpp           # SUS game implementation
├── FourInARow.h / .cpp       # Four-in-a-Row implementation
├── Word.h / .cpp             # Word Tic-Tac-Toe
├── XO_4x4_Classes.h / .cpp   # 4×4 variant
├── XO_5x5_Classes.h / .cpp   # 5×5 variant
├── NumericalTicTacToe.h / .cpp       # Numerical variant
├── obstacles_6x6_tictactoe.h / .cpp  # Obstacles variant
├── infinity_XO.h / .cpp      # Infinity variant
├── ultimate_XO_Classes.h / .cpp      # Ultimate variant (bonus)
├── Memory_TicTacToe.h / .cpp # Memory variant (bonus)
├── pyramid_XO_Classes.h / .cpp       # Pyramid variant
├── MisereTicTacToe.h / .cpp  # Misère variant
├── Diamond_TicTacToe.h / .cpp        # Diamond variant
├── MainMenu.cpp              # Main application entry point
├── dic.txt                   # Dictionary for Word Tic-Tac-Toe
└── docs/                     # Doxygen-generated documentation
```

## Building and Running

### Prerequisites

- **C++ Compiler**: GCC 7.0+ or Clang 6.0+ with C++17 support
- **Make** (optional): For automated builds
- **Doxygen** (optional): For generating documentation

### Compilation

#### Using g++

```bash
# Compile all source files
g++ -std=c++17 -Wall -Wextra -O2 \
    MainMenu.cpp \
    sus.cpp \
    FourInARow.cpp \
    Word.cpp \
    XO_4x4_Classes.cpp \
    XO_5x5_Classes.cpp \
    NumericalTicTacToe.cpp \
    obstacles_6x6_tictactoe.cpp \
    infinity_XO.cpp \
    ultimate_XO_Classes.cpp \
    Memory_TicTacToe.cpp \
    pyramid_XO_Classes.cpp \
    MisereTicTacToe.cpp \
    Diamond_TicTacToe.cpp \
    -o BoardGames
```

#### Quick Compile (All games)

```bash
g++ -std=c++17 *.cpp -o BoardGames
```

### Running the Application

```bash
./BoardGames
```

### Game Menu

Upon running, you'll see:

```
=============================================
  Welcome to the Board Games Application!
=============================================

 1.  SUS Game
 2.  Four-in-a-Row (Connect Four)
 3.  5x5 Tic-Tac-Toe
 4.  Word Tic-Tac-Toe
 5.  Misere Tic-Tac-Toe
 6.  Diamond Tic-Tac-Toe
 7.  4x4 Tic-Tac-Toe
 8.  Pyramid Tic-Tac-Toe
 9.  Numerical Tic-Tac-Toe
 10. Obstacles 6x6 Tic-Tac-Toe
 11. Infinity XO Tic-Tac-Toe
 12. Ultimate Tic-Tac-Toe (Bonus)
 13. Memory Tic-Tac-Toe (Bonus)
 0.  Exit

Choose a game (0-13):
```

## Documentation

### Doxygen Documentation

Complete API documentation is available in the `docs/` directory (generated with Doxygen).

#### Generating Documentation

If you need to regenerate the documentation:

1. Install Doxygen:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install doxygen graphviz
   
   # macOS
   brew install doxygen graphviz
   ```

2. Generate docs:
   ```bash
   doxygen Doxyfile
   ```

3. View documentation:
   ```bash
   # Open in browser
   firefox docs/html/index.html
   # or
   google-chrome docs/html/index.html
   ```

### Documentation Features

- **Class Hierarchies**: Visual inheritance diagrams
- **Function Documentation**: Detailed parameter and return descriptions
- **Code Examples**: Usage demonstrations
- **Cross-References**: Easy navigation between related classes
- **Search Functionality**: Quick lookup of classes and methods

## Input Validation Features

The `ValidatedUI` class provides robust input handling:

### Features

1. **Numeric Range Validation**
   ```cpp
   int value = get_validated_int("Enter value (1-10): ", 1, 10);
   ```

2. **Position Validation**
   ```cpp
   auto pos = get_validated_position("Enter position: ", 3, 3, board, empty_symbol);
   ```

3. **Menu Choice Validation**
   ```cpp
   int choice = get_menu_choice("Select option: ", num_options);
   ```

4. **Automatic Error Recovery**
   - Invalid input type → Clear buffer and retry
   - Out of range → Display valid range and retry
   - Occupied cell → Inform user and retry

## Design Principles Applied

### SOLID Principles

- **Single Responsibility**: Each class has one well-defined purpose
- **Open/Closed**: Extend framework through inheritance, not modification
- **Liskov Substitution**: Derived classes fully substitutable for base classes
- **Interface Segregation**: Clean, minimal interfaces
- **Dependency Inversion**: Depend on abstractions (Board, UI, Player)

### OOP Concepts

- **Encapsulation**: Private data with public interfaces
- **Inheritance**: Reuse common functionality
- **Polymorphism**: Virtual functions for game-specific behavior
- **Abstraction**: Hide implementation details

## Testing

### Manual Testing Checklist

- [ ] All 13 games launch correctly
- [ ] Human vs Human gameplay works
- [ ] Human vs Computer gameplay works
- [ ] Human vs AI (smart) gameplay works
- [ ] Input validation handles invalid inputs
- [ ] Win conditions detected correctly
- [ ] Draw conditions detected correctly
- [ ] Board displays correctly for all games
- [ ] AI makes strategic moves (not random)
- [ ] No memory leaks or crashes

### Sample Test Session

```bash
# Test SUS Game with AI
./BoardGames
> 1  # Select SUS Game
> Ahmed  # Player 1 name
> 2  # AI player
> Comp  # Player 2 name
> 1  # Human player
# Play game and verify AI makes strategic moves
```

## Contributing

Contributions are welcome! Please follow these guidelines:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/AmazingFeature`)
3. **Commit** your changes (`git commit -m 'Add some AmazingFeature'`)
4. **Push** to the branch (`git push origin feature/AmazingFeature`)
5. **Open** a Pull Request

### Coding Standards

- Follow existing code style
- Add Doxygen comments for new classes/functions
- Test thoroughly before submitting
- Update README if adding new features

## Future Enhancements

Potential improvements for future versions:

- [ ] Graphical UI using SDL2 or Qt
- [ ] Network multiplayer support
- [ ] Save/load game functionality
- [ ] Replay system for game analysis
- [ ] More sophisticated AI algorithms (deep learning)
- [ ] Tournament mode for multiple players
- [ ] Statistics and leaderboards
- [ ] Hint system for beginners
- [ ] Undo/redo functionality
- [ ] Configurable difficulty levels for AI

## Known Issues

- Word Tic-Tac-Toe requires `dic.txt` in same directory
- Ultimate Tic-Tac-Toe UI could be more intuitive
- Some AI players are random (can be improved with minimax)

## License

This project is available for educational and personal use. Feel free to learn from, modify, and share the code.

## Acknowledgments

- Inspired by classic board games and their variants
- Framework design influenced by OOP best practices
- AI algorithms based on game theory research
- Input validation patterns from production-grade applications

## Contact

For questions, suggestions, or collaboration:

- **Primary Contact**: Ahmed Mostafa Ellaboudy
- **GitHub**: [ahmedellaboudy](https://github.com/ahmedellaboudy)
- **Repository**: [Board-Games-project](https://github.com/ahmedellaboudy/Board-Games-project)

---

**Enjoy playing!** 🎮

*Built with passion by a team of four C++ enthusiasts*
