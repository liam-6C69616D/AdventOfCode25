import 'dart:io';

typedef Grid<X> = List<List<X>>;

// Read the file to a grid (as spaces are also important in this part)
Future<Grid<String>> read_file() async {
  Grid<String> grid = [];

  List<String> lines = await File('input.txt').readAsLines();

  lines.forEach((line) {
    List<String> row = [];
    line.split('').forEach((char) {
      row.add(char);
    });
    grid.add(row);
  });

  return grid;
}

// Transpose rows and columns (allows us to easily loop columns, and see blanks)
Grid<String> transpose(Grid<String> matrix) {
  int rowCount = matrix.length;
  int colCount = matrix[0].length;

  Grid<String> transposed = List.generate(colCount, (_) => List<String>.filled(rowCount, ""));

  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < colCount; j++) {
      transposed[j][i] = matrix[i][j];
    }
  }

  return transposed;
}

Grid<String> make_new_calcs(Grid<String> grid) {
  List<List<String>> calculations = [];

  List<String> current_calc = [];
  for (int i = 0; i < grid.length; i++) {
    String value = grid[i].join().replaceAll(' ', '');
    if (value != '') {
      current_calc.add(value);
    } else { // If the whole column is spaces, we clear ready for the next calc block
      calculations.add(current_calc);
      current_calc = [];
    }
  }

  calculations.add(current_calc); // Add last calc in (no blank array will follow this one)

  return calculations;
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
  Grid<String> grid = await read_file();
  // Transposing allows each sub array to be the digits of our columns
  Grid<String> new_grid = transpose(grid.sublist(0, grid.length - 1)); // Ignore the operator row as its length differs
  Grid<String> new_calc_values = make_new_calcs(new_grid);
  List<String> operators = grid.sublist(grid.length - 1, grid.length)[0];
  
  operators.removeWhere((item) => item == ' ');
  
  int total = 0;
  for (int i = 0; i < new_calc_values.length; i++) {
    print(new_calc_values[i].map((str) => int.parse(str)).toList());
    print(operators[i]);
    total += single_calc(new_calc_values[i].map((str) => int.parse(str)).toList(), operators[i]);
  }

  print(total);
}