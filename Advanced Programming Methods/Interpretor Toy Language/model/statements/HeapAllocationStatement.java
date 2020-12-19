package model.statements;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.adt.ProgramState;
import model.expressions.Expression;
import model.types.ReferenceType;
import model.types.Type;
import model.values.ReferenceValue;
import model.values.Value;

public class HeapAllocationStatement implements Statement{
    private final String variableName;
    private final Expression expression;

    public HeapAllocationStatement(String variableName, Expression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public synchronized ProgramState execute(ProgramState state) throws MyException {
        synchronized (this) {
            MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
            if (symbolTable.isDefined(variableName)) {
                if (symbolTable.lookup(variableName).getType() instanceof ReferenceType) {
                    ReferenceValue locationValue = (ReferenceValue) symbolTable.lookup(variableName);
                    Value value = expression.evaluate(symbolTable, state.getHeap());
                    if (locationValue.getType().equals(locationValue.getType())) {
                        MyIHeap<Value> heap = state.getHeap();
                        int address = heap.allocate(value);
                        symbolTable.update(variableName, new ReferenceValue(address, value.getType()));
                    } else {
                        throw new MyException("The expression is not a reference type!");
                    }

                } else {
                    throw new MyException("The type is not of reference type!");
                }

            } else {
                throw new MyException("The variable is not defined!");
            }
            return null;
        }
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type variableType = typeEnvironment.lookup(variableName);
        Type expressionType = expression.typeCheck(typeEnvironment);
        if(variableType.equals(new ReferenceType(expressionType))){
            return typeEnvironment;
        } else
            throw new MyException("The right side of the NEW statement and the left side are of different types!");
    }

    @Override
    public String toString() {
        return "new( " + variableName + "," + expression.toString() + ")";
    }

    @Override
    public Statement deepCopy() {
        return new HeapAllocationStatement(variableName, expression.deepCopy());
    }
}
