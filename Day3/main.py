from typing import List

class Bank:

    def __init__(self, bank: str) -> None:
        self.batteries = bank
        self.batteries = self.batteries.replace("\n", "")

    def solveTask1(self) -> int:
        combinations = []
        for firstIdx, first in enumerate(self.batteries):
            for secondIdx, second in enumerate(self.batteries):
                if secondIdx <= firstIdx:
                    continue
                combinations.append(first + second)
        return max([int(joltage) for joltage in combinations])
    
    def solveTask2(self) -> int:
        result = ""
        digits = 12
        for digit in range(digits):
            ignore = (-1) * (digits - digit - 1)
            ignore = ignore if ignore != 0 else len(self.batteries)
            batteries = [int(batterie) for batterie in self.batteries[:ignore]]
            value = max(batteries)
            valueIdx = batteries.index(value)
            result += str(value)
            self.batteries = self.batteries[(valueIdx+1):]
        return int(result)

def parseFile() -> List[Bank]:
    with open("./Day3/Input.txt", "r") as file:
        result = [Bank(bank) for bank in file.readlines()]
        return result

def main():
    banks = parseFile()
    task1 = sum([bank.solveTask1() for bank in banks])
    task2 = sum([bank.solveTask2() for bank in banks])

    print(f'The result of task1: {task1}')
    print(f'The result of task2: {task2}')

if __name__ == "__main__":
    main()