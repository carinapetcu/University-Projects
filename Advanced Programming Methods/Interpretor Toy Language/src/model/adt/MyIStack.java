package model.adt;

import exceptions.MyException;

public interface MyIStack<T> {
    T pop() throws MyException;
    void push(T value);
    boolean isEmpty();
}
