package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.ProgramState;
import model.expressions.Expression;
import model.types.StringType;
import model.types.Type;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements Statement{
    private final Expression expression;

    public CloseRFileStatement(Expression expression){
        this.expression = expression;
    }

    @Override
    public synchronized ProgramState execute(ProgramState state) throws MyException {
        synchronized (this) {
            MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
            Value value = expression.evaluate(symbolTable, state.getHeap());
            if (value.getType().equals(new StringType())) {
                MyIDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
                StringValue stringValue = (StringValue) value;
                if (fileTable.isDefined(stringValue)) {
                    BufferedReader reader = fileTable.lookup(stringValue);
                    try {
                        reader.close();
                        fileTable.remove(stringValue);
                    } catch (IOException exception) {
                        throw new MyException(exception.getMessage());
                    }
                } else {
                    throw new MyException("The string value is not defined in the file table!");
                }
            } else {
                throw new MyException("The expression is not a string!");
            }
            return null;
        }
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type expressionType = expression.typeCheck(typeEnvironment);
        if(expressionType.equals(new StringType())){
            return typeEnvironment;
        } else
            throw new MyException("The expression in the closeRFile statement is not a string!");
    }

    @Override
    public String toString() {
        return "close(" + expression + ")";
    }

    @Override
    public Statement deepCopy() {
        return null;
    }
}
