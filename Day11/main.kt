package Day11

import java.io.File
import java.util.Queue
import java.util.LinkedList

const val PATH = "./Day11/Input.txt"

public fun dfs(start: String, stop: String, devices: HashMap<String, List<String>>, memory: HashMap<String, Long> = hashMapOf()) : Long {
    if (start == stop) return 1L
    if (memory.containsKey(start)) return memory[start]!!
    var result: Long = 0
    devices[start]?.forEach {next ->
        var paths = dfs(next, stop, devices, memory)
        memory[next] = paths
        result += paths
    }
    return result
}

public fun solveTask2(devices: HashMap<String, List<String>>) : Long {
    return (dfs("svr", "dac", devices) * dfs("dac", "fft", devices) * dfs("fft", "out", devices)) + (dfs("svr", "fft", devices) * dfs("fft", "dac", devices) * dfs("dac", "out", devices))
}

public fun solveTask1(devices: HashMap<String, List<String>>) : Long {
    return dfs("you", "out", devices)
}

public fun parseFile() : HashMap<String, List<String>> {
    var result = hashMapOf<String, List<String>>()
    var file = File(PATH)
    file.forEachLine() { device -> 
        var name = device.substring(0, 3)
        var connections = device.substring(5, device.length).split(' ')
        result.put(name, connections)
    }
    return result
}

public fun main() {
    var data = parseFile()
    var solution1 = solveTask1(data)
    var solution2 = solveTask2(data)
    
    println("The result of task 1: ${solution1}")
    println("The result of task 2: ${solution2}")
}