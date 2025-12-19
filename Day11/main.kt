package Day11

import java.io.File
import java.util.Queue
import java.util.LinkedList

const val PATH = "./Day11/Input.txt"


public data class Device(public var name: String, public var connections: List<String>) {
    public override fun hashCode() : Int {
        return name.hashCode()
    }
}

public fun bfs(start: String, stop: String, devices: HashSet<Device>) : Long {
    var result: Long = 0
    var first = devices.find { it.name.equals(start) }!!
    var queue: Queue<Device> = LinkedList<Device>(listOf(first))
    while (queue.isNotEmpty()) {
        var device = queue.remove()
        device.connections.forEach { connection -> 
            if (connection.equals(stop)) result++
            else queue.add(devices.find { it.name.equals(connection) })
        }
    }
    return result
}

public fun solveTask2(devices: HashSet<Device>) : Long {
    return (bfs("svr", "dac", devices) * bfs("dac", "fft", devices) * bfs("fft", "out", devices)) + (bfs("svr", "fft", devices) * bfs("fft", "dac", devices) * bfs("dac", "out", devices))
}

public fun solveTask1(devices: HashSet<Device>) : Long {
    return bfs("you", "out", devices)
}

public fun parseFile() : HashSet<Device> {
    var result = hashSetOf<Device>()
    var file = File(PATH)
    file.forEachLine() { device -> 
        var name = device.substring(0, 3)
        var connections = device.substring(5, device.length).split(' ')
        result.add(Device(name, connections))
    }
    return result
}

class Day11(input: List<String>) {

    private val devices: Map<String, List<String>> = input.associate {
        it.substringBefore(":") to it.substringAfter(" ").split(" ")
    }

    fun solvePart1(): Long =
        dfs("you", "out")

    fun solvePart2(): Long =
        (dfs("svr", "dac") * dfs("dac", "fft") * dfs("fft", "out")) +
        (dfs("svr", "fft") * dfs("fft", "dac") * dfs("dac", "out"))

    private fun dfs(
        source: String,
        target: String,
        memory: MutableMap<String, Long> = mutableMapOf()
    ): Long =
        if (source == target) 1L
        else memory.getOrPut(source) {
            devices[source]?.sumOf { next ->
                dfs(next, target, memory)
            } ?: 0
        }
}

public fun main() {
    // var data = parseFile()
    var data = Day11(File(PATH).readLines())
    //var solution1 = solveTask1(data)
    var solution2 = data.solvePart2()//solveTask2(data)
    
    //println("The result of task 1: ${solution1}")
    println("The result of task 2: ${solution2}")
}