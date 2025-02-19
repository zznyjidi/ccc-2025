input_list = input().split()
shape1_base, shape1_height, shape2_base, shape2_height = map(int, input_list)

horizontal_perimeter = shape1_base + shape2_base + max(shape1_height, shape2_height)
vertical_perimeter = max(shape1_base, shape2_base) + shape1_height + shape2_height

print(min(horizontal_perimeter, vertical_perimeter) * 2)
