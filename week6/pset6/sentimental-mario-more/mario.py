import cs50 as cs50

height = -1
while height < 1 or height > 8:
    height = cs50.get_int("Height: ")
for i in range(height):
    for j in range(height - i - 1):
        print(" ", end="")
    for j in range(height - (height - i - 1)):
        print("#", end="")
    print("  ", end="")
    for j in range(height - (height - i - 1)):
        print("#", end="")
    print()
