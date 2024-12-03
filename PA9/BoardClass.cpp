#include "BoardClass.hpp"

Board::Board() {
    num_rows = 10;
    num_cols = 10;
    initializeBoard();
    for (int i = 0; i < 5; i++) {
        shipList[i] = nullptr;
    }
    displayPos.x = 0;
    displayPos.y = 0;
}

Vector2i Board::get_displayPos() const {
    return displayPos;
}

void Board::set_displayPos(const Vector2i& newStartDisplayPos) {
    displayPos = newStartDisplayPos;
}

void Board::initializeBoard() {
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            sea[row][col] = '~';
        }
    }
}

bool Board::placeShip(Ship* ship) {
    int pos = pos_ship(ship->getID());
    if (pos == -1 || ship == nullptr) {
        std::cout << "Invalid ship or ID" << std::endl;
        return false;
    }
    for (int cell = 0, r = ship->getStartPos().x, c = ship->getStartPos().y; cell < ship->getSize(); cell++) {
        if (r < 0 || r >= num_rows || c < 0 || c >= num_cols || sea[r][c] != '~') {
            std::cout << "Placement failed for " << ship->getName() << " at (" << r << ", " << c << ")" << std::endl;
            return false;
        }
        adjacent_cell(&r, &c, ship->getDirection());
    }
    for (int cell = 0, r = ship->getStartPos().x, c = ship->getStartPos().y; cell < ship->getSize(); cell++) {
        sea[r][c] = ship->getID();
        adjacent_cell(&r, &c, ship->getDirection());
    }
    if (shipList[pos] != nullptr) {
        delete shipList[pos];
    }
    shipList[pos] = ship;
    std::cout << ship->getName() << " placed successfully." << std::endl;
    return true;
}

void Board::displayBoard(sf::RenderWindow& window, const sf::Sprite& background) const {
    window.draw(background);
    float cellWidth = window.getSize().x / static_cast<float>(num_cols);
    float cellHeight = window.getSize().y / static_cast<float>(num_rows);
    float cellSize = std::min(cellWidth, cellHeight);
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setOutlineThickness(2);
    cell.setOutlineColor(sf::Color::Black);
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            cell.setPosition(displayPos.x + col * cellSize, displayPos.y + row * cellSize);
            if (sea[row][col] == '~') {
                cell.setFillColor(sf::Color::Transparent);
            }
            else if (sea[row][col] == 'H') {
                cell.setFillColor(sf::Color(255, 0, 0, 110));
            }
            else if (sea[row][col] == 'M') {
                cell.setFillColor(sf::Color(255, 255, 255, 110));
            }
            else {
                cell.setFillColor(sf::Color::Green);
            }
            window.draw(cell);
        }
    }
}

bool Board::shootPosition(int row, int col) {
    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) return false;
    if (sea[row][col] == '~') {
        sea[row][col] = 'M';
    }
    else if (sea[row][col] != 'M' && sea[row][col] != 'H') {
        char sunk_ship_code = sea[row][col];
        sea[row][col] = 'H';
        if (checkIfSunk(*shipList[pos_ship(sunk_ship_code)])) {}
    }
    return true;
}

bool Board::checkIfSunk(Ship& ship) const {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            if (sea[row][col] == ship.getID()) return false;
        }
    }
    return true;
}

bool Board::checkIfAllSunk() {
    for (int i = 0; i < 5; i++) {
        if (shipList[i] != nullptr && !checkIfSunk(*shipList[i])) return false;
    }
    return true;
}

Board::~Board() {
    for (int i = 0; i < 5; i++) {
        if (shipList[i] != nullptr) {
            delete shipList[i];
            shipList[i] = nullptr;
        }
    }
}

int Board::pos_ship(char id) {
    switch (id) {
    case 'c': return 0;
    case 'b': return 1;
    case 'r': return 2;
    case 's': return 3;
    case 'd': return 4;
    default:
        std::cout << "Invalid ship ID received: " << id << std::endl;
        return -1;
    }
}

void Board::adjacent_cell(int* r, int* c, int dir) {
    switch (dir) {
    case 1: (*c)--; break;
    case 2: (*c)++; break;
    case 3: (*r)--; break;
    case 4: (*r)++; break;
    }
}

void Board::manualPlaceShip(sf::RenderWindow& window, Ship* ship, float cellSize, Vector2i displayPos, const sf::Sprite& gameplayBackground) {
    bool placing = true;
    sf::Vector2i mousePos;
    int dir = 1;
    while (placing && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                dir = (dir == 1) ? 3 : 1;
                ship->setDirection(dir);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePos = sf::Mouse::getPosition(window);
                int col = (mousePos.x - displayPos.x) / cellSize;
                int row = (mousePos.y - displayPos.y) / cellSize;
                ship->setStartPos(Vector2i(row, col));
                if (placeShip(ship)) {
                    placing = false;
                }
            }
        }
        window.clear();
        displayBoard(window, gameplayBackground);
        highlightCells(window, ship->getSize(), mousePos, dir, cellSize);
        window.display();
    }
}

void Board::highlightCells(sf::RenderWindow& window, int size, sf::Vector2i mousePos, int dir, float cellSize) const {
    int col = (mousePos.x - displayPos.x) / cellSize;
    int row = (mousePos.y - displayPos.y) / cellSize;
    for (int i = 0; i < size; i++) {
        sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
        cell.setPosition(
            displayPos.x + (col + (dir == 2 ? i : (dir == 1 ? -i : 0))) * cellSize,
            displayPos.y + (row + (dir == 4 ? i : (dir == 3 ? -i : 0))) * cellSize
        );
        cell.setFillColor(sf::Color(0, 255, 0, 100));
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::Black);
        window.draw(cell);
    }
}

int Board::get_numOfShots() const {
    int count = 0;
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            if (sea[row][col] == 'H' || sea[row][col] == 'M') {
                ++count;
            }
        }
    }
    return count;
}