import cs50
import re


def everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(cardNumber):
    total = 0
    for i in range(len(cardNumber) - 2, -1, -2):
        number = str(int(cardNumber[i]) * 2)
        if len(number) > 1:
            for j in range(len(number)):
                total += int(number[j])
        else:
            total += int(number)
    return total


def allOtherDigitsAddedTogether(cardNumber):
    total = 0
    for i in range(len(cardNumber) - 1, -1, -2):
        total += int(cardNumber[i])
    return total


def findCardType(cardNumber):
    firstNumber = int(cardNumber[0])
    secondNumber = int(cardNumber[1])
    card = "INVALID"
    if firstNumber == 3:
        if secondNumber == 4 or secondNumber == 7:
            card = "AMEX"
    elif firstNumber == 5:
        if secondNumber >= 1 and secondNumber <= 5:
            card = "MASTERCARD"
    elif firstNumber == 4:
        card = "VISA"
    return card


def checksum(cardNumber):
    if not re.match(r"^(?:\d{13}|\d{15}|\d{16})$", cardNumber):
        return "INVALID"

    total = everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(
        cardNumber
    )
    total2 = allOtherDigitsAddedTogether(cardNumber)
    sum = total + total2

    if sum % 10 != 0:
        return "INVALID"

    return findCardType(cardNumber)


def main():
    cardNumber = ""
    while not cardNumber.isnumeric():
        cardNumber = cs50.get_string("Number: ")
    print(checksum(cardNumber))


if __name__ == "__main__":
    main()
