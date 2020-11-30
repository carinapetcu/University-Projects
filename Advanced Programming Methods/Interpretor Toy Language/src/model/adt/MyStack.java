package model.adt;

import exceptions.MyException;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Stack;

public class MyStack<T> implements MyIStack<T>{
    private final Deque<T> stack;

    public MyStack(){
        this.stack = new ArrayDeque<T>();
    }
    @Override
    public T pop() throws MyException {
        if(stack.size() == 0) {
            throw new MyException("The stack is empty!");
        }
        return (T)stack.pop();
    }

    @Override
    public void push(T value) {
        stack.push(value);
    }

    @Override
    public boolean isEmpty() {
        return (stack.size() == 0);
    }

    @Override
    public String toString() {
        StringBuilder requiredString = new StringBuilder();
        for (T item: stack) {
            requiredString.append(item).append("|");
        }
        return requiredString.toString();
    }
}
