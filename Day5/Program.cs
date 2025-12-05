using System.Net.Sockets;

class MainClass
{

    class Range(long start, long end)
    {
        public long Start { get; set; } = start;
        public long End { get; set; } = end;
    }

    static int SolveTask1(List<Range> freshIngredients, List<long> ingredients)
    {
        var result = ingredients.Where(ingre =>
        {
            return freshIngredients.Any(range => range.Start <= ingre && ingre <= range.End);
        });
        return result.Count();
    }

    static long SolveTask2(List<Range> freshIngredients)
    {
        var visited = new List<Range>();

        foreach(var elem in freshIngredients.OrderBy(elem => elem.Start))
        {
            var change = true;
            while (change)
            {
                var existStart = visited.FirstOrDefault(range => elem.Start >= range.Start && elem.Start <= range.End);
                var existEnd = visited.FirstOrDefault(range => elem.End >= range.Start && elem.End <= range.End);

                if (existStart is not null)
                    elem.Start = existStart.End + 1;
                if (existEnd is not null)
                    elem.End = existEnd.Start - 1;
                if (existStart is null && existEnd is null)
                    change = false;

            }
            if (elem.Start <= elem.End)
                visited.Add(elem);
        }

        return visited.Aggregate<Range, long>(0, (sum, range) => sum += range.End - range.Start + 1);
    }

    static (List<Range>, List<long>) ParseInput()
    {
        using StreamReader reader = new("/home/proglin/Daten/Programmieren/AdventOfCode/2025/Day5/Input.txt");
        var freshIngredients = new List<Range>();
        var ingredients = new List<long>();
        var parseStock = false;

        while (!reader.EndOfStream)
        {
            var line = reader.ReadLine();
            if (string.IsNullOrEmpty(line))
            {
                parseStock = true;
                continue;
            }

            line = line!.Replace("\n", "");
            if (parseStock)
            {
                ingredients.Add(long.Parse(line));
            }
            else
            {
                var range = line.Split("-");
                var value = new Range(long.Parse(range[0]), long.Parse(range[1]));
                freshIngredients.Add(value);
            }
        }
        return (freshIngredients, ingredients);
    }

    static void Main()
    {
        var (freshIngredients, ingredients) = ParseInput();
        var solution1 = SolveTask1(freshIngredients, ingredients);
        var solution2 = SolveTask2(freshIngredients);

        Console.WriteLine($"Result of task 1: {solution1}");
        Console.WriteLine($"Result of task 2: {solution2}");
    }
}