package model.statements;

import exceptions.MyException;
import exceptions.VariableNotDefinedException;
import exceptions.VariableTypesNotMatchingException;
import model.adt.MyIDictionary;
import model.adt.ProgramState;
import model.expressions.Expression;
import model.types.Type;
import model.values.Value;

public class AssignmentStatement implements Statement {
    private final String id;
    private final Expression expression;

    public AssignmentStatement(String id, Expression expression){
        this.id = id;
        this.expression = expression;
    }

    public String getId() {
        return id;
    }

    public Expression getExpression() {
        return expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();

        if (symbolTable.isDefined(id)){
            Value value = expression.evaluate(symbolTable, state.getHeap());
            Type typeId = (symbolTable.lookup(id)).getType();
            if(value.getType().equals(typeId)){
                symbolTable.update(id, value);
            }
            else throw new VariableTypesNotMatchingException("Declared type of variable" + id +
                    "and type of the assigned expression do not match.");
        }
        else throw new VariableNotDefinedException("The used variable" + id + "was not declared before.");
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type variableType = typeEnvironment.lookup(id);
        Type expressionType = expression.typeCheck(typeEnvironment);
        if(variableType.equals(expressionType))
            return typeEnvironment;
        else
            throw new MyException("The right hand side of the assignment and the left hand side have different types.");
    }

    @Override
    public Statement deepCopy() {
        return new AssignmentStatement(id, expression.deepCopy());
    }

    @Override
    public String toString(){

        return id + "=" + expression.toString();
    }

}
