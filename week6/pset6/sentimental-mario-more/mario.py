# TODO
height = ""
while not height.isnumeric() or int(height) < 1 or int(height) > 8:
    height = input("Height: ")
height = int(height)
for i in range(height):
    for j in range(height - i - 1):
        print(" ", end="")
    for j in range(height - (height - i - 1)):
        print("#", end="")
    print("  ", end="")
    for j in range(height - (height - i - 1)):
        print("#", end="")
    print()
