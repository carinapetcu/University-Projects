package model.adt;

import exceptions.MyException;

import java.util.List;
import java.util.NoSuchElementException;
import java.util.Vector;


public class MyList<T> implements MyIList<T>{
    private final List<T> list;

    public MyList(){
        this.list = new Vector<T>();
    }

    @Override
    public void add(T value) {
        list.add(value);
    }

    @Override
    public void remove(T value) throws MyException {
        try{
            list.remove(value);
        } catch(NoSuchElementException exception){
            throw new MyException("The element does not exist in the list!");
        }
    }

    @Override
    public String toString() {
        StringBuilder requiredString = new StringBuilder("[");
        for (T item: list) {
            requiredString.append(item).append("|");
        }
        return requiredString + "]";
    }
}
