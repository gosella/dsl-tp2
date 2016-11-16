#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <utility>


using namespace std;

enum cell_t {
    EMPTY = 0,
    // 1-8 for counting mines
    HIDDEN = 9,
    MINE,
    MARKED,
    QUESTION_MARK
};


struct game_model {
    bool playing;
    size_t rows;
    size_t columns;
    vector<cell_t> board;
    vector<bool> mines;
    vector<size_t> mines_near;
};

game_model new_game(size_t rows, size_t columns, size_t mines) {
    game_model model;

    size_t cells = rows * columns;
    assert(mines <= cells);

    model.playing = true;
    model.rows = rows;
    model.columns = columns;

    model.board.resize(cells, HIDDEN);
    model.mines.resize(cells, false);
    model.mines_near.resize(cells, 0);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> random_pos(0, cells-1);

    size_t p;
    while (mines-- > 0)  {
        do {
            p = random_pos(gen);
        } while (model.mines[p]);
        model.mines[p] = true;

        size_t r = p / columns;
        size_t c = p % columns;

        bool do_top = r != 0;
        bool do_bottom = r + 1 != rows;
        bool do_left = c != 0;
        bool do_right = c + 1 != columns;

        if (do_top)
            ++model.mines_near[p - columns];
        if (do_bottom)
            ++model.mines_near[p + columns];

        if (do_left) {
            auto q = p - 1;
            ++model.mines_near[q];
            if (do_top)
                ++model.mines_near[q - columns];
            if (do_bottom)
                ++model.mines_near[q + columns];
        }

        if (do_right) {
            auto q = p + 1;
            ++model.mines_near[q];
            if (do_top)
                ++model.mines_near[q - columns];
            if (do_bottom)
                ++model.mines_near[q + columns];
        }
    }

    return model;
}

void uncover(game_model & game, size_t row, size_t column) {
    size_t cell = column + row * game.columns;
    if (HIDDEN == game.board[cell]) {
        if (0 == (game.board[cell] = static_cast<cell_t>(game.mines_near[cell]))) {
            for (size_t r = max(1u, row) - 1; r < min(row + 1, game.rows - 1); ++r) {
                for (size_t c = max(1u, column) - 1; c < min(column + 1, game.columns - 1); ++c) {
                    uncover(game, r, c);
                }
            }
        }
    }
}

game_model play(game_model game, size_t row, size_t column) {
    size_t cell = column + row * game.columns;

    if (game.mines[cell]) {
        // Clicked on a mine!
        for (size_t i = 0; i < game.board.size(); ++i) {
            if (game.mines[i]) {
                game.board[i] = MINE;
            }
        }
        game.playing = false;
    } else if (game.board[cell] == HIDDEN) {
        uncover(game, row, column);
    }

    return game;
}


template<typename iter>
void display_board(const game_model & game, iter p) {
    for (size_t r = 0; r < game.rows; ++r) {
        for (size_t c = 0; c < game.columns; ++c, ++p) {
            cout << "| " << *p << " ";
        }
        cout << "|\n";
    }
}

int main() {
    auto game = new_game(8, 10, 20);

    cout << "Mines:" << endl;
    display_board(game, begin(game.mines));

    cout << "Mines near:" << endl;
    display_board(game, begin(game.mines_near));

    size_t r;
    size_t c;
    cout << "Board:" << endl;
    while(game.playing) {
        display_board(game, begin(game.board));
        cout << "Inserte Fila? ";
        cin >> r;
	cout << "Inserte Columna? ";
	cin >> c;
        game = play(game, r, c);
    }
    display_board(game, begin(game.board));
}

