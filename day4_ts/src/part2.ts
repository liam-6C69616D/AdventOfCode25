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

function is_accessible(grid : string[][], row : number, col : number) : boolean {

    let surround_count = 0;

    for (let i = -1; i <= 1; i++) {
        for (let j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            let row_check = row + i;
            let col_check = col + j;

            if (row_check < 0 || row_check > grid.length - 1 || col_check < 0 || col_check > grid[0]!.length - 1) {
                continue;
            }

            if (grid[row_check]![col_check] === '@') {
                surround_count++;
            }
        }
    }

    return surround_count < 4;
}

function find_removals(grid : string[][]) : number[][] {
    let removals : number[][] = [];

    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[i]!.length; j++) {
            if (grid[i]![j] === '@' && is_accessible(grid, i, j)) {
                removals.push([i, j]);
            }
        }
    }

    return removals;
}

function remove_items_in_place(grid : string[][], removals : number[][]) : void {
    removals.forEach((rem) => {
        grid[rem[0]!]![rem[1]!] = 'x';
    });
}

let grid : string[][] = read_file_to_grid();

let num_removed = 0

while (true) {
    let to_remove = find_removals(grid);
    num_removed += to_remove.length;

    if (to_remove.length == 0) {
        break;
    }

    remove_items_in_place(grid, to_remove);
}

console.log(num_removed);