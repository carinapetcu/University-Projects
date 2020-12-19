package repository;

import exceptions.MyException;
import model.adt.ProgramState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    void logProgramStateExecution(ProgramState programState) throws MyException, IOException;
    List<ProgramState> getProgramList();
    void setProgramList(List<ProgramState> newList);
    ProgramState getInitialProgramState();
}
