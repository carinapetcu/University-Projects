package repository;

import exceptions.MyException;
import model.adt.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<ProgramState> repository;
    private final String logFilePath;
    private final ProgramState initialProgramState;

    public Repository(String logFilePath, ProgramState initialProgramState){
        repository = new ArrayList<>();
        this.initialProgramState = initialProgramState;
        repository.add(initialProgramState);
        this.logFilePath = logFilePath;
    }

    @Override
    public List<ProgramState> getProgramList() {
        return repository;
    }

    @Override
    public ProgramState getInitialProgramState(){
        return initialProgramState;
    }

    @Override
    public void setProgramList(List<ProgramState> newList) {
        repository = newList;
    }

    @Override
    public void logProgramStateExecution(ProgramState programState) throws MyException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath.strip(), true)));
            logFile.write(programState + "\n\n");
            logFile.close();

        } catch(IOException exception){
            throw new MyException(exception.getMessage());
        }
    }

    @Override
    public String toString(){
        return initialProgramState.getOriginalProgram().toString();
    }


}
