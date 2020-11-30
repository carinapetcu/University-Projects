package model.values;

import model.types.StringType;
import model.types.Type;

import java.util.Objects;

public class StringValue implements Value{

    private String value;

    public StringValue(){
        this.value = "";
    }

    public StringValue(String value){

        this.value = value;
    }

    public String getValue(){
        return value;
    }

    public void setValue(StringValue newValue){
        value = newValue.value;
    }
    @Override
    public boolean equals(Object another){
        if(this == another)
            return true;
        if(another == null || getClass() != another.getClass())
            return false;
        StringValue newValue = (StringValue)another;
        return Objects.equals(value, newValue.value);

    }

    @Override
    public String toString(){
        return value;
    }
    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public Value deepCopy() {
        return new StringValue(value);
    }
}
