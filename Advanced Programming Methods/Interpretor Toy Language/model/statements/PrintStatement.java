package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIList;
import model.adt.ProgramState;
import model.expressions.Expression;
import model.types.Type;
import model.values.Value;

public class PrintStatement implements Statement {
    private final Expression expression;

    public PrintStatement(Expression expression){
        this.expression = expression;
    }

    @Override
    public String toString(){

        return "print(" + expression.toString() + ")";
    }

    @Override
    public synchronized ProgramState execute(ProgramState state) throws MyException {
        synchronized (this) {
            MyIList<Value> outputList = state.getOutput();
            MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
            outputList.add(expression.evaluate(symbolTable, state.getHeap()));
            return null;
        }
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        expression.typeCheck(typeEnvironment);
        return typeEnvironment;
    }

    @Override
    public Statement deepCopy() {
        return new PrintStatement(expression.deepCopy());
    }
}
