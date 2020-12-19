package model.values;

import model.types.BooleanType;
import model.types.Type;

public class BooleanValue implements Value{
    private boolean value;

    public BooleanValue(){
        value = false;
    }

    public BooleanValue(boolean value){
        this.value = value;
    }

    public boolean getValue(){
        return value;
    }

    void setValue(BooleanValue newValue){
        value = newValue.value;
    }

    @Override
    public boolean equals(Object another){
        if(this == another)
            return true;
        if(another == null || getClass() != another.getClass())
            return false;
        BooleanValue newValue = (BooleanValue)another;
        return newValue.value == value;

    }

    @Override
    public String toString(){
        return String.valueOf(value);
    }

    @Override
    public Type getType(){
        return new BooleanType();
    }

    @Override
    public Value deepCopy() {
        return new BooleanValue(value);
    }
}
