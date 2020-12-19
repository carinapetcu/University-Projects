package model.expressions;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.Type;
import model.values.Value;

public class ValueExpression implements Expression{
    private final Value expression;

    public ValueExpression(Value expression){

        this.expression = expression;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heap) throws MyException {
        return expression;
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        return expression.getType();
    }

    @Override
    public String toString() {
        return expression.toString();
    }

    @Override
    public Expression deepCopy() {
        return new ValueExpression(expression.deepCopy());
    }
}
