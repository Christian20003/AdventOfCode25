from typing import List, Tuple, Set
from functools import reduce
import math

PATH = './Day8/Input.txt'
LIMIT = 1000

class Distance:
    def __init__(self, a: Tuple[int, int, int], b: Tuple[int, int, int], distance: float):
        self.a = a
        self.b = b
        self.distance = distance

def getDistances(data: List[Tuple[int, int, int]]) -> List[Distance]:
    result = []
    seen = set()
    for (x1,y1,z1) in data:
        for (x2,y2,z2) in data:
            distance = math.sqrt((x1-x2)**2 + (y1-y2)**2 + (z1-z2)**2)
            if distance == 0: continue
            if ((x2,y2,z2),(x1,y1,z1)) in seen: continue
            result.append(Distance((x1,y1,z1), (x2,y2,z2), distance))
            seen.add(((x1,y1,z1),(x2,y2,z2)))
    result.sort(key=lambda x: x.distance)
    return result

def mergeComponents(distance: Distance, components: List[Set]) -> List[Set]:
    componenta = None
    componentb = None
    for component in components:
        if componenta is not None and componentb is not None: break
        if distance.a in component:
            componenta = component
        if distance.b in component:
            componentb = component
    if componenta is None and componentb is None:
        components.append({distance.a, distance.b})
    elif componenta is not None and componentb is None:
        componenta.add(distance.b)
    elif componenta is None and componentb is not None:
        componentb.add(distance.a)
    elif componenta != componentb:
        components.remove(componentb)
        componenta.update(componentb)
    return components

def getComponentSizes(components: List[Set]) -> int:
    components.sort(key=lambda x: x.__len__(), reverse=True)
    return reduce(lambda x,y: x*y,(len(component) for component in components[0:3]))

def solveTasks(data: List[Tuple[int, int, int]]) -> Tuple[int, int]:
    distances = getDistances(data)
    components: List[Set] = []
    task1 = 0
    task2 = 0
    for idx, distance in enumerate(distances):
        if idx == LIMIT:
            task1 = getComponentSizes(components)
        components = mergeComponents(distance, components)
        if len(components[0]) == len(data):
            task2 = distance.a[0] * distance.b[0]
            break
    return task1, task2

def parseFile() -> List[Tuple[int, int, int]]:
    with open(PATH, 'r') as file:
        result = []
        content = file.readlines()
        values = [line.split(',') for line in content]
        for line in values:
            result.append((int(line[0]), int(line[1]), int(line[2])))
        return result

def main():
    data = parseFile()
    (solution1, solution2) = solveTasks(data)

    print(f'Result of task 1: {solution1}')
    print(f'Result of task 2: {solution2}')

if __name__ == "__main__":
    main()