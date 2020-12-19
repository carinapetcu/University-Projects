package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.ProgramState;
import model.types.Type;

public interface Statement {
    ProgramState execute(ProgramState state) throws MyException; // which is the execution method for a statement
    MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException;
    Statement deepCopy();
}
