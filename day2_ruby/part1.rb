def read_file
  split = []
  File.foreach('input.txt') do |line|
    range = line.split(",")
    range.each do |r|
      range_values = r.split("-")
      split.append([range_values[0], range_values[1]])
    end
  end

  split
end

def is_invalid(value)
  stringified = value.to_s
  len = stringified.length

  stringified[0...len/2] == stringified[len/2..-1]
end

def check_range(r_start, r_end)
  invalid = []
  range = (r_start..r_end).to_a
  range.each do |value|
    if is_invalid(value)
      invalid.append(value)
    end
  end

  invalid
end

def main
  ranges = read_file

  running_total = 0
  ranges.each do |s, e|
    invalid_ids = check_range(s, e)
    invalid_ids.each { |id| running_total += id.to_i}
  end

  puts running_total
end

main