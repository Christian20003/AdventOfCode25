import java.io.File

class Range(private var first: Long, private var last: Long) {
    
    public fun solveTask1(): Long {
        var sum: Long = 0;
        for (id in first..last) {
            var str = id.toString()
            if (str.length % 2 != 0) continue
            var firstHalf = str.substring(0, str.length / 2)
            var secondHalf = str.substring(str.length / 2, str.length)
            if (firstHalf.equals(secondHalf)) sum += id
        }
        return sum;
    }

    public fun solveTask2(): Long {
        var sum: Long = 0;
        for (id in first..last) {
            var str = id.toString()
            for (index in 1..(str.length / 2)) {
                var pattern = str.substring(0, index)
                var parts = str.chunked(pattern.length)
                var condition = parts.all{it.equals(pattern)}
                if (condition) {
                    sum += id
                    break
                }
            }
        }
        return sum;
    }
}

fun parseInput(): List<Range> {
    var text = File("./Day2/Input.txt").readText(Charsets.UTF_8)
    var data = text.split(",")
    var ranges = mutableListOf<Range>()

    for (range in data) {
        var ids = range.split("-")
        ranges.add(Range(ids[0].toLong(), ids[1].toLong()))
    }
    return ranges;
}

fun main () {
    var data = parseInput()
    var task1: Long = 0
    var task2: Long = 0

    for (range in data) {
        task1 += range.solveTask1()
        task2 += range.solveTask2()
    }

    println("The result of task 1 is ${task1}")
    println("The result of task 2 is ${task2}")
}