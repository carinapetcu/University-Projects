package model.adt;

import exceptions.MyException;

public interface MyIList<T> {
    void add(T value);
    void remove(T value) throws MyException;
}
