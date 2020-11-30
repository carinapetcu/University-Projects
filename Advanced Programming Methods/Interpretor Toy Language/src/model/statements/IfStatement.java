package model.statements;

import exceptions.InvalidOperandTypeException;
import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.ProgramState;
import model.expressions.Expression;
import model.types.BooleanType;
import model.types.Type;
import model.values.BooleanValue;
import model.values.Value;

public class IfStatement implements Statement {

    private final Expression expression;
    private final Statement thenStatement;
    private final Statement elseStatement;

    public IfStatement(Expression expression, Statement thenStatement, Statement elseStatement){
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyIStack<Statement> stack = state.getExecutionStack();
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        Value condition = expression.evaluate(symbolTable, state.getHeap());

        if(!condition.getType().equals(new BooleanType())){
            throw new InvalidOperandTypeException("Conditional expression is not a boolean");
        } else {
            BooleanValue booleanCondition = (BooleanValue)condition;
            if(booleanCondition.getValue()){
                stack.push(thenStatement);
            } else {
                stack.push(elseStatement);
            }
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type expressionType = expression.typeCheck(typeEnvironment);
        if(expressionType.equals(new BooleanType())){
            elseStatement.typeCheck(typeEnvironment.deepCopy());
            thenStatement.typeCheck(typeEnvironment.deepCopy());
            return typeEnvironment;
        } else
            throw new MyException("The condition of IF has not the type boolean!");
    }

    @Override
    public Statement deepCopy() {
        return new IfStatement(expression.deepCopy(), thenStatement.deepCopy(), elseStatement.deepCopy());
    }

    @Override
    public String toString(){
        return "(IF(" + expression.toString() + ") THEN(" + thenStatement.toString() + ") ELSE("
                + elseStatement.toString() + "))";
    }
}
