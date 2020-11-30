package controller;

import exceptions.EmptyExecutionStackException;
import exceptions.MyException;
import model.adt.MyIStack;
import model.adt.ProgramState;
import model.statements.Statement;
import model.types.ReferenceType;
import model.values.ReferenceValue;
import model.values.Value;
import repository.IRepository;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    IRepository repository;
    ExecutorService executor;

    public Controller(IRepository repository){
        this.repository = repository;
    }

    public Map<Integer, Value> garbageCollector(List<Integer> symbolTableAddresses, Map<Integer, Value> heap){
        return heap.entrySet()
                .stream()
                .filter(e->symbolTableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    List<Integer> getAllAddressesAllSymbolTables(List<ProgramState> programStates){
        List<Integer> addressesList = new LinkedList<>();
        programStates.forEach(state -> addressesList.addAll(getAllValidAddresses
                (getAddressFromSymbolTable(state.getSymbolTable().getContent().values()), state.getHeap().getContent())));
        return addressesList;
    }

    public void garbageCollectorAll(List<ProgramState> programStates){
        List<Integer> addresses = getAllAddressesAllSymbolTables(programStates);
        programStates.forEach(state -> state.getHeap().setContent(garbageCollector(addresses, state.getHeap().getContent())));
    }

    List<Integer> getAllValidAddresses(List<Integer> symbolTableAddresses, Map<Integer, Value> heap) {
        var heapEntrySet = heap.entrySet();
        LinkedList<Integer> addressesList = new LinkedList<Integer>(symbolTableAddresses);

        boolean filteredAll = false;
        while (!filteredAll) {
            filteredAll = true;
            List <Integer> currentAddresses = heapEntrySet.stream()
                    .filter(entry -> addressesList.contains(entry.getKey()))
                    .filter(entry -> entry.getValue() instanceof ReferenceValue)
                    .map(entry -> {ReferenceValue value = (ReferenceValue) entry.getValue();
                        return value.getAddress();})
                    .filter(entry -> !addressesList.contains(entry))
                    .collect(Collectors.toList());

            if (!currentAddresses.isEmpty()) {
                addressesList.addAll(currentAddresses);
                filteredAll = false;
            }
        }
        return addressesList;
    }


    public List<Integer> getAddressFromSymbolTable(Collection<Value> symbolTableValues){
        return symbolTableValues.stream()
                .filter(value->value instanceof ReferenceValue)
                .map(value->{ReferenceValue value1 = (ReferenceValue)value; return value1.getAddress();})
                .collect(Collectors.toList());
    }

    public List<ProgramState> removeCompletedPrograms(List<ProgramState> inputProgramList){
        return inputProgramList.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrograms(List<ProgramState> programStates)
    {
        programStates.forEach(programState -> {
            try {
                repository.logProgramStateExecution(programState);
            } catch (IOException exception) {
                exception.printStackTrace();
            }
        });

        List<Callable<ProgramState>> callableList = programStates.stream()
                .map((ProgramState programState) -> (Callable<ProgramState>) programState::oneStepExecution)
                .collect(Collectors.toList());

        List<ProgramState> newProgramList = null;
        try{
            newProgramList = executor.invokeAll(callableList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        } catch (InterruptedException | ExecutionException exception) {
                            exception.printStackTrace();
                        }
                        return null; })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());

        } catch(MyException | InterruptedException exception) {
            throw new MyException(exception.getMessage());
        }

        programStates.addAll(newProgramList);

        programStates.forEach(programState -> {
            try {
                repository.logProgramStateExecution(programState);
            } catch (IOException exception) {
                exception.printStackTrace();
            }
        });
        repository.setProgramList(programStates);

    }

    public void allStep(){
        executor = Executors.newFixedThreadPool(2);

        List<ProgramState> programStateList = removeCompletedPrograms(repository.getProgramList());
        while(programStateList.size() > 0){
            oneStepForAllPrograms(programStateList);
            garbageCollectorAll(programStateList);
            programStateList = removeCompletedPrograms(repository.getProgramList());
        }

        executor.shutdownNow();
        repository.setProgramList(programStateList);
    }

    @Override
    public String toString() {
        try {
            return repository.toString();
        } catch (MyException exception) {
            exception.printStackTrace();
        }
        return null;
    }
}
