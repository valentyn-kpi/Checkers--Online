//
// Created by valen on 5/5/2023.
//

#include <iostream>
#include <cmath>
#include "GameBoard.h"

/**
 * Конструктор класу GameBoard
 * @param target вікно в якому буде відображатися ігрове поле
 * @param isRedTurn чи черга білих(червоних?)
 */
GameBoard::GameBoard(sf::RenderTarget &target, bool isRedTurn) {
    this->target = &target;
    this->isRedTurn = isRedTurn;
    squareSize = (float) (target.getSize().y) / 8.0f;
    font.loadFromFile("res/fonts/chess.ttf");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i < 3 && (i + j) % 2) {
                checkers[i][j].type = isRedTurn ? BLACK : RED;
            } else if (i > 4 && (i + j) % 2) {
                checkers[i][j].type = isRedTurn ? RED : BLACK;
            } else {
                checkers[i][j].type = EMPTY;
            }
            checkers[i][j].y = i;
            checkers[i][j].x = j;
        }
    }
    updateDrawables();
    updateAvailableMoves();
    if (!checkerSoundBuffer.loadFromFile("res/audio/checkermove.wav")) {
    }
}

/**
 * Оновлює текстури гральної дошки
 */
void GameBoard::updateDrawables() {
    const sf::Color board_dark(196, 157, 113);
    const sf::Color board_light(252, 227, 175);
    squareSize = (float) (target->getSize().y) / 8.1f;
    boardTexture.create(static_cast<unsigned int>(squareSize * 8.2f), static_cast<unsigned int>(squareSize * 8.2f));
    boardTexture.clear(sf::Color::Transparent);
    for (int i = 0; i < 8; i++) {
        float y = (float) i * squareSize;
        sf::RectangleShape board;
        for (int j = 0; j < 8; j++) {
            float x = (float) j * squareSize;
            board.setSize(sf::Vector2f(squareSize * .98f, squareSize * .98f));
            board.setOrigin(squareSize / 2, squareSize / 2);
            board.setPosition(x + squareSize / 2 + squareSize * 0.04f, y + squareSize / 2 + squareSize * 0.04f);
            if ((i + j) % 2 == 0) {
                board.setFillColor(board_light);
            } else {
                board.setFillColor(board_dark);
            }
            boardTexture.draw(board);
        }
    }
    boardTexture.display();

    createTexture(redCheckerTexture, false, false);
    createTexture(blackCheckerTexture, true, false);
    createTexture(redKingTexture, false, true);
    createTexture(blackKingTexture, true, true);
    renderShadow();
}

/**
 * створює текстуру шашки
 */
void GameBoard::createTexture(sf::RenderTexture &texture, bool black, bool king) const {
    texture.create((uint32_t) squareSize, (uint32_t) squareSize);
    texture.setSmooth(true);
    texture.clear(sf::Color::Transparent);
    const sf::Color black_color = sf::Color(50, 50, 50);
    const sf::Color white_color = sf::Color(200, 200, 200);
    const sf::Color inner_black_color = sf::Color(100, 100, 100);
    const sf::Color inner_white_color = sf::Color(230, 230, 230);

    const float center_pos = squareSize / 2 + squareSize * 0.04f;
    const float radius1 = squareSize / 2.5f;

    sf::CircleShape circle(radius1);
    circle.setOrigin(radius1, radius1);
    circle.setPosition(center_pos, center_pos);
    circle.setFillColor(black ? black_color : white_color);
    texture.draw(circle);

    const float radius2 = squareSize / 3.f;
    circle.setRadius(radius2);
    circle.setOrigin(radius2, radius2);
    circle.setPosition(center_pos, center_pos);
    circle.setFillColor(black ? inner_black_color : inner_white_color);
    texture.draw(circle);
    if (king) {
        sf::Text text("q", font, static_cast<int>(squareSize / 2.0f));
        text.setFillColor(black ? white_color : black_color);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(center_pos, center_pos);
        texture.draw(text);
    } else {
        const float radius3 = squareSize / 4.5f;
        circle.setRadius(radius3);
        circle.setOrigin(radius3, radius3);
        circle.setPosition(center_pos, center_pos);
        circle.setFillColor(black ? black_color : white_color);
        texture.draw(circle);
    }

    texture.display();
}

/**
 * Малює гральну дошку
 */
void GameBoard::drawBoard() {
    target->draw(sf::Sprite(boardTexture.getTexture()));
}

/**
 * Малює шашки
 */
void GameBoard::drawCheckers() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (checkers[i][j].type == EMPTY) continue;
                sf::Sprite shadowSprite(shadowTexture.getTexture());
                shadowSprite.setPosition((float) j * squareSize, (float) i * squareSize);
                target->draw(shadowSprite);
            if (checkers[i][j].type == RED) {
                sf::Sprite redChecker(redCheckerTexture.getTexture());
                redChecker.setPosition((float) j * squareSize, (float) i * squareSize);
                target->draw(redChecker);
            } else if (checkers[i][j].type == BLACK) {
                sf::Sprite blackChecker(blackCheckerTexture.getTexture());
                blackChecker.setPosition((float) j * squareSize, (float) i * squareSize);
                target->draw(blackChecker);
            } else if (checkers[i][j].type == RED_KING) {
                sf::Sprite redKing(redKingTexture.getTexture());
                redKing.setPosition((float) j * squareSize, (float) i * squareSize);
                target->draw(redKing);
            } else if (checkers[i][j].type == BLACK_KING) {
                sf::Sprite blackKing(blackKingTexture.getTexture());
                blackKing.setPosition((float) j * squareSize, (float) i * squareSize);
                target->draw(blackKing);
            }
        }
    }
}

/**
 * Обводить шашку, яка вибрана
 * Та шашки які можуть зробити хід
 */
void GameBoard::drawAvailableMoves() {
    if (selectedChecker.type != EMPTY) {
        for (auto &move: selectedAvailableMoves) {
            // Create a sprite for the available move
            sf::Sprite sprite;
            if (selectedChecker.type == RED) {
                sprite.setTexture(redCheckerTexture.getTexture());
            } else if (selectedChecker.type == BLACK) {
                sprite.setTexture(blackCheckerTexture.getTexture());
            } else if (selectedChecker.type == RED_KING) {
                sprite.setTexture(redKingTexture.getTexture());
            } else if (selectedChecker.type == BLACK_KING) {
                sprite.setTexture(blackKingTexture.getTexture());
            }
            sprite.setPosition((float) move.x * squareSize, (float) move.y * squareSize);
            sprite.setColor(sf::Color(255, 255, 255, 150));
            target->draw(sprite);
        }
    }
    for (auto &move: availableMoves) {
        sf::RectangleShape square(sf::Vector2f(squareSize * .98f, squareSize * .98f));
        square.setPosition((float) move.checker.x * squareSize + squareSize * 0.04f, (float) move.checker.y * squareSize + squareSize * 0.04f);
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineThickness(squareSize * 0.025f);
        if (move.checker.x == selectedChecker.x && move.checker.y == selectedChecker.y) {
            square.setOutlineColor(sf::Color(36, 255, 36));
        } else {
            square.setOutlineColor(sf::Color(255, 36, 35));
        }
        target->draw(square);
    }
}

/**
 * Малює гральну дошку, шашки та можливі ходи
 */
void GameBoard::draw() {
    drawBoard();
    drawCheckers();
    drawAvailableMoves();
}

/**
 * Обробка подій (миші, зміна розміру вікна і тд)
 */
void GameBoard::handleEvent(sf::Event event) {
    //if resized
    if (event.type == sf::Event::Resized) {
        updateDrawables();
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            if (x >= 0 && x < static_cast<int>(squareSize * 8) && y >= 0 && y < static_cast<int>(squareSize * 8)) {
                int xIndex = static_cast<int>(static_cast<float>(x) / squareSize);
                int yIndex = static_cast<int>(static_cast<float>(y) / squareSize);
                processSelection(yIndex, xIndex);
            }
        }
    }
}

/**
 * Обробка взаємодії з шашкою
 */
void GameBoard::processSelection(int y, int x) {
    if ((selectedChecker.type == EMPTY || checkers[y][x].type != EMPTY) && !isInCapture) {
        selectPiece(x, y);
    } else {
        movePiece(x, y);
    }
}

/**
 * Хід шашкою
 */
void GameBoard::movePiece(int x, int y) {
    for (auto &move: availableMoves) {
        if (move.checker.x == selectedChecker.x && move.checker.y == selectedChecker.y && move.x == x && move.y == y) {
            checkers[y][x].type = selectedChecker.type;
            checkers[selectedChecker.y][selectedChecker.x].type = EMPTY;
            if (abs(selectedChecker.y - y) >= 2) {
                for (int dx = selectedChecker.x, dy = selectedChecker.y;
                     dx != x && dy != y; dx += (x - selectedChecker.x) / abs(x - selectedChecker.x), dy += (y - selectedChecker.y) / abs(y - selectedChecker.y)) {
                    checkers[dy][dx].type = EMPTY;
                }
            }
            if (isRedTurn) {
                if (y == 0) {
                    checkers[y][x].type = RED_KING;
                }
            } else {
                if (y == 7) {
                    checkers[y][x].type = BLACK_KING;
                }
            }
            checkerSound.setBuffer(checkerSoundBuffer);
            checkerSound.setPlayingOffset(sf::seconds(0.00001f));
            checkerSound.play();
            if (move.type == CAPTURE) {
                updateAvailableMoves();
                selectPiece(x, y);
                selectAvailableMoves();
                for (auto &next_move: selectedAvailableMoves) {
                    if (next_move.type == CAPTURE && next_move.checker.x == x && next_move.checker.y == y) {
                        isInCapture = true;
                        return;
                    }
                }
            }
            isRedTurn = !isRedTurn;
            selectedChecker.type = EMPTY;
            updateAvailableMoves();
            isInCapture = false;
            return;
        }
    }
}

/**
 * Вибір шашки
 */
void GameBoard::selectPiece(int x, int y) {
    if (checkers[y][x].type != (isRedTurn ? RED : BLACK) && checkers[y][x].type != (isRedTurn ? RED_KING : BLACK_KING)) {
        return;
    }
    selectedChecker.type = checkers[y][x].type;
    selectedChecker.x = x;
    selectedChecker.y = y;
    std::cout << "Selected: " << selectedChecker.y << " " << selectedChecker.x << std::endl;
    selectAvailableMoves();
}

/**
 * Оновлення доступних ходів вибраної шашки
 */
void GameBoard::selectAvailableMoves() {
    selectedAvailableMoves.clear();
    for (const auto &move: availableMoves) {
        if (move.checker.x == selectedChecker.x && move.checker.y == selectedChecker.y) {
            selectedAvailableMoves.push_back(move);
        }
    }
}

/**
 * Стан гри
 * TODO: додати нічию
 */
int GameBoard::getGameState() const {
    if (availableMoves.empty()) {
        return isRedTurn ? BLACK_WON : RED_WON;
    } else {
        return isRedTurn ? RED_TURN : BLACK_TURN;
    }
}

/**
 * Оновлення всіх доступних ходів для всіх шашок гравця, що має ходити
 */
void GameBoard::updateAvailableMoves() {
    availableMoves.clear();
    bool captureAvailable = false;
    /*
     * Шукаємо шашки, які можуть зробити захоплення
     */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Checker &checker = checkers[i][j];
            if (checker.type != EMPTY &&
                ((checker.type == RED && isRedTurn)
                 || (checker.type == BLACK && !isRedTurn))) {
                int maxDistance = (checker.type == RED_KING || checker.type == BLACK_KING) ? 8 : 1;
                for (int dy = -maxDistance; dy <= maxDistance; dy++) {
                    for (int dx = -maxDistance; dx <= maxDistance; dx++) {
                        if (dx == 0 || dy == 0 || abs(dx) != abs(dy)) {
                            continue;
                        }
                        int x = j + dx;
                        int y = i + dy;
                        if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                            // Skip moves that go outside the board
                            continue;
                        }
                        if (checkers[y][x].type != EMPTY && checker.type != (isRedTurn ? RED_KING : BLACK_KING)) {
                            if (checkers[y][x].type == (isRedTurn ? RED : BLACK) || checkers[y][x].type == (isRedTurn ? RED_KING : BLACK_KING)) {
                                continue;
                            }
                            int cx = x + dx;
                            int cy = y + dy;
                            if (cx < 0 || cx >= 8 || cy < 0 || cy >= 8) {
                                continue;
                            }
                            if (checkers[cy][cx].type == EMPTY) {
                                availableMoves.push_back({checker, cx, cy, CAPTURE});
                                captureAvailable = true;
                            }
                        }
                    }
                }
            } else if (checker.type != EMPTY &&
                       ((checker.type == RED_KING && isRedTurn) ||
                        (checker.type == BLACK_KING && !isRedTurn))) {
                int maxDistance = 8;
                for (int dy = -maxDistance; dy <= maxDistance; dy++) {
                    for (int dx = -maxDistance; dx <= maxDistance; dx++) {
                        if (dx == 0 || dy == 0 || abs(dx) != abs(dy)) {
                            continue;
                        }
                        int x = j + dx;
                        int y = i + dy;
                        if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                            // Skip moves that go outside the board
                            continue;
                        }
                        if (checkers[y][x].type != EMPTY) {
                            // Skip moves that end on a non-empty square
                            continue;
                        }
                        bool isCapture = false;
                        for (int k = 1; k < abs(dx); k++) {
                            int checkX = j + k * dx / abs(dx);
                            int checkY = i + k * dy / abs(dy);
                            if (checkers[checkY][checkX].type != EMPTY) {
                                if ((checkers[checkY][checkX].type == RED || checkers[checkY][checkX].type == RED_KING) && !isRedTurn
                                    || (checkers[checkY][checkX].type == BLACK || checkers[checkY][checkX].type == BLACK_KING) && isRedTurn) {
                                    // Only capture enemy checkers
                                    if (!isCapture) {
                                        isCapture = true;
                                    } else {
                                        isCapture = false;
                                        break;
                                    }
                                } else {
                                    // Can't jump ovr multiple checkers
                                    isCapture = false;
                                    break;
                                }
                            }
                        }
                        if (isCapture) {
                            availableMoves.push_back({checker, x, y, CAPTURE});
                            captureAvailable = true;
                        }
                    }
                }
            }
        }
    }
    /**
     * Якщо доступний захоплення, то інші ходи не доступні
     */
    if (captureAvailable) {
        return;
    }
    /**
     * Якшо захоплення недоступне, то шукаємо доступні ходи
     */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Checker &checker = checkers[i][j];
            if (checker.type != EMPTY &&
                (checker.type == RED && isRedTurn
                 || checker.type == BLACK && !isRedTurn
                 || checker.type == RED_KING && isRedTurn
                 || checker.type == BLACK_KING && !isRedTurn)) {
                int maxDistance = (checker.type == RED_KING || checker.type == BLACK_KING) ? 8 : 1;
                for (int dy = -maxDistance; dy <= maxDistance; dy++) {
                    for (int dx = -maxDistance; dx <= maxDistance; dx++) {
                        if (dx == 0 || dy == 0 || abs(dx) != abs(dy)) {
                            continue;
                        }
                        int x = j + dx;
                        int y = i + dy;
                        if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                            // Skip moves that go outside the board
                            continue;
                        }
                        if (checker.type == RED && dy > 0 || checker.type == BLACK && dy < 0) {
                            continue;
                        }
                        // Check if the path is clear
                        bool pathClear = true;
                        int cx = j;
                        int cy = i;
                        while (cx != x && cy != y) {
                            cx += dx > 0 ? 1 : -1;
                            cy += dy > 0 ? 1 : -1;
                            if (checkers[cy][cx].type != EMPTY) {
                                pathClear = false;
                                break;
                            }
                        }
                        if (pathClear) {
                            if (checkers[y][x].type == EMPTY) {
                                availableMoves.push_back({checker, x, y, NORMAL});
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Отримати розмір дошки
 * @return - розмір дошки
 */
sf::Vector2u GameBoard::getBoardSize() const {
    return boardTexture.getSize();
}

/**
 * Кількість шашок на дошці
 * @return - якого гравця
 */
int GameBoard::getPieceCount(int type) const {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (type == RED_C ? (checkers[i][j].type == RED || checkers[i][j].type == RED_KING) : (checkers[i][j].type == BLACK || checkers[i][j].type == BLACK_KING)) {
                count++;
            }
        }
    }
    return count;
}

/**
 * Створення текстури тіні
 */
void GameBoard::renderShadow() {
    const float center_pos = squareSize / 2 + squareSize * 0.04f;
    const float radius1 = squareSize / 2.5f;
    shadowTexture.create( static_cast<unsigned int>(std::ceil(squareSize*1.2f)), static_cast<unsigned int>(std::ceil(squareSize*1.2f)));
    shadowTexture.clear(sf::Color::Transparent);
    sf::CircleShape shadowCircle(radius1);
    shadowCircle.setOrigin(radius1, radius1);

    for (int i = 0; i < 120; i++) {
        float alpha = 5.0f - i * 0.039f;
        shadowCircle.setFillColor(sf::Color(0, 0, 20, static_cast<sf::Uint8>(alpha)));

        float positionOffset = i * 0.1f;
        shadowCircle.setPosition(center_pos + positionOffset, center_pos + positionOffset);

        shadowTexture.draw(shadowCircle);
    }

    shadowTexture.display();
}

