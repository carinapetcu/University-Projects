package model.types;

import model.values.BooleanValue;
import model.values.Value;

public class BooleanType implements Type{

    @Override
    public boolean equals(Object another){

        return another instanceof BooleanType;
    }

    @Override
    public String toString(){
        return "boolean";
    }

    @Override
    public Type deepCopy() {
        return new BooleanType();
    }

    @Override
    public Value defaultValue() {
        return new BooleanValue(false);
    }
}
