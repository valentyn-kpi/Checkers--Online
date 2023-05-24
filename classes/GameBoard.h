#ifndef CHECKERS_GAMEBOARD_H
#define CHECKERS_GAMEBOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "UI/Menu.h"
#include <vector>

/**
 * Клас GameBoard об'єктом якого є ігрове поле
 * Цей клас відповідає за ігрову графіку та логіку
 */
class GameBoard {
public:
    explicit GameBoard(sf::RenderTarget &target, bool isRedTurn = true);

    void handleEvent(sf::Event event);

    void draw();

    enum {
        RED_WON, BLACK_WON, DRAW, RED_TURN, BLACK_TURN
    };

    sf::Vector2u getBoardSize() const;

    int getGameState() const;

    enum {
        RED_C, BLACK_C
    };
    int getPieceCount(int type) const;

private:
    void selectAvailableMoves();

    void updateAvailableMoves();

    void selectPiece(int x, int y);

    void movePiece(int x, int y);

    void drawBoard();

    void drawCheckers();

    void drawAvailableMoves();

    void createTexture(sf::RenderTexture &texture, bool black, bool king) const;

    void updateDrawables();

    enum {
        EMPTY, RED, BLACK, RED_KING, BLACK_KING
    };
    struct Checker {
        int x;
        int y;
        int type;
    };
    enum {
        NORMAL, CAPTURE
    };

    struct Move {
        Checker checker;
        int x;
        int y;
        int type;

        bool operator==(const Move &other) const {
            return x == other.x && y == other.y;
        }
    };

    sf::RenderTarget *target;
    sf::RenderTexture boardTexture;
    sf::RenderTexture redCheckerTexture;
    sf::RenderTexture blackCheckerTexture;
    sf::RenderTexture redKingTexture;
    sf::RenderTexture blackKingTexture;
    sf::RenderTexture shadowTexture;
    sf::SoundBuffer checkerSoundBuffer;
    sf::Sound checkerSound;
    sf::Font font;
    Checker checkers[8][8]{EMPTY};
    Checker selectedChecker = {-1, -1, EMPTY};
    bool isRedTurn = true;
    bool isInCapture = false;
    float squareSize;
    std::vector<Move> selectedAvailableMoves;
    std::vector<Move> availableMoves;
    void processSelection(int y, int x);

    void renderShadow();
};

#endif //CHECKERS_GAMEBOARD_H