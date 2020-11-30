package repository;

import exceptions.EmptyRepositoryException;
import exceptions.MyException;
import model.adt.ProgramState;
import model.statements.PrintStatement;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<ProgramState> repository;
    private final String logFilePath;

    public Repository(String logFilePath, ProgramState initialProgramState){
        repository = new ArrayList<>();
        repository.add(initialProgramState);
        this.logFilePath = logFilePath;
    }

    @Override
    public List<ProgramState> getProgramList() {
        return repository;
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


}
