package model.adt;

import exceptions.MyException;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class MyHeap<V> implements MyIHeap<V>{
    private Map<Integer,V> heap;
    private final AtomicInteger newFreeLocation;

    public MyHeap() {
        this.heap = new ConcurrentHashMap<Integer, V>();
        this.newFreeLocation = new AtomicInteger(0);
    }


    @Override
    public int allocate(V value) {
        int freeLocation = newFreeLocation.incrementAndGet();
        heap.put(freeLocation, value);
        return freeLocation;
    }

    @Override
    public V lookup(int address) {
        return heap.get(address);
    }

    @Override
    public boolean isDefined(int address) {
        return heap.containsKey(address);
    }

    @Override
    public void update(int address, V value) {
        heap.put(address, value);
    }

    @Override
    public void deallocate(int address) throws MyException {
        if(!heap.containsKey(address))
            throw new MyException("The address was not allocated on the heap!");
        heap.remove(address);
    }

    @Override
    public Map<Integer, V> getContent() {
        return heap;
    }

    @Override
    public void setContent(Map<Integer, V> content) {
        heap = content;
    }

    @Override
    public String toString() {
        StringBuilder requiredString = new StringBuilder();

        for (HashMap.Entry<Integer, V> entry : heap.entrySet()) {
            requiredString.append("(")
                        .append(entry.getKey())
                        .append("->")
                        .append(entry.getValue())
                        .append(")")
                        .append(", ");
        }
        return requiredString.toString();
    }
}
