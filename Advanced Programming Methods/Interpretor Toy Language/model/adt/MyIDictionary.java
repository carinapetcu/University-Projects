package model.adt;

import exceptions.MyException;

import java.util.Map;

public interface MyIDictionary<K, V> {
    V lookup(K key);
    boolean isDefined(K key);
    void update(K key, V value);
    void remove(K key) throws MyException;
    Map<K, V> getContent();
    void setContent(Map<K, V> content);
    MyIDictionary<K, V> deepCopy();
}
