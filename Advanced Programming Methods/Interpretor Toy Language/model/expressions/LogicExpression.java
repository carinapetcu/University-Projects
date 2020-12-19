package model.expressions;

import exceptions.InvalidOperandTypeException;
import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.BooleanType;
import model.types.Type;
import model.values.BooleanValue;
import model.values.Value;

public class LogicExpression implements Expression{
    private final Expression firstExpression;
    private final Expression secondExpression;
    private final int operator; // 1 - &&, 2 - ||

    public LogicExpression(Expression firstExpression, Expression secondExpression, int operator){
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operator = operator;
    }

    @Override
    public synchronized Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heap) throws MyException {
        Value firstValue;
        Value secondValue;
        firstValue = firstExpression.evaluate(symbolTable, heap);

        if(firstValue.getType().equals(new BooleanType())){

            secondValue = secondExpression.evaluate(symbolTable, heap);

            if(secondValue.getType().equals(new BooleanType())){
                BooleanValue firstIntValue = (BooleanValue)firstValue;
                BooleanValue secondIntValue = (BooleanValue)secondValue;
                boolean firstBoolean, secondBoolean;
                firstBoolean = firstIntValue.getValue();
                secondBoolean = secondIntValue.getValue();
                if(operator == 1)
                    return new BooleanValue(firstBoolean && secondBoolean);
                else if(operator == 2)
                    return new BooleanValue(firstBoolean || secondBoolean);
            }
            else throw new InvalidOperandTypeException("Second operand is not a boolean!");
        }
        else throw new InvalidOperandTypeException("First operand is not a boolean!");
        return new BooleanValue();
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type firstExpressionType, secondExpressionType;
        firstExpressionType = firstExpression.typeCheck(typeEnvironment);
        secondExpressionType = secondExpression.typeCheck(typeEnvironment);
        if(firstExpressionType.equals(new BooleanType())){
            if(secondExpressionType.equals(new BooleanType())){
                return new BooleanType();
            } else
                throw new MyException("The second operand is not a boolean!");
        } else
            throw new MyException("The first operand is not a boolean!");
    }

    @Override
    public String toString() {
        return switch (operator) {
            case 1 -> firstExpression.toString() + " && " + secondExpression.toString();
            case 2 -> firstExpression.toString() + " || " + secondExpression.toString();
            default -> "";
        };
    }

    @Override
    public Expression deepCopy() {
        return new LogicExpression(firstExpression.deepCopy(), secondExpression.deepCopy(), operator);
    }
}
