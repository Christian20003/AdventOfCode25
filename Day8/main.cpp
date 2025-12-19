#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class JunctionBox {
    public:
    int x;
    int y;
    int z;

    JunctionBox() : x(0), y(0), z(0) {}

    JunctionBox(int x, int y, int z) : x(x), y(y), z(z) {}

    double distance(JunctionBox& other) {
        return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2));
    }

    bool operator==(const JunctionBox& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    string toString() const {
        return "" + to_string(x) + "," + to_string(y) + "," + to_string(z);
    }
};

class Distance {
    public:
    JunctionBox a;
    JunctionBox b;
    double distance;

    Distance(JunctionBox& a, JunctionBox& b, double distance) {
        this->a = a;
        this->b = b;
        this->distance = distance;
    }

    bool operator==(const Distance& other) {
        return 
            ((this->a == other.a && this->b == other.b) ||
            (this->a == other.b && this->b == other.a)) &&
            this->distance == other.distance;
    }

    bool operator<(const Distance& other) const {
        return this->distance < other.distance;
    }
};

class Circuit {
    public:
    vector<JunctionBox> boxes;

    Circuit() {
        this->boxes = vector<JunctionBox>();
    }
    
    Circuit(vector<JunctionBox> boxes) {
        this->boxes = boxes;
    }

    void addBox(JunctionBox box) {
        this->boxes.push_back(box);
    }

    void addBoxes(vector<JunctionBox>& boxes) {
        for (const auto& box : boxes) {
            this->boxes.push_back(box);
        }
    }

    bool containsBox(const JunctionBox& box) const {
        auto result = find(boxes.begin(), boxes.end(), box);
        return result != boxes.end();
    }

    bool isFilled() {
        return boxes.size() != 0;
    }

    bool operator<(const Circuit& other) const {
        return this->boxes.size() < other.boxes.size();
    }

    bool operator>(const Circuit& other) const {
        return this->boxes.size() > other.boxes.size();
    }
};

void getDistances(vector<JunctionBox>& boxes, set<Distance>& distances) {
    for (auto& box : boxes) {
        for (auto& otherBox : boxes) {
            if (box == otherBox) continue;
            auto newDistance = box.distance(otherBox);
            distances.insert(Distance(box, otherBox, newDistance));
        }
    }
}

vector<Circuit>::iterator getCircuit(vector<Circuit>& circuits, const JunctionBox& box) {
    for (auto circuit = circuits.begin(); circuit != circuits.end(); circuit++) {
        if (circuit->containsBox(box)) return circuit;
    }
    return circuits.end();
}

int solveTask1(vector<JunctionBox>& boxes, int connections) {
    auto distances = set<Distance>();
    auto circuits = vector<Circuit>();
    getDistances(boxes, distances);
    
    auto idx = 1;
    for (const auto& dist : distances) {
        cout << dist.distance << " A: " << dist.a.toString() << " B: " << dist.b.toString() << endl;
        if (idx == connections) break;
        auto circuitA = getCircuit(circuits, dist.a);
        auto circuitB = getCircuit(circuits, dist.b);

        if (circuitA == circuits.end() && circuitB == circuits.end()) {
            Circuit newCircuit;
            newCircuit.addBox(dist.a);
            newCircuit.addBox(dist.b);
            circuits.push_back(newCircuit);
        }
        else if (circuitA == circuitB) continue;
        else if (circuitA == circuits.end()) circuitB->addBox(dist.a);
        else if (circuitB == circuits.end()) circuitA->addBox(dist.b);
        else { 
            circuitA->addBoxes(circuitB->boxes);
            circuits.erase(circuitB);
        }
        idx++;
    }
    
    sort(circuits.begin(), circuits.end(), greater<>());
    
    auto result = 1;
    idx = 0;
    for (auto elem = circuits.begin(); elem != circuits.end(); elem++) {
        if (idx == 3) break;
        result *= elem->boxes.size();
        cout << "Size: " << elem->boxes.size() << endl;
        idx++;
    }

    return result;
}

void parseFile(vector<JunctionBox>& boxes) {
    ifstream stream("./Day8/Input.txt");
    if (stream.fail()) {
        cout << "File not found" << endl;
    }
    if (stream.is_open()) {
        string line;
        while (getline(stream, line)) {
            auto pos = line.find(",");
            auto coord = vector<int>();
            while (pos != string::npos) {
                coord.push_back(stoi(line.substr(0, pos)));
                line.erase(0, pos + 1);
                pos = line.find(",");
            }
            JunctionBox box(coord[0], coord[1], stoi(line));
            boxes.push_back(box);
        }
        stream.close();
    }
}

int main() {
    vector<JunctionBox> boxes;
    parseFile(boxes);
    auto solution1 = solveTask1(boxes, 1000);

    cout << "Result of task 1: " << solution1 << endl;
    return 0;
}