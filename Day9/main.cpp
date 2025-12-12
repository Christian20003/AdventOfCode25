#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <set>
#include <algorithm>

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

    bool operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }
};

struct Line {
    Tile a;
    Tile b;

    Line(Tile a, Tile b) : a(a), b(b) {}
};

struct Area {
    Tile a;
    Tile b;
    int64_t area;

    Area(Tile a, Tile b, int64_t area): a(a), b(b), area(area) {}

    bool operator>(const Area& other) const {
        return area > other.area;
    }

    bool operator==(const Area& other) {
        return a.x == other.a.x && a.y == other.a.y && b.x == other.b.x && b.y == other.b.y;
    }
};

bool isTileInside(vector<Line>& lines, Tile& tile) {
    /* auto hits = 0;
    for (const auto& line : lines) {
        if (line.a.x == line.b.x) {
            auto minY = min(line.a.y, line.b.y);
            auto maxY = max(line.a.y, line.b.y);
            if (tile.y >= minY && tile.y <= maxY) hits++;
        }
        else if (line.a.y == line.b.y) {
            auto minX = min(line.a.x, line.b.x);
            auto maxX = max(line.a.x, line.b.x);
            if (tile.x >= minX && tile.x <= maxX) hits++;
        }

    }
    cout << hits << endl;
    return hits % 2 == 1; */

    auto even_odd = 0;
    for (const auto &line : lines) {
      if (line.a.y == line.b.y) { // horizontal
        if (tile.y != line.a.y)
          continue;
        if (tile.x <= line.a.x)
          continue;
        if (tile.x < line.b.x)
          return true;
        even_odd += 1;
      } else { // vertical
        if (tile.x < line.a.x)
          continue;
        if (tile.y < line.a.y || tile.y > line.b.y)
          continue;
        if (tile.x == line.a.x)
          return true;
        even_odd += 1;
      }
    }
    return even_odd % 2 == 0;
}

bool isLineInside(vector<Line>& lines, Line& line) {
    auto directionX = line.b.x - line.a.x;
    auto directionY = line.b.y - line.a.y;
    // cout << directionY << endl;
    if (directionX != 0) directionX /= abs(directionX);
    if (directionY != 0) directionY /= abs(directionY);

    Tile start = line.a;
    auto result = true;
    while (!(start.x == line.b.x && start.y == line.b.y) && result) {
        result &= isTileInside(lines, start);
        // cout << "X: " << start.x << " Y: " << start.y << " Finish: " << line.b.y << " Direction: " << directionY  << endl;
        start.x += directionX;
        start.y += directionY;
        // sleep(1);
    }
    return result;
}

bool checkCorner(vector<Line>& lines, Tile corner, Tile redTile) {
    auto line = Line(corner, redTile);
    return isLineInside(lines, line);
}

int64_t solveTask2(vector<Tile>& tiles) {
    auto lines = vector<Line>();
    auto areas = vector<Area>();

    for (size_t idx = 0; idx < tiles.size() - 1; idx++) {
        lines.push_back(Line(tiles[idx], tiles[idx+1]));
    }
    lines.push_back(Line(tiles.back(), tiles.front()));

    for (const auto& tile : tiles) {
        for (const auto& otherTile : tiles) {
            if (!(tile == otherTile))
                areas.push_back(Area(tile, otherTile, tile.getArea(otherTile)));
        }
    }
    sort(areas.begin(), areas.end(), greater<>());

    auto idx = 0;
    for (const auto& area : areas) {
        auto corners = area.a.getOtherCorners(area.b);
        auto first = checkCorner(lines, corners.first, area.a) && checkCorner(lines, corners.first, area.b);
        auto second = checkCorner(lines, corners.second, area.a) && checkCorner(lines, corners.second, area.b);
        cout << "Checked: " << idx << endl;
        if (first && second) return area.area;
        idx++;
    }

    return 0;
}

int64_t solveTask1(vector<Tile>& tiles) {
    int64_t result = 0;
    auto test = vector<int64_t>();
    for (const auto& tile : tiles) {
        for (const auto& otherTile : tiles) {
            test.push_back(tile.getArea(otherTile));
            result = max(result, tile.getArea(otherTile));
        }
    }
    sort(test.begin(), test.end(), greater<>());
    auto idx = 0;
    for (auto val : test) {
        if (val == 1543501936)
            cout << idx << endl;
        idx++;
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