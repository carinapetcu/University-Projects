package model.adt;

import javafx.beans.property.SimpleStringProperty;
import model.values.Value;

public class SymbolTableEntry {
    private final SimpleStringProperty name;
    private final SimpleStringProperty value;
    private final String initialName;
    private final Value initialValue;

    public SymbolTableEntry(String initialName, Value initialValue){
        name = new SimpleStringProperty(String.valueOf(initialName));
        value = new SimpleStringProperty(initialValue.toString());
        this.initialName = initialName;
        this.initialValue = initialValue.deepCopy();
    }

    public String getName(){
        return initialName;
    }

    public Value getValue(){
        return initialValue;
    }
}
