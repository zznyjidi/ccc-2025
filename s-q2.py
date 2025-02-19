input_str = input()
target_index = int(input())

char_list = []
len_list = []
current_index = -1

for i in range(len(input_str)):
    current_char = input_str[i]
    try:
        int(current_char)
        try:
            len_list[current_index] += current_char
        except IndexError:
            len_list.append(current_char)
    except ValueError:
        char_list.append(current_char)
        current_index += 1

len_list = list(map(int, len_list))
pattern_len = sum(len_list)

left_index = target_index % pattern_len
for i in range(len(len_list)):
    if left_index - len_list[i] < 0:
        print(char_list[i])
        break
    else:
        left_index -= len_list[i]
