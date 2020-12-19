package model.adt;

import exceptions.EmptyExecutionStackException;
import exceptions.MyException;
import model.statements.Statement;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.util.concurrent.atomic.AtomicInteger;

public class ProgramState {
    private final MyIStack<Statement> executionStack;
    private final MyIDictionary<String, Value> symbolTable;
    private final MyIList<Value> output;
    private final MyIDictionary<StringValue, BufferedReader> fileTable;
    private final Statement originalProgram;
    private final MyIHeap<Value> heap;
    private int stateId;
    private static AtomicInteger lastId = new AtomicInteger(0);

    public ProgramState(MyIStack<Statement> executionStack, MyIDictionary<String, Value> symbolTable,
                        MyIList<Value> output, MyIDictionary<StringValue, BufferedReader> fileTable, MyIHeap<Value> heap,
                        Statement program) {
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.output = output;
        this.fileTable = fileTable;
        this.executionStack.push(program);
        this.originalProgram = program;
        this.heap = heap;
        this.stateId = lastId.incrementAndGet();
    }

    public static ProgramState empty(Statement program){
        return new ProgramState(new MyStack<Statement>(),
                new MyDictionary<String, Value>(),
                new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<>(), program);
    }

    public MyIStack<Statement> getExecutionStack() {
        return executionStack;
    }

    public MyIDictionary<String, Value> getSymbolTable() {
        return symbolTable;
    }

    public MyIList<Value> getOutput() {
        return output;
    }

    public Statement getOriginalProgram() {
        return originalProgram;
    }

    public MyIHeap<Value> getHeap() {
        return heap;
    }

    public int getStateId() {
        return stateId;
    }

    public MyIDictionary<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public Boolean isNotCompleted(){
        return !executionStack.isEmpty();
    }

    public ProgramState oneStepExecution() throws MyException {
        if(executionStack.isEmpty()){
            throw new EmptyExecutionStackException("The program state stack is empty!");
        }
        Statement currentStatement = executionStack.pop();
        return currentStatement.execute(this);
    }

    @Override
    public String toString() {
        String content = "---- Program state ----";
        content += "\nThread number: " + stateId;
        content += "\nStack: " + executionStack.toString();
        content += "\nHeap: " + heap.toString();
        content += "\nSymbolTable: " + symbolTable.toString();
        content += "\nOutput: " + output.toString();
        content += "\nFileTable: " + fileTable.toString();
        return content;
    }
}
