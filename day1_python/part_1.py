import re

def read_file_to_lines(path: str) -> list[str]:
    with open(path, "r") as file:
        return file.read().splitlines()
    
def parse_move(move: str) -> list[bool, int]:
    match = re.match("([LR])([0-9]+)", move)
    clockwise = True if match[1] == "R" else False
    
    return [clockwise, int(match[2])]
    
def next_position(current_pos: int, rotate_by: int, clockwise: bool) -> int:
    if clockwise:
        return (current_pos + rotate_by) % 100
    else:
        return (current_pos - rotate_by) % 100
    
if __name__ == "__main__":
    moves = read_file_to_lines("input.txt")
    position = 50
    zero_count = 0

    for move in moves:
        parts = parse_move(move)
        position = next_position(position, parts[1], parts[0])
        if position == 0:
            zero_count += 1

    print(zero_count)