package model.values;

import model.types.IntType;
import model.types.Type;

public class IntValue implements Value{
    private int value;

    public IntValue(){
        this.value = 0;
    }

    public IntValue(int value){

        this.value = value;
    }

    public int getValue(){
        return value;
    }

    public void setValue(IntValue newIntValue){
        value = newIntValue.value;
    }

    @Override
    public boolean equals(Object another){
        if(this == another)
            return true;
        if(another == null || getClass() != another.getClass())
            return false;
        IntValue newValue = (IntValue)another;
        return newValue.value == value;

    }

    @Override
    public String toString(){
        return String.valueOf(value);
    }

    @Override
    public Type getType(){
        return new IntType();
    }

    @Override
    public Value deepCopy() {
        return new IntValue(value);
    }

}
