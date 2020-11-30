package model.adt;

import exceptions.MyException;
import java.io.BufferedReader;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MyDictionary<K, V> implements MyIDictionary<K, V>{
    private Map<K,V> map;

    public MyDictionary(){
        this.map = new ConcurrentHashMap<K, V>();
    }

    @Override
    public void remove(K key) throws MyException {
        if(!map.containsKey(key))
            throw new MyException("The key does not exist!");
        map.remove(key);
    }

    @Override
    public Map<K, V> getContent() {
        return map;
    }

    @Override
    public void setContent(Map<K, V> content) {
        map = content;
    }

    @Override
    public V lookup(K key) {
        return map.get(key);
    }

    @Override
    public boolean isDefined(K key) {
        return map.containsKey(key);
    }

    @Override
    public void update(K key, V value) {
        map.put(key, value);
    }

    @Override
    public MyIDictionary<K, V> deepCopy() {
        HashMap<K, V> newMap = new HashMap<K, V>(map);
        MyDictionary<K, V> newDictionary = new MyDictionary<K, V>();
        newDictionary.setContent(newMap);
        return newDictionary;
    }

    @Override
    public String toString() {
        StringBuilder requiredString = new StringBuilder();
        for (HashMap.Entry<K, V> entry : map.entrySet()) {
            if(entry.getValue() instanceof BufferedReader) {
                requiredString.append("(")
                        .append(entry.getKey())
                        .append(")")
                        .append(", ");
            }
            else
            {
                requiredString.append("(")
                        .append(entry.getKey())
                        .append("->")
                        .append(entry.getValue())
                        .append(")")
                        .append(", ");
            }
        }
        return requiredString.toString();
    }
}
