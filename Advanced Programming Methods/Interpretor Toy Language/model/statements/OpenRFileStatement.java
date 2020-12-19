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
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStatement implements Statement{
    private final Expression expression;

    public OpenRFileStatement(Expression expression){
        this.expression = expression;
    }

    public Expression getExpression() {
        return expression;
    }

    @Override
    public synchronized ProgramState execute(ProgramState state) throws MyException {
        synchronized (this) {
            MyIDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
            MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
            Value value = expression.evaluate(symbolTable, state.getHeap());

            if (value.getType().equals(new StringType())) {
                StringValue file = (StringValue) value;
                if (fileTable.isDefined(file)) {
                    throw new MyException("The file is already opened!");
                }
                try {
                    BufferedReader reader = new BufferedReader(new FileReader(file.getValue()));
                    fileTable.update(file, reader);
                } catch (FileNotFoundException exception) {
                    throw new MyException("Cannot create file reader! " + exception.getMessage());
                }
            } else {
                throw new MyException("The expression is not a string type!");
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
            throw new MyException("The expression in the openRFile statement is not a string!");
    }

    @Override
    public String toString() {
        return "open(" + expression + ")";
    }

    @Override
    public Statement deepCopy() {
        return null;
    }


}
