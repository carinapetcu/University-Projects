import math
from entities.entities import Number


class ServiceNumber:
    def __init__(self, validateNumber):
        self.__validateNumber = validateNumber

    @staticmethod
    def convert_to_decimal_digit(digit):
        listOfDigits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
        if digit in listOfDigits:
            digit = int(digit)
        elif digit.lower() == 'a':
            digit = 10
        elif digit.lower() == 'b':
            digit = 11
        elif digit.lower() == 'c':
            digit = 12
        elif digit.lower() == 'd':
            digit = 13
        elif digit.lower() == 'e':
            digit = 14
        elif digit.lower() == 'f':
            digit = 15
        return digit

    @staticmethod
    def convert_to_base_digit(digit):
        if digit <= 9:
            return str(digit)
        elif digit == 10:
            return 'A'
        elif digit == 11:
            return 'B'
        elif digit == 12:
            return 'C'
        elif digit == 13:
            return 'D'
        elif digit == 14:
            return 'E'
        elif digit == 15:
            return 'F'

    def add_integers(self, firstNumber, secondNumber):
        self.__validateNumber.validate_number(firstNumber)
        self.__validateNumber.validate_number(secondNumber)
        firstValue = firstNumber.get_number()
        secondValue = secondNumber.get_number()
        base = firstNumber.get_base()
        transport = 0

        # we will retain the digits of the sum, in the reverse order
        sumOfNumbers = []
        for index in range(0, max(len(firstNumber.get_number()), len(secondNumber.get_number()))):
            # if the index is bigger than the length of the number we use 0 as the last digit,
            # otherwise we use the corresponding digit
            if index < len(firstValue):
                currentDigitFirstNumber = firstValue[len(firstValue) - index - 1]
            else:
                currentDigitFirstNumber = '0'
            if index < len(secondValue):
                currentDigitSecondNumber = secondValue[len(secondValue) - index - 1]
            else:
                currentDigitSecondNumber = '0'

            # we convert to decimal digits such that we can do the operation
            currentDigitFirstNumber = self.convert_to_decimal_digit(currentDigitFirstNumber)
            currentDigitSecondNumber = self.convert_to_decimal_digit(currentDigitSecondNumber)

            currentSum = currentDigitFirstNumber + currentDigitSecondNumber + transport

            # the result is then transformed into the corresponding digit in the base, being returned as a string
            # because in case of base 16 we can also have letters
            lastDigitOfSum = self.convert_to_base_digit(currentSum % base)
            transport = currentSum // base
            sumOfNumbers.append(lastDigitOfSum)
        transport = self.convert_to_base_digit(transport)

        # if the transport digit is nonzero, then we add it to the formed number
        if transport != "0":
            sumOfNumbers.append(transport)

        # the digits are saved in the reverse order, so we calculate the reverse of it
        sumOfNumbers.reverse()
        sumOfNumbers = "".join(sumOfNumbers)
        return sumOfNumbers

    def subtract_integers(self, firstNumber, secondNumber):
        firstValue = firstNumber.get_number()
        secondValue = secondNumber.get_number()
        base = firstNumber.get_base()
        transport = 0

        # we will retain the digits of the difference, in the reverse order
        difference = []
        for index in range(0, len(firstNumber.get_number())):
            currentDigitFirstNumber = firstValue[len(firstValue) - index - 1]

            # in the case that the index is bigger than the length of the second number, then we take as digit 0,
            # otherwise the current digit in the number
            if index < len(secondValue):
                currentDigitSecondNumber = secondValue[len(secondValue) - index - 1]
            else:
                currentDigitSecondNumber = '0'

            # we convert the digits into decimal ones such that we can do the operations
            currentDigitFirstNumber = self.convert_to_decimal_digit(currentDigitFirstNumber)
            currentDigitSecondNumber = self.convert_to_decimal_digit(currentDigitSecondNumber)

            # we set the transport digit
            if currentDigitFirstNumber + transport >= currentDigitSecondNumber:
                differenceOfNumbers = currentDigitFirstNumber + transport - currentDigitSecondNumber
                transport = 0
            else:
                differenceOfNumbers = currentDigitFirstNumber + transport + base - currentDigitSecondNumber
                transport = -1

            # we convert the current difference to the given base, being returned as a string
            differenceOfNumbers = self.convert_to_base_digit(differenceOfNumbers)
            difference.append(differenceOfNumbers)

        # having done the operations from right to left, the digits will be saved in reverse order, so we have to put
        # them in the right order
        difference.reverse()
        difference = "".join(difference)

        # we eliminate the leftmost zeros from the beginning of the number
        while difference[0] == '0':
            difference = difference[1:]
        return difference

    def multiply_integers(self, firstNumber, secondNumber):
        firstValue = firstNumber.get_number()
        secondValue = secondNumber.get_number()
        secondValue = self.convert_to_decimal_digit(secondValue)
        base = firstNumber.get_base()
        transport = 0
        product = []
        for index in range(0, len(firstNumber.get_number())):
            currentDigitFirstNumber = firstValue[len(firstValue) - index - 1]

            # we convert the current digit to decimal such that we can do the multiplication
            currentDigitFirstNumber = self.convert_to_decimal_digit(currentDigitFirstNumber)
            currentProduct = currentDigitFirstNumber * secondValue + transport
            transport = currentProduct // base
            currentDigitProduct = currentProduct % base
            currentDigitProduct = self.convert_to_base_digit(currentDigitProduct)
            product.append(currentDigitProduct)
        transport = self.convert_to_base_digit(transport)

        # we add the transport digit to the formed number only if it is nonzero
        if transport != "0":
            product.append(transport)
        product.reverse()
        product = "".join(product)
        return product

    def divide_integers(self, firstNumber, secondNumber):
        firstValue = firstNumber.get_number()
        secondValue = secondNumber.get_number()
        secondValue = self.convert_to_decimal_digit(secondValue)
        base = firstNumber.get_base()
        quotient = []
        remainder = 0
        for index in range(0, len(firstNumber.get_number())):
            currentDigitFirstNumber = firstValue[index]

            # we convert the current digit into the decimal one such that we can do the operations
            currentDigitFirstNumber = self.convert_to_decimal_digit(currentDigitFirstNumber)
            currentQuotient = (remainder * base + currentDigitFirstNumber) // secondValue
            remainder = (remainder * base + currentDigitFirstNumber) - \
                        ((remainder * base + currentDigitFirstNumber) // secondValue) * secondValue
            currentQuotient = self.convert_to_base_digit(currentQuotient)
            quotient.append(currentQuotient)
        remainder = self.convert_to_base_digit(remainder)
        quotient = "".join(quotient)
        while quotient[0] == '0' and len(quotient) != 1:
            quotient = quotient[1:]
        return quotient, remainder

    @staticmethod
    def rapid_conversions_from_base2_to_base(number, sourceBase, destinationBase):
        powerOfDestination = int(math.log(destinationBase, 2))
        # this list of lists contains the conversions of the first 15 digits in base 2, 4, 8 and 16
        rapidConversionTable = [['0', '1', '10', '11', '100', '101', '110', '111', '1000', '1001', '1010', '1011',
                                 '1100', '1101', '1110', '1111'],
                                ['0', '1', '2', '3', '10', '11', '12', '13', '20', '21', '22', '23', '30', '31', '32',
                                 '33'],
                                ['0', '1', '2', '3', '4', '5', '6', '7', '10', '11', '12', '13', '14', '15', '16', '17']
                                , ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']]

        # adding insignificant zeros to the left such that we can make groups of k digits, where k is the power of 2 \
        # of the destination base
        while len(number) % powerOfDestination != 0:
            number = '0' + number[:]
        newNumber = ""
        # adding insignificant zeros to the elements in the conversion list such that we have groups of k digits,
        # where k is the the power of 2 of the destination base
        for index in range(0, destinationBase - 1):
            while len(rapidConversionTable[0][index]) < powerOfDestination:
                rapidConversionTable[0][index] = "0" + rapidConversionTable[0][index][:]
        # we search for the corresponding group of k digits in the conversion list
        for index1 in range(0, len(number), powerOfDestination):
            index2 = 0
            while index2 <= 15:
                if rapidConversionTable[0][index2] == number[index1:index1 + powerOfDestination]:
                    newNumber += rapidConversionTable[powerOfDestination - 1][index2]
                    index2 = 15
                index2 += 1
        # removing the insignificant zeros
        while newNumber[0] == '0':
            newNumber = newNumber[1:]
        return newNumber

    @staticmethod
    def rapid_conversions_from_base_to_base2(number, sourceBase, destinationBase):
        powerOfSource = int(math.log(sourceBase, 2))
        rapidConversionTable = [['0', '1', '10', '11', '100', '101', '110', '111', '1000', '1001', '1010', '1011',
                                 '1100', '1101', '1110', '1111'], ['0', '1', '2', '3', '10', '11', '12', '13', '20',
                                                                   '21', '22', '23', '30', '31', '32', '33'],
                                ['0', '1', '2', '3', '4', '5', '6', '7',
                                 '10', '11', '12', '13', '14', '15', '16', '17'], ['0', '1', '2', '3', '4', '5', '6',
                                                                                   '7', '8', '9', 'A', 'B', 'C', 'D',
                                                                                   'E', 'F']]
        newNumber = ""
        for index in range(0, sourceBase - 1):
            while len(rapidConversionTable[0][index]) < powerOfSource:
                rapidConversionTable[0][index] = "0" + rapidConversionTable[0][index][:]
        for digit in number:
            index = 0
            while index <= sourceBase - 1:
                if rapidConversionTable[powerOfSource - 1][index] == digit:
                    newNumber += rapidConversionTable[0][index]
                    index = sourceBase
                index += 1
        while newNumber[0] == '0':
            newNumber = newNumber[1:]
        return newNumber

    def successive_divisions(self, number, sourceBase, destinationBase):
        newNumber = []
        quotient, remainder = self.divide_integers(Number(number, sourceBase), Number(str(destinationBase), sourceBase))
        newNumber.append(remainder)
        while quotient != "0":
            quotient, remainder = self.divide_integers(Number(quotient, sourceBase),
                                                       Number(str(destinationBase), sourceBase))
            newNumber.append(remainder)
        newNumber.reverse()
        newNumber = "".join(newNumber)
        return newNumber

    def substitution(self, number, sourceBase, destinationBase):
        newNumber = "0"
        powerOfSourceBase = "1"

        # we calculate the maximum power of the source base
        for index in range(1, len(number)):
            powerOfSourceBase = self.multiply_integers(Number(powerOfSourceBase, destinationBase),
                                                       Number(str(sourceBase), destinationBase))

        for index in range(len(number)):
            currentProduct = self.multiply_integers(Number(powerOfSourceBase, destinationBase),
                                                    Number(number[index], destinationBase))
            powerOfSourceBase, quotient = self.divide_integers(Number(powerOfSourceBase, destinationBase),
                                                               Number(str(sourceBase), destinationBase))
            newNumber = self.add_integers(Number(newNumber, destinationBase), Number(currentProduct, destinationBase))
        return newNumber

    def converse_from_base_to_another_base(self, number, baseToConvert):
        self.__validateNumber.validate_number(number)
        currentBase = number.get_base()
        if int(math.log(baseToConvert, 2)) == math.log(baseToConvert, 2):
            baseToConvertPowerOf2 = True
        else:
            baseToConvertPowerOf2 = False
        if int(math.log(currentBase, 2)) == math.log(currentBase, 2):
            currentBasePowerOf2 = True
        else:
            currentBasePowerOf2 = False
        valueOfNumber = number.get_number()
        if currentBase == 2 and baseToConvertPowerOf2 == True:
            numberConverted = self.rapid_conversions_from_base2_to_base(valueOfNumber, currentBase, baseToConvert)
        elif currentBasePowerOf2 == True and baseToConvert == 2:
            numberConverted = self.rapid_conversions_from_base_to_base2(valueOfNumber, currentBase, baseToConvert)
        elif currentBasePowerOf2 == True and baseToConvertPowerOf2 == True:
            numberConverted = self.rapid_conversions_from_base_to_base2(valueOfNumber, currentBase, 2)
            numberConverted = self.rapid_conversions_from_base2_to_base(numberConverted, 2, baseToConvert)
        elif currentBase == 10 and baseToConvert == 2:
            numberConverted = self.successive_divisions(valueOfNumber, currentBase, 16)
            numberConverted = self.rapid_conversions_from_base_to_base2(numberConverted, 16, baseToConvert)
        elif currentBase < baseToConvert:
            numberConverted = self.substitution(valueOfNumber, currentBase, baseToConvert)
        elif currentBase > baseToConvert:
            numberConverted = self.successive_divisions(valueOfNumber, currentBase, baseToConvert)
        elif currentBase == baseToConvert:
            numberConverted = valueOfNumber
        return numberConverted
