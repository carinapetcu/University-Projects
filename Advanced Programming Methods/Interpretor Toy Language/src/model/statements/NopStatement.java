package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.ProgramState;
import model.types.Type;

public class NopStatement implements Statement {

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        return typeEnvironment;
    }

    @Override
    public Statement deepCopy() {
        return new NopStatement();
    }
}
