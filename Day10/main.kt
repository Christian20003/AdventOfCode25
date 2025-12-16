import java.io.File
import java.util.Queue
import java.util.LinkedList
import kotlin.collections.mutableListOf
import kotlin.math.max
import kotlin.math.min

const val PATH = "./Day10/Input.txt";

class Machine(public var lights: MutableList<Boolean>, public var buttons: List<List<Int>>, public var joltages: List<Int>) {
    public var joltageState = joltages.map { 0 }.toMutableList()

    public fun getState() : MutableList<Boolean> {
        return lights.map { false }.toMutableList()
    }

    public fun getButton(ignore: List<Int>) : Int {
        var result = -1
        var bestScore = 0
        for (buttonIdx in buttons.indices) {
            if (ignore.contains(buttonIdx)) continue
            var button = buttons[buttonIdx]
            var score = 0
            for (light in button) {
                if (joltageState[light] == joltages[light]) {
                    score = Int.MIN_VALUE
                    break
                }
                score += joltages[light] - joltageState[light]
            }
            if (score > bestScore) {
                bestScore = score
                result = buttonIdx
            }
        }
        return result
    }

    public fun changeJoltageState(buttonIdx: Int) {
        var button = buttons[buttonIdx]
        button.forEach { light ->
            joltageState[light]++ 
        }
    }

    public fun reverseJoltageState(buttonIdx: Int) {
        var button = buttons[buttonIdx]
        button.forEach { light ->
            joltageState[light]--
        }
    }

    public fun compareJoltageState(): Boolean {
        for (idx in joltageState.indices) {
            if (joltageState[idx] != joltages[idx]) return false
        }
        return true
    }

    public fun search(presses: Int) : Int {
        var toIngore = mutableListOf<Int>()
        println("Search: ${presses}")
        while (toIngore.size != buttons.size) {
            var button = getButton(toIngore)
            if (button == -1) return -1
            changeJoltageState(button)
            // println("Button: ${button} - State: ${joltageState[buttons[button][0]]}")
            if (compareJoltageState()) return presses + 1
            var result = search(presses+1)
            if (result == -1) {
                toIngore.add(button)
                reverseJoltageState(button)
            } else {
                return result
            }
        }
        return -1
    }
}

class State(public var state: MutableList<Boolean>, public var presses: Int) {}

fun changeState(state: MutableList<Boolean>, button: List<Int>) {
    button.forEach { light ->
        state.set(light, !state[light])
    }
}

fun compareStates(isState: MutableList<Boolean>, shouldState: MutableList<Boolean>) : Boolean {
    for (idx in isState.indices) {
        if (isState[idx] != shouldState[idx]) return false;
    }
    return true;
}

fun solveTask2(machines: List<Machine>) : Int {
    var result = 0
    var index = 0
    machines.forEach { machine -> 
        println(index)
        result += machine.search(0)
        index++
    }
    return result
}

fun solveTask1(machines: List<Machine>): Int {
    var result = 0;
    machines.forEach { machine -> 
        var queue: Queue<State> = LinkedList()
        var visited = mutableSetOf<List<Boolean>>()
        queue.add(State(machine.getState(), 0))
        while (!queue.isEmpty()) {
            var state = queue.remove()
            if (compareStates(state.state, machine.lights)) {
                result += state.presses
                break
            }
            for (button in machine.buttons) {
                var copy = state.state.toMutableList()
                changeState(copy, button)
                if (visited.add(copy)) {
                    queue.add(State(copy, state.presses + 1))
                }
            }
        }
    }
    return result;
}

fun extractLights(data: String) : MutableList<Boolean> {
    var result = mutableListOf<Boolean>();
    var start = data.indexOf('[')
    var end  = data.indexOf(']')
    data.substring(start+1, end).forEach { char -> 
        if (char == '#') result.add(true)
        else result.add(false)
    }
    return result;
}

fun extractButtons(data: String) : List<List<Int>> {
    var result = mutableListOf<List<Int>>();
    var content = data.substring(data.indexOf(']')+1, data.indexOf('{'))
    var button = mutableListOf<Int>()
    for (char in content) {
        if (char == '(') button = mutableListOf<Int>()
        else if (char == ')') result.add(button)
        else if (char == ',' || char == ' ') continue
        else button.add(char.digitToInt());
    }
    return result;
}

fun extractJoltage(data: String) : List<Int> {
    var result = mutableListOf<Int>()
    var content = data.substring(data.indexOf('{') + 1, data.indexOf('}'))
    var joltages = content.split(',')
    joltages.forEach { joltage -> 
        result.add(joltage.toInt())
    }
    return result
}

fun parseFile() : List<Machine> {
    var result = mutableListOf<Machine>()
    var content = File(PATH).readLines()
    
    content.stream().forEach { line -> 
        var lights = extractLights(line)
        var buttons = extractButtons(line)
        var joltages = extractJoltage(line)
        result.add(Machine(lights, buttons, joltages))
    }

    return result
}

fun main () {
    var data = parseFile()
    var solution1 = solveTask1(data)
    var solution2 = solveTask2(data)

    println("The result of task 1: ${solution1}");
    println("The result of task 2: ${solution2}");
}