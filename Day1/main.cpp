#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Dial {
    int value = 50;
    int max = 99;
    int password = 0;
};

void rotateTask1(string& value, Dial& dial) {
    int number = stoi(value.substr(1, value.length() - 1)) % (dial.max+1);
    char direction = value[0];
    if (direction == 'R') dial.value = (dial.value + number) % (dial.max + 1);
    if (direction == 'L') dial.value -= number;
    if (dial.value < 0) dial.value = (dial.max + 1) + dial.value;
    if (dial.value == 0) dial.password++;
}

void rotateTask2(string& value, Dial& dial) {
        int number = stoi(value.substr(1, value.length() - 1));
        dial.password += number / (dial.max + 1);
        number = number % (dial.max + 1);
        char direction = value[0];
        if (direction == 'R') dial.value += number;
        if (direction == 'L') dial.value -= number;
        if (dial.value > dial.max) {
            dial.value = dial.value % (dial.max + 1);
            if (dial.value != 0) dial.password++;
        }
        if (dial.value < 0) {
            dial.value = (dial.max + 1) + dial.value;
            if (dial.value != 0 && (dial.value + number) != (dial.max + 1)) dial.password++;
        }
        
        if (dial.value == 0) dial.password++;
    }

Dial parseFile(void(*rotate)(string&, Dial&)) {
    ifstream stream("./Day1/Input.txt");
    if (stream.fail()) {
        cout << "File not found" << endl;
    }
    Dial dial;
    if (stream.is_open()) {
        string line;
        while (getline(stream, line)) {
            rotate(line, dial);
        }
        stream.close();
    }
    return dial;
}

int main() {
    Dial result1 = parseFile(&rotateTask1);
    Dial result2 = parseFile(&rotateTask2);
    cout << "Password of Task 1: " << to_string(result1.password) << endl; 
    cout << "Password of Task 2: " << to_string(result2.password) << endl;
    return 0;
}