#include <vector>
/**
Maximilian Peresunchak (st152466@stud.uni-stuttgart.de)
Nico Reng (st188620@stud.uni-stuttgart.de)
Viorel Tsigos (st188085@stud.uni-stuttgart.de)
Philip Reimann (st182312@stud.uni-stuttgart.de)
Christian Keller (st166512@stud.uni-stuttgart.de)
Florian Frank  (st@stud.uni-stuttgart.de)
Johannes Heugel (st@stud.uni-stuttgart.de)
Maysaa Abualqumboz (st@stud.uni-stuttgart.de)
Benedikt Wachmer (st177118@stud.uni-stuttgart.de)
Miles Holl (st@stud.uni-stuttgart.de)
*/

/**
 * @brief Represents a 2D position on the Game of Life board. // KI-generiert
 */
struct Position {
    int x{};
    int y{};
    
    /**
     * @brief Adds two Position objects component-wise.
     * @param otherPosition Another position to add.
     * @return New Position equal to the sum of this and otherPosition. // KI-generiert
     */
    Position operator+(const Position& otherPosition){
        return {x + otherPosition.x, y + otherPosition.y};
    }
};

/**
 * @brief Represents a single cell on the Game of Life board.
 *
 * Each cell can either be alive or dead. No other properties are stored. // KI-generiert
 */
struct GameCell{
    bool isAlive{false}; ///< Cells are set to dead by default
};

/**
 * @brief Implements Conway's Game of Life simulation logic.
 *
 * This class manages the game grid, calculates generations, and provides
 * methods to manipulate and query the board. It supports arbitrary grid sizes. // KI-generiert
 */
class GameOfLife
{
private:
    // --- Static Data ---
    /**
     * @brief Relative positions of all 8 neighboring cells (Moore neighborhood).
     *
     * Ordered clockwise: right, top, top-right, bottom-right, bottom,
     * bottom-left, left, top-left. // KI-generiert
     */
    static const std::vector<Position> neighborPositionOffsets;
    
    int boardWidth;
    int boardHeight;

    // --- Instance Data ---
    std::vector<std::vector<GameCell>> activeBoard;
    std::vector<std::vector<GameCell>> nextGenerationBufferBoard; ///< We use a buffer in order to not mix user input and computation.

    // --- Internal Helper Functions ---
    /**
     * @brief Checks whether a given position lies within the board boundaries.
     * @param position Position to check.
     * @return True if the position is within the board; false otherwise. // KI-generiert
     */
    bool isInBounds(Position position) const;

    /**
     * @brief Determines whether a cell will be alive in the next generation.
     * @param centerCellPosition Position of the cell to check.
     * @return True if the cell will be alive in the next generation. // KI-generiert
     */
    bool willCellBeAliveNextGeneration(Position centerCellPosition) const;

    /**
     * @brief Marks a cell as alive in the next-generation buffer.
     * @param position Position of the cell to mark alive. // KI-generiert
     */
    void setAliveInBuffer(Position position);

    /**
     * @brief Creates a new empty (all-dead) board of the correct size.
     * @return A 2D vector representing an empty board. // KI-generiert
     */
    std::vector<std::vector<GameCell>> getBlankBoard() const;

    /**
     * @brief Returns all valid neighboring positions for a given cell.
     * @param centerCellPosition Position of the center cell.
     * @return A vector of neighboring positions (within bounds). // KI-generiert
     */
    std::vector<Position> getNeighbors(Position centerCellPosition) const;

public:
    // --- Constructors ---
    /**
     * @brief Constructs a new GameOfLife board.
     * @param boardWidth  Number of columns.
     * @param boardHeight Number of rows. // KI-generiert
     */
    GameOfLife(int boardWidth, int boardHeight);

    // --- Public API ---
    /**
     * @brief Checks whether a cell at the given position is currently alive.
     * @param position Position to check.
     * @return True if the cell is alive; false otherwise.
     * @throws std::out_of_range if the position is outside the board. // KI-generiert
     */
    bool isAlive(Position position) const;

    /**
     * @brief Sets a cell to be alive on the active board.
     * @param position Position of the cell to activate.
     * @throws std::out_of_range if the position is outside the board. // KI-generiert
     */
    void setAlive(Position position);
    
    /**
     * @brief Advances the simulation by one generation.
     *
     * Applies the Game of Life rules to determine which cells
     * live, die, or are born in the next generation. // KI-generiert
     */
    void step();

    /**
     * @brief Prints the current state of the board to the console.
     *
     * Alive cells are displayed as 'X', dead cells as '_'.
     * Useful for debugging or visualizing small boards. // KI-generiert
     */
    void printBoard() const;
};
