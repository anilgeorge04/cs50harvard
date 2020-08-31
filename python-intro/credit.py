# This software validates a credit card number entered by the user
# Validity checks: Format, Luhn's checksum algorithm*, Number of digits, Starting digit(s) with RegEx
# Output: It reports whether the card is Amex, Mastercard, Visa or Invalid
# *Luhn's checksum algorithm: https:#en.wikipedia.org/wiki/Luhn_algorithm
import re


def main():
    card_type = {
        1: "AMEX",
        2: "MASTERCARD",
        3: "VISA",
        4: "INVALID"
    }
    # Get credit card number
    cardnum = input("Number: ")

    # check card length
    if len(cardnum) == 13 or len(cardnum) == 15 or len(cardnum) == 16:
        key = checkcard(cardnum)
    else:
        key = 4
    print(card_type[key])


def checkcard(cardnum):
    # check card meet Luhn's algorithm specs
    # if yes, RegEx check on first digits of card
    if luhn(int(cardnum)):
        # AMEX starts with 34 or 37
        if re.search("^3(4|7)*", cardnum):
            return 1
        # MASTERCARD starts with 51-55
        elif re.search("^5[1-5]*", cardnum):
            return 2
        # VISA starts with 4
        elif re.search("^4+", cardnum):
            return 3
        else:
            return 4
    else:
        return 4


def luhn(cardnum):
    last_digit, sum_odd, sum_prod_even, pos = 0, 0, 0, 1
    num = cardnum

    while num > 0:
        last_digit = num % 10
        # alternate numbers from right
        if not pos % 2 == 0:
            sum_odd += last_digit
        # alternate numbers second from right
        else:
            sum_prod_even += (last_digit * 2) % 10
            if last_digit * 2 >= 10:
                # max number in 10s place can only be 1 (9*2=18)
                sum_prod_even += 1

        # remove last digit
        num = (num - last_digit) / 10
        pos += 1

    # Luhn's algorithm check
    if (sum_prod_even + sum_odd) % 10 == 0:
        return True
    else:
        # print("Failed Luhn Algorithm check")
        return False


main()
