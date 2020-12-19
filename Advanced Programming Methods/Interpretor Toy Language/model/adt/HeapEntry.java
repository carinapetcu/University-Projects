package model.adt;

import javafx.beans.property.SimpleStringProperty;
import model.values.Value;

public class HeapEntry {
    private final SimpleStringProperty address;
    private final SimpleStringProperty value;
    private final int initialAddress;
    private final Value initialValue;

    public HeapEntry(int initialAddress, Value initialValue){
        address = new SimpleStringProperty(String.valueOf(initialAddress));
        value = new SimpleStringProperty(initialValue.toString());
        this.initialAddress = initialAddress;
        this.initialValue = initialValue;
    }

    public int getAddress(){
        return initialAddress;
    }

    public Value getValue(){
        return initialValue;
    }
}
