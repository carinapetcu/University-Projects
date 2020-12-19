package model.expressions;

import exceptions.InvalidOperandTypeException;
import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.BooleanType;
import model.types.IntType;
import model.types.Type;
import model.values.BooleanValue;
import model.values.IntValue;
import model.values.Value;

public class RelationalExpression implements Expression{
    private final Expression firstExpression;
    private final Expression secondExpression;
    private final String operation;

    public RelationalExpression(String operation, Expression firstExpression, Expression secondExpression){
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }
    @Override
    public synchronized Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heap) throws MyException {

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
                switch (operation) {
                    case "<":
                        return new BooleanValue(firstNumber < secondNumber);
                    case "<=":
                        return new BooleanValue(firstNumber <= secondNumber);
                    case "==":
                        return new BooleanValue(firstNumber == secondNumber);
                    case "!=":
                        return new BooleanValue(firstNumber != secondNumber);
                    case ">":
                        return new BooleanValue(firstNumber > secondNumber);
                    case ">=":
                        return new BooleanValue(firstNumber >= secondNumber);
                }
            }
            else throw new InvalidOperandTypeException("Second operand is not an integer!");
        }
        else throw new InvalidOperandTypeException("First operand is not an integer!");
        return new BooleanValue(false);
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type firstType, secondType;
        firstType = firstExpression.typeCheck(typeEnvironment);
        secondType = secondExpression.typeCheck(typeEnvironment);
        if(firstType.equals(new IntType())){
            if(secondType.equals(new IntType())){
                return new BooleanType();
            } else
                throw new MyException("The second operand is not an integer!");
        } else
            throw new MyException("The first operand is not an integer!");
    }

    @Override
    public String toString() {
        return switch (operation) {
            case "<"  -> firstExpression.toString() + " < " + secondExpression.toString();
            case "<=" -> firstExpression.toString() + " <= " + secondExpression.toString();
            case "==" -> firstExpression.toString() + " == " + secondExpression.toString();
            case "!=" -> firstExpression.toString() + " != " + secondExpression.toString();
            case ">"  -> firstExpression.toString() + " > " + secondExpression.toString();
            case "=>" -> firstExpression.toString() + " >= " + secondExpression.toString();
            default -> "";
        };
    }

    @Override
    public Expression deepCopy() {
        return new RelationalExpression(operation, firstExpression.deepCopy(),secondExpression.deepCopy());
    }
}
