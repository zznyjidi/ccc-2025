pen_count, color_count, change_count = map(int, input().split())

pen_list = []
for i in range(pen_count):
    pen_list.append(list(map(int, input().split())))

change_list = []
for i in range(change_count):
    change_list.append(list(map(int, input().split())))

for i in range(change_count + 1):
    # Apply Changes
    if i != 0:
        pen_list[change_list[i - 1][1] - 1][change_list[i - 1][0] - 1] = change_list[i - 1][2]
    
    # Calculate Max Pretty for each Color
    color_max_list = [[index + 1, 0] for index in range(color_count)]
    for pen in pen_list:
        if pen[1] > color_max_list[pen[0] - 1][1]:
            color_max_list[pen[0] - 1] = pen
    
    # Apply Color change
    max_unused_pen = []
    pen_list_sorted = pen_list.copy()
    list.sort(pen_list_sorted, key=lambda x: x[1], reverse=True)
    for pen in pen_list_sorted:
        for max_pen in color_max_list:
            if pen is max_pen:
                break
        else:
            max_unused_pen = pen
            break
    list.sort(color_max_list, key=lambda x: x[1])
    if max_unused_pen:
        if color_max_list[0][1] < max_unused_pen[1]:
            color_max_list[0] = max_unused_pen
    
    # Calculate Max Pen Sum
    print(sum(map(lambda x: x[1], color_max_list)))
