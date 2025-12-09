import * as fs from 'fs';

function solveTask2(data: string[]) : number {
    let startIdx = data[0].indexOf('S');
    let result = new Map<number, number>();
    result.set(startIdx, 1);

    for (let line of data) {
        if (line.includes('S')) continue;
        let newMap = new Map<number, number>();
        result.forEach((occurence, position) => {
            if (line[position] === '^') {
                if (position > 0) {
                    let newPosition = position - 1;
                    let value = newMap.get(newPosition);
                    if (value !== undefined) newMap.set(newPosition, value + occurence);
                    else newMap.set(newPosition, occurence);
                }
                if (position < line.length) {
                    let newPosition = position + 1;
                    let value = newMap.get(newPosition);
                    if (value !== undefined) newMap.set(newPosition, value + occurence);
                    else newMap.set(newPosition, occurence);
                }
            } else {
                let value = newMap.get(position);
                if (value !== undefined) newMap.set(position, value + occurence);
                else newMap.set(position, occurence);
            }
        });
        result = newMap;
    }

    let timelines = 0;
    result.forEach((occurence, position) => {
        timelines += occurence;
    });

    return timelines;
}

function solveTask1(data: string[]) : number {
    let result = 0;
    let startIdx = data[0].indexOf('S');
    let beams = new Set<number>();
    beams.add(startIdx);

    for (let line of data) {
        if (line.includes('S')) continue;
        let newBeams = new Set<number>();
        beams.forEach((position) => {
            if (line[position] === '^') {
                if (position > 0) newBeams.add(position-1);
                if (position < line.length) newBeams.add(position+1);
                result++;
            } else {
                newBeams.add(position);
            }
        });
        beams = newBeams;
    }

    return result;
}

function readFile() : string[] {
    let content = fs.readFileSync('./Input.txt', 'utf-8');
    return content.split('\n');
}

function main() {
    let content = readFile();
    let solution1 = solveTask1(content);
    let solution2 = solveTask2(content);

    console.log(`The result of task 1: ${solution1}`);
    console.log(`The result of task 2: ${solution2}`);    
}

main();