import cs50 as cs50


def getCoins(change, coinValue):
    coins = 0
    while change - coinValue >= 0:
        change -= coinValue
        coins += 1
    return round(change, 2), coins


change = -1
while change < 0:
    change = cs50.get_float("Change owed: ")

change, quarters = getCoins(change, 0.25)
change, dimes = getCoins(change, 0.1)
change, nickels = getCoins(change, 0.05)
change, pennies = getCoins(change, 0.01)

print(quarters + dimes + nickels + pennies)
