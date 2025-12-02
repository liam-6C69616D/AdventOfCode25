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

def split_string_variably(input)
  results = []

  (1..input.length/2).each do |length|
    substrings = input.chars.each_slice(length).map(&:join) # Split to characters, then group into x elements, and join
    results.append(substrings)
  end

  results
end

def is_invalid(value)
  split_options = split_string_variably(value.to_s)
  p value, split_options
  split_options.each do |split|
    first = split[0]
    if split.all? {|elem| elem == first}
      return true
    end
  end

  return false
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