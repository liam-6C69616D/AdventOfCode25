import part_1

def zero_passes(current_pos: int, rotate_by: int, clockwise: bool):
    passes = 0
    if clockwise:
        while rotate_by > 0:
            current_pos += 1
            rotate_by -= 1
            if current_pos % 100 == 0:
                passes += 1
    else:
        while rotate_by > 0:
            current_pos -= 1
            rotate_by -= 1
            if current_pos % 100 == 0:
                passes += 1

    return passes

if __name__ == "__main__":
    moves = part_1.read_file_to_lines("./input.txt")
    position = 50
    zero_count = 0

    for move in moves:
        parts = part_1.parse_move(move)
        zero_count += zero_passes(position, parts[1], parts[0])
        position = part_1.next_position(position, parts[1], parts[0])

    print(zero_count)