package model.statements;

import exceptions.AlreadyDeclaredVariableException;
import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.ProgramState;
import model.types.Type;
import model.values.Value;

public class VariableDeclarationStatement implements Statement {
    private final String name;
    private final Type type;

    public VariableDeclarationStatement(String name, Type type){
        this.name = name;
        this.type = type;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        if(symbolTable.isDefined(name)){
            throw new AlreadyDeclaredVariableException("Variable is already declared!");
        } else {
            symbolTable.update(name, type.defaultValue());
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        typeEnvironment.update(name, type);
        return typeEnvironment;
    }

    @Override
    public Statement deepCopy() {
        return new VariableDeclarationStatement(name, type.deepCopy());
    }

    @Override
    public String toString() {
        return type + " " + name;
    }
}
