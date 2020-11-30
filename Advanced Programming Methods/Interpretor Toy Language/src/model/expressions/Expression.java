package model.expressions;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.adt.MyIStack;
import model.types.Type;
import model.values.Value;

public interface Expression {
    Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heap) throws MyException;
    Type typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException;
    Expression deepCopy();
}
