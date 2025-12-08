import fs, { read } from 'fs';
import { fileURLToPath } from 'url';
import { dirname, resolve } from 'path';
import { AsyncLocalStorage } from 'async_hooks';

function read_file_to_grid() : string[][] {

    let grid : string[][] = [];

    const inputFilePath = resolve(dirname(fileURLToPath(import.meta.url)), '..', 'input.txt');
    const input = fs.readFileSync(inputFilePath, 'utf-8');

    input.split('\n').forEach((row, index) => {
        let new_row : string[] = [];

        let characters = row.split('');
        characters.forEach((char, index) => {
            new_row.push(char);
        });

        grid.push(new_row);
    });

    return grid;
}

function trace_beam(grid : string[][]) : [string[][], number]{

    let split_count = 0;

    for (let i = 0; i < grid.length - 1; i++) {
        for (let j = 0; j < grid[i]!.length; j++) {
            if (grid[i]![j] == 'S' || grid[i]![j] == '|') {
                if (grid[i+1]![j] == '^') {
                    grid[i+1]![j-1] = '|';
                    grid[i+1]![j+1] = '|';
                    split_count++;
                } else {
                    grid[i+1]![j] = '|';
                }
            }
        }
    }

    return [grid, split_count];
}


let grid : string[][] = read_file_to_grid();
let [traced_grid, split_count] = trace_beam(grid);

console.log(split_count);