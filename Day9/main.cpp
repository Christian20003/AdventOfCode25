#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string FILE_NAME = "./Day9/Input.txt";

struct Tile {
    int64_t x;
    int64_t y;

    Tile(int x, int y) : x(x), y(y) {}

    int64_t getArea(const Tile& other) const {
        return (max(x, other.x) - min(x, other.x) + 1) * (max(y, other.y) - min(y, other.y) + 1);
    }

    pair<Tile, Tile> getOtherCorners(const Tile& other) const {  
        return make_pair(Tile(x, other.y), Tile(other.x, y));
    }
};

struct Line {
    Tile a;
    Tile b;

    Line(Tile a, Tile b) : a(a), b(b) {}
};

/* bool isInsideArea(vector<Tile>& tiles, Tile& tile) {
    auto leftUp = false;
    auto leftDown = false;
    auto rightUp = false;
    auto rightDown = false;

    for (const auto& position : tiles) {
        if (position.x == tile.x && position.y == tile.y) return true;
        if (position.x < tile.x && position.y < tile.y) leftUp = true;
        else if (position.x > tile.x && position.y < tile.y) rightUp = true;
        else if (position.x > tile.x && position.y > tile.y) rightDown = true;
        else if (position.x < tile.x && position.y > tile.y) leftDown = true;
    }

    return leftUp && leftDown && rightUp && rightDown;
} */

int64_t solveTask2(vector<Tile>& tiles) {
    int64_t result = 0;
    /* auto lines = vector<Line>();

    for (size_t idx = 0; idx < tiles.size() - 1; idx++) {
        lines.push_back(Line(tiles[idx], tiles[idx+1]));
    }
    lines.push_back(Line(tiles.back(), tiles.front()));

    for (const auto& tile : tiles) {
        for (const auto& otherTile : tiles) {
            auto area = max(result, tile.getArea(otherTile));
            if (area == result) continue;
            auto corners = tile.getOtherCorners(otherTile);
            if (isInsideArea(tiles, corners.first) && isInsideArea(tiles, corners.second)) {
                cout << area << endl;
                result = area;
            }
        }
    } */
    return result;
}

int64_t solveTask1(vector<Tile>& tiles) {
    int64_t result = 0;
    for (const auto& tile : tiles) {
        for (const auto& otherTile : tiles) {
            result = max(result, tile.getArea(otherTile));
        }
    }
    return result;
}

void parseFile(vector<Tile>& tiles) {
    auto stream = ifstream(FILE_NAME);
    if (stream.fail()) cerr << "File not found" << endl;

    while (stream.is_open()) {
        string line;
        while (getline(stream, line)) {
            auto index = line.find(",");
            auto x = stol(line.substr(0, index));
            auto y = stol(line.substr(index+1, line.size() - index + 1));
            tiles.push_back(Tile(x, y));
        }
        stream.close();
    }
}

int main() {
    auto data = vector<Tile>();
    parseFile(data);
    auto solution1 = solveTask1(data);
    auto solution2 = solveTask2(data);

    cout << "Result of task 1: " << solution1 << endl;
    cout << "Result of task 2: " << solution2 << endl;

    return 0;
}