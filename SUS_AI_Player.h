// SUS_AI_Player.h
// Strategic AI player for SUS game using pattern-based heuristics

#ifndef SUS_AI_PLAYER_H
#define SUS_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "sus.h"
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Move with strategic evaluation
 */
struct ScoredMove {
    int x;
    int y;
    int score;

    ScoredMove(int x = -1, int y = -1, int score = 0)
        : x(x), y(y), score(score) {}
};

/**
 * @brief Strategic AI for SUS game using pattern recognition
 */
class SUS_AI_Player : public Player<char> {
private:
    char opp_symbol;

    /**
     * @brief Check if placing symbol at (r, c) completes S-U-S
     */
    bool creates_sus_pattern(vector<vector<char>>& grid, int r, int c, char sym) {
        char original = grid[r][c];
        grid[r][c] = sym;
        bool found = false;

        // Check horizontal pattern at this row
        if (grid[r][0] == 'S' && grid[r][1] == 'U' && grid[r][2] == 'S') {
            found = true;
        }

        // Check vertical pattern at this column
        if (grid[0][c] == 'S' && grid[1][c] == 'U' && grid[2][c] == 'S') {
            found = true;
        }

        // Check main diagonal if on it
        if (r == c && grid[0][0] == 'S' && grid[1][1] == 'U' && grid[2][2] == 'S') {
            found = true;
        }

        // Check anti-diagonal if on it
        if (r + c == 2 && grid[0][2] == 'S' && grid[1][1] == 'U' && grid[2][0] == 'S') {
            found = true;
        }

        grid[r][c] = original;
        return found;
    }

    /**
     * @brief Calculate strategic value of a position
     */
    int calculate_position_value(vector<vector<char>>& grid, int r, int c) {
        int value = 0;

        // Center position is most valuable (part of both diagonals)
        if (r == 1 && c == 1) {
            value += 15;
        }

        // Corner positions (part of one diagonal each)
        if ((r == 0 && c == 0) || (r == 2 && c == 2) ||
            (r == 0 && c == 2) || (r == 2 && c == 0)) {
            value += 8;
        }

        // Edge positions
        if ((r == 1 && c != 1) || (c == 1 && r != 1)) {
            value += 5;
        }

        return value;
    }

    /**
     * @brief Count potential patterns this move enables
     */
    int count_potential_patterns(vector<vector<char>>& grid, int r, int c, char sym) {
        int potential = 0;
        char temp = grid[r][c];
        grid[r][c] = sym;

        // Check row potential
        int s_count = 0, u_count = 0, empty = 0;
        for (int j = 0; j < 3; j++) {
            if (grid[r][j] == 'S') s_count++;
            else if (grid[r][j] == 'U') u_count++;
            else empty++;
        }
        if (s_count >= 2 && u_count >= 1 && empty == 0) potential += 3;
        else if (s_count >= 1 && u_count >= 1 && empty == 1) potential += 2;

        // Check column potential
        s_count = u_count = empty = 0;
        for (int i = 0; i < 3; i++) {
            if (grid[i][c] == 'S') s_count++;
            else if (grid[i][c] == 'U') u_count++;
            else empty++;
        }
        if (s_count >= 2 && u_count >= 1 && empty == 0) potential += 3;
        else if (s_count >= 1 && u_count >= 1 && empty == 1) potential += 2;

        // Check diagonals if applicable
        if (r == c) {
            s_count = u_count = empty = 0;
            for (int i = 0; i < 3; i++) {
                if (grid[i][i] == 'S') s_count++;
                else if (grid[i][i] == 'U') u_count++;
                else empty++;
            }
            if (s_count >= 2 && u_count >= 1 && empty == 0) potential += 3;
            else if (s_count >= 1 && u_count >= 1 && empty == 1) potential += 2;
        }

        if (r + c == 2) {
            s_count = u_count = empty = 0;
            for (int i = 0; i < 3; i++) {
                if (grid[i][2-i] == 'S') s_count++;
                else if (grid[i][2-i] == 'U') u_count++;
                else empty++;
            }
            if (s_count >= 2 && u_count >= 1 && empty == 0) potential += 3;
            else if (s_count >= 1 && u_count >= 1 && empty == 1) potential += 2;
        }

        grid[r][c] = temp;
        return potential;
    }

    /**
     * @brief Evaluate move using multiple strategies
     */
    int evaluate_move_quality(vector<vector<char>>& grid, int r, int c) {
        int total_score = 0;

        // Strategy 1: Check if this completes our pattern (highest priority)
        if (creates_sus_pattern(grid, r, c, symbol)) {
            total_score += 100;
        }

        // Strategy 2: Check if this blocks opponent pattern (high priority)
        if (creates_sus_pattern(grid, r, c, opp_symbol)) {
            total_score += 80;
        }

        // Strategy 3: Position value
        total_score += calculate_position_value(grid, r, c);

        // Strategy 4: Future potential
        total_score += count_potential_patterns(grid, r, c, symbol);

        // Strategy 5: Blocking opponent potential
        total_score += count_potential_patterns(grid, r, c, opp_symbol) / 2;

        return total_score;
    }

public:
    /**
     * @brief Constructor
     */
    SUS_AI_Player(string name, char sym, char opponent)
        : Player<char>(name, sym, PlayerType::AI), opp_symbol(opponent) {}

    /**
     * @brief Find best strategic move
     */
    ScoredMove get_best_move(int ai_score, int opp_score) {
        vector<vector<char>> grid = boardPtr->get_board_matrix();
        ScoredMove optimal_move(-1, -1, -1000);

        // Evaluate all empty positions
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == '.') {
                    int move_score = evaluate_move_quality(grid, i, j);

                    // Add score difference consideration
                    if (ai_score < opp_score) {
                        // We're behind, prioritize completing patterns
                        if (creates_sus_pattern(grid, i, j, symbol)) {
                            move_score += 50;
                        }
                    } else if (ai_score > opp_score) {
                        // We're ahead, prioritize blocking
                        if (creates_sus_pattern(grid, i, j, opp_symbol)) {
                            move_score += 50;
                        }
                    }

                    if (move_score > optimal_move.score) {
                        optimal_move.x = i;
                        optimal_move.y = j;
                        optimal_move.score = move_score;
                    }
                }
            }
        }

        return optimal_move;
    }
};

#endif // SUS_AI_PLAYER_H