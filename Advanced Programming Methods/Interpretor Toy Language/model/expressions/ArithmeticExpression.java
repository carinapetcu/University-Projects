package model.expressions;

import exceptions.DivisionByZeroException;
import exceptions.InvalidOperandTypeException;
import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

public class ArithmeticExpression implements Expression{
    private final Expression firstExpression;
    private final Expression secondExpression;
    private final int operation; // 1- plus, 2-minus, 3-star, 4-divide

    public ArithmeticExpression(int operation, Expression firstExpression, Expression secondExpression){
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }
    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heap) throws MyException {

        Value firstValue;
        Value secondValue;
        firstValue = firstExpression.evaluate(symbolTable, heap);

        if(firstValue.getType().equals(new IntType())){

            secondValue = secondExpression.evaluate(symbolTable, heap);

            if(secondValue.getType().equals(new IntType())){
                IntValue firstIntValue = (IntValue)firstValue;
                IntValue secondIntValue = (IntValue)secondValue;
                int firstNumber, secondNumber;
                firstNumber = firstIntValue.getValue();
                secondNumber = secondIntValue.getValue();
                if(operation == 1)
                    return new IntValue(firstNumber + secondNumber);
                else if(operation == 2)
                    return new IntValue(firstNumber - secondNumber);
                else if(operation == 3)
                    return new IntValue(firstNumber * secondNumber);
                else if(operation == 4)
                    if(secondNumber == 0) throw new DivisionByZeroException("Division by zero!");
                    else return new IntValue(firstNumber / secondNumber);
            }
            else throw new InvalidOperandTypeException("Second operand is not an integer!");
        }
        else throw new InvalidOperandTypeException("First operand is not an integer!");
        return new IntValue(0);
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type firstExpressionType = firstExpression.typeCheck(typeEnvironment);
        Type secondExpressionType = secondExpression.typeCheck(typeEnvironment);
        if(firstExpressionType.equals(new IntType())){
            if(secondExpressionType.equals(new IntType())){
                return new IntType();
            } else
                throw new MyException("The second operand is not an integer!");
        } else
            throw new MyException("The first operand is not an integer!");
    }

    @Override
    public String toString() {
        return switch (operation) {
            case 1 -> firstExpression.toString() + " + " + secondExpression.toString();
            case 2 -> firstExpression.toString() + " - " + secondExpression.toString();
            case 3 -> firstExpression.toString() + " * " + secondExpression.toString();
            case 4 -> firstExpression.toString() + " / " + secondExpression.toString();
            default -> "";
        };
    }

    @Override
    public Expression deepCopy() {
        return new ArithmeticExpression(operation, firstExpression.deepCopy(),secondExpression.deepCopy());
    }
}
