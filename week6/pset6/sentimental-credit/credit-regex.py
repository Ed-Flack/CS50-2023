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
    card = "INVALID"
    if re.match(r"^3[47]\d{13}$", cardNumber):
        card = "AMEX"
    if re.match(r"^5[1-5]\d{14}$", cardNumber):
        card = "MASTERCARD"
    if re.match(r"^4\d{12}(\d{3})?$", cardNumber):
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
