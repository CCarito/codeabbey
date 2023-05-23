def sliding_window_search(text, positions):
    result = []
    window_size = 4096
    max_length = 15

    for pos in positions:
        current_substring = text[pos:pos+max_length+1]
        search_window = text[max(0, pos-window_size):pos]
        match_length = 0
        match_offset = 0

        for i in range(len(search_window)-max_length+1):
            if search_window[i:i+max_length+1] == current_substring:
                match_length = len(current_substring)
                match_offset = pos - (len(search_window)-i)
                break

        result.append("{:03X}{:04X}".format(match_offset, match_length))

    return ' '.join(result)


# Read the input file
with open('doyle.txt', 'r') as file:
    text = file.read()

# Parse the input
num_testcases = int(input())
positions = list(map(int, input().split()))

# Perform sliding window search
output = sliding_window_search(text, positions)
print(output)
