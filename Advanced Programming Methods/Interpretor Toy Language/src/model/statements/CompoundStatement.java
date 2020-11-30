package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.ProgramState;
import model.types.Type;

public class CompoundStatement implements Statement {
    private final Statement firstStatement;
    private final Statement secondStatement;

    public CompoundStatement(Statement firstStatement, Statement secondStatement){
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIStack<Statement> stack = state.getExecutionStack();
        stack.push(secondStatement);
        stack.push(firstStatement);
        return null;

    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        MyIDictionary<String, Type> firstStatementTypeEnvironment = firstStatement.typeCheck(typeEnvironment);
        return secondStatement.typeCheck(firstStatementTypeEnvironment);
    }

    @Override
    public Statement deepCopy() {
        return new CompoundStatement(firstStatement.deepCopy(), secondStatement.deepCopy());
    }

    @Override
    public String toString(){

        return "(" + firstStatement.toString() + ";" + secondStatement.toString() + ")";
    }
}
