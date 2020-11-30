package model.expressions;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.ReferenceType;
import model.types.Type;
import model.values.ReferenceValue;
import model.values.Value;

public class HeapReadingExpression implements Expression{
    private final Expression expression;

    public HeapReadingExpression(Expression expression) {
        this.expression = expression;
    }

    @Override
    public synchronized Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heap) throws MyException {
        synchronized (this) {
            Value value = expression.evaluate(symbolTable, heap);
            if (value.getType() instanceof ReferenceType) {
                ReferenceValue address = (ReferenceValue) value;
                if (heap.isDefined(address.getAddress())) {
                    return heap.lookup(address.getAddress());
                } else {
                    throw new MyException("The address is not defined on the heap!");
                }
            } else {
                throw new MyException("The value is not a reference type!");
            }
        }
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnvironment) throws MyException {
        Type expressionType = expression.typeCheck(typeEnvironment);
        if(expressionType instanceof ReferenceType){
            ReferenceType referenceTypeExpression = (ReferenceType) expressionType;
            return referenceTypeExpression.getInner();
        } else
            throw new MyException("The rH argument is not a Reference Type!");
    }

    @Override
    public Expression deepCopy() {
        return new HeapReadingExpression(expression.deepCopy());
    }

    @Override
    public String toString() {
        return "rH(" + expression + ")";
    }
}
