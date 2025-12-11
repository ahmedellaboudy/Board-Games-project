// ValidatedUI.h
// A custom base UI class with input validation helpers

#ifndef VALIDATED_UI_H
#define VALIDATED_UI_H

#include "BoardGame_Classes.h"
#include <limits>
#include <utility>

/**
 * @brief Extended UI class with input validation utilities
 * @tparam T Type of symbol used on the board
 */
template <typename T>
class ValidatedUI : public UI<T> {
protected:
    /**
     * @brief Get validated integer input within a range
     * @param prompt Message to display to user
     * @param min Minimum valid value (inclusive)
     * @param max Maximum valid value (inclusive)
     * @return Valid integer within range
     */
    int get_validated_int(const string& prompt, int min, int max) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                if (value >= min && value <= max) {
                    return value;
                }
                cout << "Invalid input! Please enter a number between "
                     << min << " and " << max << ".\n";
            } else {
                cout << "Invalid input! Please enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    /**
     * @brief Get validated coordinates for board position
     * @param prompt Message to display
     * @param max_row Maximum row value (exclusive, so for 0-2 pass 3)
     * @param max_col Maximum column value (exclusive, so for 0-4 pass 5)
     * @param board_ptr Pointer to board to check if cell is empty (optional)
     * @param empty_symbol Symbol representing empty cell
     * @return Pair of (x, y) coordinates
     */
    pair<int, int> get_validated_position(
        const string& prompt,
        int max_row,
        int max_col,
        Board<T>* board_ptr = nullptr,
        T empty_symbol = T()) {

        int x, y;
        while (true) {
            cout << prompt;

            if (!(cin >> x >> y)) {
                cout << "Invalid input! Please enter two numbers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (x < 0 || x >= max_row || y < 0 || y >= max_col) {
                cout << "Invalid position! Row must be 0-" << (max_row-1)
                     << " and column must be 0-" << (max_col-1) << ".\n";
                continue;
            }

            if (board_ptr != nullptr && board_ptr->get_cell(x, y) != empty_symbol) {
                cout << "Cell already occupied! Choose another position.\n";
                continue;
            }

            return {x, y};
        }
    }

    /**
     * @brief Get validated choice from menu options
     * @param prompt Message to display
     * @param num_options Number of valid options (1 to num_options)
     * @return Valid choice
     */
    int get_menu_choice(const string& prompt, int num_options) {
        return get_validated_int(prompt, 1, num_options);
    }

    /**
     * @brief Clear any remaining input in the buffer
     */
    void clear_input_buffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    /**
     * @brief Override base class method with proper validation
     * @param player_label Label for the player (e.g., "Player X")
     * @param options Vector of type options (e.g., {"Human", "Computer"})
     * @return PlayerType selected by user
     */
    PlayerType get_player_type_choice(string player_label, const vector<string>& options) override {
        cout << "Choose " << player_label << " type:\n";
        for (size_t i = 0; i < options.size(); ++i)
            cout << i + 1 << ". " << options[i] << "\n";

        int choice;
        while (true) {
            cout << "Enter choice: ";
            if (cin >> choice) {
                if (choice >= 1 && choice <= (int)options.size()) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return (choice == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
                }
                cout << "Invalid choice! Please enter a number between 1 and "
                     << options.size() << ".\n";
            } else {
                cout << "Invalid input! Please enter a number.\n";
                clear_input_buffer();
            }
        }
    }

public:
    /**
     * @brief Constructor with cell width
     */
    ValidatedUI(int cell_display_width = 3)
        : UI<T>(cell_display_width) {}

    /**
     * @brief Constructor with message and cell width
     */
    ValidatedUI(const string& message, int cell_display_width = 3)
        : UI<T>(message, cell_display_width) {}

    virtual ~ValidatedUI() {}
};

#endif // VALIDATED_UI_H