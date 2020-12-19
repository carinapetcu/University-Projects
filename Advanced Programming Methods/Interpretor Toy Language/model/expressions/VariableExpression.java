package model.expressions;

import exceptions.MyException;
import exceptions.VariableNotDefinedException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.Type;
import model.values.Value;

public class VariableExpression implements Expression{
    private final String id;

    public VariableExpression(String id){
        this.id = id;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heap) throws MyException {

        if(!symbolTable.isDefined(id))
            throw new VariableNotDefinedException("The variable is not defined!");
        return symbolTable.lookup(id);
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        return typeEnvironment.lookup(id);
    }

    @Override
    public String toString() {
        return id;
    }

    @Override
    public Expression deepCopy() {
        return new VariableExpression(id);
    }
}
