package model.values;

import model.types.ReferenceType;
import model.types.Type;

public class ReferenceValue implements Value{
    int address;
    Type locationType;

    public ReferenceValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public int getAddress() {
        return address;
    }

    void setValue(ReferenceValue newReferenceValue){
        address = newReferenceValue.address;
        locationType = newReferenceValue.locationType;
    }

    public Type getLocationType() {
        return locationType;
    }

    @Override
    public Type getType() {
        return new ReferenceType(locationType);
    }

    @Override
    public Value deepCopy() {
        return new ReferenceValue(address, locationType.deepCopy());
    }

    @Override
    public String toString() {
        return "(" + address + ", " + locationType + ")";
    }


}
