package Day6;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Problem {

    private List<Long> values;
    private String operator;

    public Problem() {
        values = new ArrayList<>();
        operator = "+";
    }
   
    public void addValue(long value) {
        values.add(value);
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }

    public long solveTasks() {
        boolean isAdd = operator.equals("+");
        long result = isAdd ? 0 : 1;
        for (long value : this.values) {
            if (isAdd) {
                result += value;
            } else {
                result *= value;
            }
        }
        return result;
    }
    
}

class Main {

    public static List<Problem> encodeTask2(List<String> fileData) {
        List<Problem> result = new ArrayList<>();
        Problem problem = new Problem();
        String operator = "";

        for (int index = 0; index < fileData.get(0).length(); index++) {
            boolean isComplete = true;
            String number = "";
            for (String line : fileData) {
                char value = index < line.length() ? line.charAt(index) : '\s';
                if (line.contains("+")) {
                    if (value != '\s') operator = Character.toString(value);
                    continue;
                }
                if (value == '\s') continue;
                number += value;
                isComplete = index+1 == line.length();
            }
            if (isComplete) {
                if (!number.equals("")) problem.addValue(Long.parseLong(number));
                problem.setOperator(operator);
                result.add(problem);
                problem = new Problem();
            } else {
                problem.addValue(Long.parseLong(number));
            }
        }

        return result;
    }

    public static List<Problem> encodeTask1(List<String> fileData) {
        List<Problem> result = new ArrayList<>();
        for (String data : fileData) {
            String[] input = data.trim().split("\\s+");
            for (int index = 0; index < input.length; index++) {
                    String value = input[index];
                    if (value.equals("+") || value.equals("*")) {
                        result.get(index).setOperator(value);
                    } else {
                        if (result.size() != input.length) {
                            Problem problem = new Problem();
                            problem.addValue(Long.parseLong(input[index]));
                            result.add(problem);
                        } else {
                            result.get(index).addValue(Long.parseLong(input[index]));
                        }
                    }

                }
        }
        return result;
    }

    public static List<String> parseFile() {
        File input = new File("./Day6/Input.txt");
        List<String> data = new ArrayList<>();

        try(Scanner scanner = new Scanner(input)) {
            while (scanner.hasNext()) {              
                data.add(scanner.nextLine());
            }
        } catch (FileNotFoundException exception) {
            System.out.println("Input file not found");
        }
        return data;
    }
    
    public static void main() {
        List<String> data = parseFile();
        List<Problem> problems1 = encodeTask1(data);
        List<Problem> problems2 = encodeTask2(data);

        long solution1 = problems1.stream().map(problem -> problem.solveTasks()).reduce((long) 0, Long::sum);
        long solution2 = problems2.stream().map(problem -> problem.solveTasks()).reduce((long) 0, Long::sum);
        
        System.out.println(String.format("Result of task 1: %d", solution1));
        System.out.println(String.format("Result of task 2: %d", solution2));
    }
}