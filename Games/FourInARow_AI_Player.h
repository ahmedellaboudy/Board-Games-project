// FourInARow_AI_Player.h
// Smart AI player for Four-in-a-Row using Minimax with Alpha-Beta Pruning

#ifndef FOUR_IN_A_ROW_AI_PLAYER_H
#define FOUR_IN_A_ROW_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "FourInARow.h"
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

/**
 * @brief Smart AI Player for Four-in-a-Row using Minimax algorithm
 */
class FourInARow_AI_Player : public Player<char> {
private:
    const int MAX_DEPTH = 6; // Search depth limit for performance

    /**
     * @brief Find the lowest available row in a column
     */
    int find_lowest_row(vector<vector<char>>& board, int col) {
        for (int row = 5; row >= 0; row--) {
            if (board[row][col] == ' ') {
                return row;
            }
        }
        return -1;
    }

    /**
     * @brief Check if there are four in a row for given symbol
     */
    bool check_four_in_row(vector<vector<char>>& board, char sym) {
        // Horizontal
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col <= 3; col++) {
                if (board[row][col] == sym &&
                    board[row][col + 1] == sym &&
                    board[row][col + 2] == sym &&
                    board[row][col + 3] == sym) {
                    return true;
                }
            }
        }

        // Vertical
        for (int col = 0; col < 7; col++) {
            for (int row = 0; row <= 2; row++) {
                if (board[row][col] == sym &&
                    board[row + 1][col] == sym &&
                    board[row + 2][col] == sym &&
                    board[row + 3][col] == sym) {
                    return true;
                }
            }
        }

        // Diagonal (bottom-left to top-right)
        for (int row = 3; row < 6; row++) {
            for (int col = 0; col <= 3; col++) {
                if (board[row][col] == sym &&
                    board[row - 1][col + 1] == sym &&
                    board[row - 2][col + 2] == sym &&
                    board[row - 3][col + 3] == sym) {
                    return true;
                }
            }
        }

        // Diagonal (top-left to bottom-right)
        for (int row = 0; row <= 2; row++) {
            for (int col = 0; col <= 3; col++) {
                if (board[row][col] == sym &&
                    board[row + 1][col + 1] == sym &&
                    board[row + 2][col + 2] == sym &&
                    board[row + 3][col + 3] == sym) {
                    return true;
                }
            }
        }

        return false;
    }

    /**
     * @brief Evaluate board position (heuristic)
     */
    int evaluate_position(vector<vector<char>>& board, char ai_sym, char opp_sym) {
        // Check terminal states first
        if (check_four_in_row(board, ai_sym)) return 100000;
        if (check_four_in_row(board, opp_sym)) return -100000;

        int score = 0;

        // Evaluate all windows of 4
        // Horizontal
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col <= 3; col++) {
                int ai_count = 0, opp_count = 0, empty = 0;
                for (int i = 0; i < 4; i++) {
                    if (board[row][col + i] == ai_sym) ai_count++;
                    else if (board[row][col + i] == opp_sym) opp_count++;
                    else empty++;
                }
                score += evaluate_window(ai_count, opp_count, empty);
            }
        }

        // Vertical
        for (int col = 0; col < 7; col++) {
            for (int row = 0; row <= 2; row++) {
                int ai_count = 0, opp_count = 0, empty = 0;
                for (int i = 0; i < 4; i++) {
                    if (board[row + i][col] == ai_sym) ai_count++;
                    else if (board[row + i][col] == opp_sym) opp_count++;
                    else empty++;
                }
                score += evaluate_window(ai_count, opp_count, empty);
            }
        }

        // Diagonal (bottom-left to top-right)
        for (int row = 3; row < 6; row++) {
            for (int col = 0; col <= 3; col++) {
                int ai_count = 0, opp_count = 0, empty = 0;
                for (int i = 0; i < 4; i++) {
                    if (board[row - i][col + i] == ai_sym) ai_count++;
                    else if (board[row - i][col + i] == opp_sym) opp_count++;
                    else empty++;
                }
                score += evaluate_window(ai_count, opp_count, empty);
            }
        }

        // Diagonal (top-left to bottom-right)
        for (int row = 0; row <= 2; row++) {
            for (int col = 0; col <= 3; col++) {
                int ai_count = 0, opp_count = 0, empty = 0;
                for (int i = 0; i < 4; i++) {
                    if (board[row + i][col + i] == ai_sym) ai_count++;
                    else if (board[row + i][col + i] == opp_sym) opp_count++;
                    else empty++;
                }
                score += evaluate_window(ai_count, opp_count, empty);
            }
        }

        // Center column preference
        for (int row = 0; row < 6; row++) {
            if (board[row][3] == ai_sym) score += 5;
        }

        return score;
    }

    /**
     * @brief Evaluate a window of 4 cells
     */
    int evaluate_window(int ai_count, int opp_count, int empty) {
        if (ai_count == 4) return 10000;
        if (opp_count == 4) return -10000;

        if (ai_count == 3 && empty == 1) return 500;
        if (ai_count == 2 && empty == 2) return 50;

        if (opp_count == 3 && empty == 1) return -400;
        if (opp_count == 2 && empty == 2) return -40;

        return 0;
    }

    /**
     * @brief Get valid columns
     */
    vector<int> get_valid_columns(vector<vector<char>>& board) {
        vector<int> valid;
        for (int c = 0; c < 7; c++) {
            if (board[0][c] == ' ') {
                valid.push_back(c);
            }
        }
        return valid;
    }

    /**
     * @brief Minimax algorithm with alpha-beta pruning
     */
    int minimax(vector<vector<char>>& board, int depth, bool is_maximizing,
                int alpha, int beta, char ai_sym, char opp_sym) {

        vector<int> valid_cols = get_valid_columns(board);

        // Terminal states
        if (check_four_in_row(board, ai_sym)) return 100000 - depth;
        if (check_four_in_row(board, opp_sym)) return -100000 + depth;
        if (valid_cols.empty()) return 0; // Draw
        if (depth == 0) return evaluate_position(board, ai_sym, opp_sym);

        if (is_maximizing) {
            int max_eval = numeric_limits<int>::min();

            for (int col : valid_cols) {
                int row = find_lowest_row(board, col);
                if (row != -1) {
                    board[row][col] = ai_sym;

                    int eval = minimax(board, depth - 1, false, alpha, beta, ai_sym, opp_sym);

                    board[row][col] = ' ';

                    max_eval = max(max_eval, eval);
                    alpha = max(alpha, eval);

                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            return max_eval;
        } else {
            int min_eval = numeric_limits<int>::max();

            for (int col : valid_cols) {
                int row = find_lowest_row(board, col);
                if (row != -1) {
                    board[row][col] = opp_sym;

                    int eval = minimax(board, depth - 1, true, alpha, beta, ai_sym, opp_sym);

                    board[row][col] = ' ';

                    min_eval = min(min_eval, eval);
                    beta = min(beta, eval);

                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            return min_eval;
        }
    }

public:
    /**
     * @brief Constructor for AI player
     */
    FourInARow_AI_Player(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::AI) {}

    /**
     * @brief Get best move using minimax algorithm
     */
    int get_best_column() {
        vector<vector<char>> board = boardPtr->get_board_matrix();
        vector<int> valid_cols = get_valid_columns(board);

        if (valid_cols.empty()) return 3;

        char ai_sym = symbol;
        char opp_sym = (symbol == 'X') ? 'O' : 'X';

        // Check for immediate win or block
        for (int col : valid_cols) {
            int row = find_lowest_row(board, col);
            if (row != -1) {
                // Check if this move wins
                board[row][col] = ai_sym;
                if (check_four_in_row(board, ai_sym)) {
                    board[row][col] = ' ';
                    return col;
                }
                board[row][col] = ' ';

                // Check if we need to block
                board[row][col] = opp_sym;
                if (check_four_in_row(board, opp_sym)) {
                    board[row][col] = ' ';
                    return col;
                }
                board[row][col] = ' ';
            }
        }

        int best_col = valid_cols[0];
        int best_score = numeric_limits<int>::min();

        int alpha = numeric_limits<int>::min();
        int beta = numeric_limits<int>::max();

        // Try each valid column
        for (int col : valid_cols) {
            int row = find_lowest_row(board, col);
            if (row != -1) {
                board[row][col] = ai_sym;

                int score = minimax(board, MAX_DEPTH - 1, false, alpha, beta, ai_sym, opp_sym);

                board[row][col] = ' ';

                if (score > best_score) {
                    best_score = score;
                    best_col = col;
                }

                alpha = max(alpha, score);
            }
        }

        return best_col;
    }
};

#endif // FOUR_IN_A_ROW_AI_PLAYER_H
