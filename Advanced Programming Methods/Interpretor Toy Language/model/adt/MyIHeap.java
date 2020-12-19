package model.adt;

import exceptions.MyException;

import java.util.Map;

public interface MyIHeap<V> {
    int allocate(V value);
    V lookup(int address);
    boolean isDefined(int address);
    void update(int address, V value);
    void deallocate(int address) throws MyException;
    Map<Integer,V> getContent();
    void setContent(Map<Integer, V> content);

}
