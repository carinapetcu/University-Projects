package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.adt.MyIStack;
import model.adt.ProgramState;
import model.expressions.Expression;
import model.types.BooleanType;
import model.types.Type;
import model.values.BooleanValue;
import model.values.Value;

public class WhileStatement implements Statement{
    public final Expression expression;
    public final Statement statement;

    public WhileStatement(Expression expression, Statement statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIStack<Statement> stack = state.getExecutionStack();
        MyIHeap<Value> heap = state.getHeap();
        Value value = expression.evaluate(symbolTable, heap);
        if(value instanceof BooleanValue){
            BooleanValue booleanValue = (BooleanValue)value;
            if(booleanValue.getValue()){
                stack.push(this.deepCopy());
                stack.push(statement);
            }
        } else {
            throw new MyException("Condition expression not a boolean!");
        }

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type expressionType = expression.typeCheck(typeEnvironment);
        if(expressionType.equals(new BooleanType())){
            statement.typeCheck(typeEnvironment.deepCopy());
            return typeEnvironment;
        } else
            throw new MyException("The condition of WHILE has not the type boolean!");
    }

    @Override
    public String toString() {
        return "(while(" + expression + ") " + statement + ")";
    }

    @Override
    public Statement deepCopy() {
        return new WhileStatement(expression.deepCopy(), statement.deepCopy());
    }
}
