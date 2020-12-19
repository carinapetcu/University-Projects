package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.ProgramState;
import model.expressions.Expression;
import model.types.IntType;
import model.types.StringType;
import model.types.Type;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements Statement{
    private final Expression expression;
    private final String variableName;

    public ReadFileStatement(Expression expression, String variableName){
        this.expression = expression;
        this.variableName = variableName;
    }

    @Override
    public synchronized ProgramState execute(ProgramState state) throws MyException {
        synchronized (this) {
            MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
            if (symbolTable.isDefined(variableName)) {
                if (symbolTable.lookup(variableName).getType().equals(new IntType())) {
                    Value value = expression.evaluate(symbolTable, state.getHeap());
                    if (value.getType().equals(new StringType())) {
                        StringValue stringValue = (StringValue) value;
                        MyIDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
                        if (fileTable.isDefined(stringValue)) {
                            BufferedReader reader = fileTable.lookup(stringValue);
                            try {
                                String line = reader.readLine();
                                IntValue newValue = new IntValue(0);
                                if (line != null) {
                                    newValue = new IntValue(Integer.parseInt(line));
                                }
                                symbolTable.update(variableName, newValue);
                            } catch (IOException exception) {
                                throw new MyException(exception.getMessage());
                            }

                        } else {
                            throw new MyException("The string value is not defined in the file table!");
                        }
                    } else {
                        throw new MyException("The expression is not a string value!");
                    }
                } else {
                    throw new MyException("Variable name is not a int!");
                }
            } else {
                throw new MyException("The variable name is not defined!");
            }
            return null;
        }
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type variableType = typeEnvironment.lookup(variableName);
        Type expressionType = expression.typeCheck(typeEnvironment);
        if(variableType.equals(new IntType())){
            if(expressionType.equals(new StringType())){
                return typeEnvironment;
            } else
                throw new MyException("The expression from the readFile statement is not a string!");
        } else
            throw new MyException("The variable from the readFile statement is not an integer!");
    }

    @Override
    public String toString() {
        return "read from " + expression + " into " + variableName;
    }


    @Override
    public Statement deepCopy() {
        return null;
    }
}
