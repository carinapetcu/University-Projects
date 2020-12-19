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

public class HeapWritingStatement implements Statement{
    private final String variableName;
    private final Expression expression;

    public HeapWritingStatement(String variableName, Expression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public synchronized ProgramState execute(ProgramState state) throws MyException {
        synchronized (this) {
            MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
            MyIHeap<Value> heap = state.getHeap();
            if (symbolTable.isDefined(variableName)) {
                Value value = symbolTable.lookup(variableName);
                if (value.getType() instanceof ReferenceType) {

                    ReferenceValue address = (ReferenceValue) value;
                    if (heap.isDefined(address.getAddress())) {

                        Value valueExpression = expression.evaluate(symbolTable, heap);
                        if (symbolTable.lookup(variableName).getType().equals(new ReferenceType(valueExpression.getType()))) {
                            int addressOfVariable = address.getAddress();
                            heap.update(addressOfVariable, valueExpression);

                        } else {
                            throw new MyException("The evaluated expression has a different type!");
                        }

                    } else {
                        throw new MyException("The reference value has not an associated a key in the symbol table!");
                    }
                } else {
                    throw new MyException("The value is not of reference type!");
                }

            } else {
                throw new MyException("The variable is not defined on the symbol table!");
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
            throw new MyException("The right side of the heapWriting statement and the left side are of different types!");
    }

    @Override
    public Statement deepCopy() {
        return new HeapWritingStatement(variableName, expression.deepCopy());
    }

    @Override
    public String toString() {
        return "wH(" + variableName + "," + expression + ")";
    }
}
