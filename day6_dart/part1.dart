import 'dart:io';

Future<List<List<String>>> read_file() async {
  List<List<String>> file_lines = [];

  List<String> lines = await File('input.txt').readAsLines();

  lines.forEach((line) {
    line = line.trim();
    file_lines.add(line.split(RegExp(r'\s+')));
  });

  return file_lines;
}

List<List<dynamic>> transpose(List<List<dynamic>> matrix) {
  int rowCount = matrix.length;
  int colCount = matrix[0].length;

  List<List<dynamic>> transposed = List.generate(colCount, (_) => List<dynamic>.filled(rowCount, null));
  
  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < colCount; j++) {
      transposed[j][i] = matrix[i][j];
    }
  }

  return transposed;
}

int single_calc(List<int> values, String operator) {
  int result = operator == '+' ? 0 : 1; // Need to not start at 0 if we are multiplying

  values.forEach((val) {
    if (operator == '+') result += val;
    else if (operator == '*') result *= val;
  });

  return result;
}

void main() async {
  List<List<String>> file_lines = await read_file();
  List<List<dynamic>> calculations = transpose(file_lines);
  
  int total = 0;

  calculations.forEach((calc) {
    List<int> values = calc.sublist(0, calc.length - 1).map((str) => int.parse(str)).toList();
    String operator = calc.sublist(calc.length - 1, calc.length)[0];
    
    total += single_calc(values, operator);
  });

  print(total);
}