from tkinter import *
from tkinter import messagebox
from entities.entities import Number


class GUI:
    def __init__(self, serviceNumber):
        self.__serviceNumber = serviceNumber

    def __gui_add_two_integers(self):
        firstNumber = self.firstNumber.get()
        secondNumber = self.secondNumber.get()
        base = self.base.get()
        try:
            result = self.__serviceNumber.add_integers(Number(str(firstNumber), int(base)), Number(str(secondNumber),
                                                                                                   int(base)))
            windowAddition = Toplevel()
            addition = Text(windowAddition)
            addition.insert(INSERT, "The sum between {} and {} in base {} is {}".format(firstNumber, secondNumber,
                                                                                        base, result))
            addition.insert(INSERT, '\n')
            addition.pack()
            windowAddition.mainloop()
        except Exception as exception:
            messagebox.showinfo("Error", "Error adding numbers - " + str(exception))

    def __gui_subtract_two_integers(self):
        firstNumber = self.firstNumber.get()
        secondNumber = self.secondNumber.get()
        base = self.base.get()
        try:
            result = self.__serviceNumber.subtract_integers(Number(str(firstNumber), int(base)),
                                                            Number(str(secondNumber), int(base)))
            windowSubtraction = Toplevel()
            subtraction = Text(windowSubtraction)
            subtraction.insert(INSERT, "The difference between {} and {} in base {} is {}".format(firstNumber,
                                                                                                  secondNumber,
                                                                                                  base, result))
            subtraction.insert(INSERT, '\n')
            subtraction.pack()
            windowSubtraction.mainloop()
        except Exception as exception:
            messagebox.showinfo("Error", "Error subtracting numbers - " + str(exception))

    def __gui_multiply_two_integers(self):
        firstNumber = self.firstNumber.get()
        secondNumber = self.secondNumber.get()
        base = self.base.get()
        try:
            result = self.__serviceNumber.multiply_integers(Number(str(firstNumber), int(base)),
                                                            Number(str(secondNumber), int(base)))
            windowMultiplication = Toplevel()
            multiplication = Text(windowMultiplication)
            multiplication.insert(INSERT, "The product between {} and {} in base {} is {}".format(firstNumber,
                                                                                                  secondNumber, base,
                                                                                                  result))
            multiplication.insert(INSERT, '\n')
            multiplication.pack()
            windowMultiplication.mainloop()
        except Exception as exception:
            messagebox.showinfo("Error", "Error multiplying numbers - " + str(exception))

    def __gui_divide_two_integers(self):
        firstNumber = self.firstNumber.get()
        secondNumber = self.secondNumber.get()
        base = self.base.get()
        try:
            quotient, remainder = self.__serviceNumber.divide_integers(Number(str(firstNumber), int(base)),
                                                                       Number(str(secondNumber), int(base)))
            windowDivision = Toplevel()
            division = Text(windowDivision)
            division.insert(INSERT, "The division between {} and {} in base {} has a quotient of {} and a "
                                    "remainder of {}".format(firstNumber, secondNumber, base, quotient, remainder))
            division.insert(INSERT, '\n')
            division.pack()
            windowDivision.mainloop()
        except Exception as exception:
            messagebox.showinfo("Error", "Error multiplying numbers - " + str(exception))

    def __gui_operations(self):
        self.operations = Tk()
        self.operations.title("Operations")
        frameOperations = Frame(self.operations)
        frameOperations.pack()
        self.frameOperations = frameOperations

        label = Label(frameOperations, text="First number:")
        label.pack(side=LEFT)

        self.firstNumber = Entry(frameOperations, {})
        self.firstNumber.pack(side=LEFT)

        label = Label(frameOperations, text="Second number:")
        label.pack(side=LEFT)

        self.secondNumber = Entry(frameOperations, {})
        self.secondNumber.pack(side=LEFT)

        label = Label(frameOperations, text="Base:")
        label.pack(side=LEFT)

        self.base = Entry(frameOperations, {})
        self.base.pack(side=LEFT)

        self.addNumbers = Button(frameOperations, text="Add", command=self.__gui_add_two_integers)
        self.addNumbers.pack(side=LEFT)

        self.subtractNumbers = Button(frameOperations, text="Subtract", command=self.__gui_subtract_two_integers)
        self.subtractNumbers.pack(side=LEFT)

        self.multiplyNumbers = Button(frameOperations, text="Multiply", command=self.__gui_multiply_two_integers)
        self.multiplyNumbers.pack(side=LEFT)

        self.divideNumbers = Button(frameOperations, text="Divide", command=self.__gui_divide_two_integers)
        self.divideNumbers.pack(side=LEFT)

        self.operations.mainloop()

    def __gui_converse_from_base_to_another_base(self):
        number = self.number.get()
        sourceBase = self.sourceBase.get()
        destinationBase = self.destinationBase.get()
        try:
            result = self.__serviceNumber.converse_from_base_to_another_base(Number(str(number),
                                                                                                 int(sourceBase)),
                                                                                          int(destinationBase))
            windowConversion = Toplevel()
            conversion = Text(windowConversion)
            conversion.insert(INSERT, "The number {} in base {} converted in base {} is {}".format(number, sourceBase,
                                                                                                   destinationBase,
                                                                                                   result))
            conversion.insert(INSERT, '\n')
            conversion.pack()
            windowConversion.mainloop()
        except Exception as exception:
            messagebox.showinfo("Error", "Error converting number - " + str(exception))

    def __gui_conversions(self):
        self.conversions = Tk()
        self.conversions.title("Conversions")
        frameConversions = Frame(self.conversions)
        frameConversions.pack()
        self.frameConversions = frameConversions

        label = Label(frameConversions, text="Number:")
        label.pack(side=LEFT)

        self.number = Entry(frameConversions, {})
        self.number.pack(side=LEFT)

        label = Label(frameConversions, text="Source base:")
        label.pack(side=LEFT)

        self.sourceBase = Entry(frameConversions, {})
        self.sourceBase.pack(side=LEFT)

        label = Label(frameConversions, text="Destination base:")
        label.pack(side=LEFT)

        self.destinationBase = Entry(frameConversions, {})
        self.destinationBase.pack(side=LEFT)

        self.convert = Button(frameConversions, text="Convert", command=self.__gui_converse_from_base_to_another_base)
        self.convert.pack(side=LEFT)

        self.operations.mainloop()

    def __gui_show_name(self):
        windowName = Toplevel()
        conversion = Text(windowName)
        conversion.insert(INSERT, "Author name: Petcu Carina\n"
                                  "Group: 916")
        conversion.insert(INSERT, '\n')
        conversion.pack()
        windowName.mainloop()

    def start_application(self):
        self.tk = Tk()
        self.tk.title("Operations and conversions in different bases.")

        frame = Frame(self.tk)
        frame.pack()
        self.frame = frame

        self.operations = Button(frame, text="Enter the operations menu.", command=self.__gui_operations)
        self.operations.pack(side=LEFT)

        self.conversions = Button(frame, text="Enter the conversions menu.", command=self.__gui_conversions)
        self.conversions.pack(side=LEFT)

        self.name = Button(frame, text="Show the name of the author.", command=self.__gui_show_name)
        self.name.pack(side=LEFT)

        self.tk.mainloop()
