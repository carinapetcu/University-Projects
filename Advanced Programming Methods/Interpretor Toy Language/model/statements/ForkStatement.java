package model.statements;

import exceptions.MyException;
import model.adt.*;
import model.types.Type;
import model.values.Value;

public class ForkStatement implements Statement{
    Statement statement;

    public ForkStatement(Statement statement){
        this.statement = statement;
    }


    @Override
    public synchronized ProgramState execute(ProgramState state) throws MyException {
        synchronized (this){
            var symbolTableInitial = state.getSymbolTable();
            var heapInitial = state.getHeap();
            var fileTableInitial = state.getFileTable();
            var outputInitial = state.getOutput();

            MyIDictionary<String, Value> newSymbolTable = new MyDictionary<>();
            MyIStack<Statement> newStack = new MyStack<>();
            symbolTableInitial.getContent().forEach((key, value) -> newSymbolTable.update(key, value.deepCopy()));

            return new ProgramState(newStack, newSymbolTable, outputInitial, fileTableInitial, heapInitial, statement);
        }
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        statement.typeCheck(typeEnvironment.deepCopy());
        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "fork( " + statement + " )";
    }

    @Override
    public Statement deepCopy() {
        return new ForkStatement(statement);
    }
}
