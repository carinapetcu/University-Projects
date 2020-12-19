package view;

import controller.Controller;
import exceptions.MyException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import model.adt.*;
import model.statements.Statement;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ProgramExecutorController {
    private final Controller controller;
    private ProgramState lastMainProgram;

    public ProgramExecutorController(Controller controller) {
        this.controller = controller;
        this.lastMainProgram = null;
    }

    @FXML
    private Label programStatesCounterLabel;

    @FXML
    private ListView<Integer> programStatesIdentifiersListView;

    @FXML
    private TableView<HeapEntry> heapTableView;

    @FXML
    private TableColumn<HeapEntry, String> heapAddress;

    @FXML
    private TableColumn<HeapEntry, String> heapValue;

    @FXML
    private TableView<SymbolTableEntry> symbolTableView;

    @FXML
    private TableColumn<SymbolTableEntry, String> variableName;

    @FXML
    private TableColumn<SymbolTableEntry, String> variableValue;

    @FXML
    private ListView<Statement> executionStackListView;

    @FXML
    private ListView<Value> outputListView;

    @FXML
    private ListView<StringValue> fileTableListView;

    @FXML
    public void initialize() {
        programStatesIdentifiersListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        heapTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        heapAddress.setCellValueFactory(new PropertyValueFactory<HeapEntry, String>("address"));
        heapValue.setCellValueFactory(new PropertyValueFactory<HeapEntry, String>("value"));

        symbolTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        variableName.setCellValueFactory(new PropertyValueFactory<SymbolTableEntry, String>("name"));
        variableValue.setCellValueFactory(new PropertyValueFactory<SymbolTableEntry, String>("value"));

        try {
            populate();
        } catch (MyException exception) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Execution Error");
            alert.setHeaderText("An execution error has occured!");
            alert.setContentText(exception.toString());

            alert.showAndWait();

        }

    }

    private void populate() throws MyException{
        List<ProgramState> states = controller.getAllProgramStates();
        ProgramState currentProgramState;
        programStatesCounterLabel.setText("Number of Program States: " + states.size());
        if(states.size() == 0){
            if(lastMainProgram == null){
                throw new MyException("No others executions left!");
            } else {
                currentProgramState = lastMainProgram;
                lastMainProgram = null;
            }
        } else {
            lastMainProgram = currentProgramState = states.get(0);
        }

        populateProgramStateList(states);
        programStatesIdentifiersListView.getSelectionModel().selectIndices(0);
        try{
            populateHeapTableView(currentProgramState);
            populateSymbolTableView(currentProgramState);
            populateExecutionStack(currentProgramState);
            populateOutputList(currentProgramState);
            populateFileTableList(currentProgramState);

        } catch (MyException exception) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Execution Error");
            alert.setHeaderText("An execution error has occured!");
            alert.setContentText(exception.toString());

            alert.showAndWait();

        }

    }

    private void populateProgramStateList(List<ProgramState> states){
        List<Integer> identifiers = states.stream().map(ProgramState::getStateId).collect(Collectors.toList());
        programStatesIdentifiersListView.setItems(FXCollections.observableList(identifiers));
    }

    private void populateExecutionStack(ProgramState currentProgramState){
        MyIStack<Statement> executionStack = currentProgramState.getExecutionStack();
        executionStackListView.setItems(FXCollections.observableList(executionStack.toList()));

    }

    private void populateFileTableList(ProgramState currentProgramState){
        MyIDictionary<StringValue, BufferedReader> fileTableList = currentProgramState.getFileTable();
        List<StringValue> fileNames = new ArrayList<>(fileTableList.getContent().keySet());
        fileTableListView.setItems(FXCollections.observableList(fileNames));
    }

    private void populateOutputList(ProgramState currentProgramState){
        MyIList<Value> outputList = currentProgramState.getOutput();
        List<Value> output = new ArrayList<Value>();
        int index;
        for(index = 0; index < outputList.size(); index++) {
            output.add(outputList.get(index));
        }
        outputListView.setItems(FXCollections.observableArrayList(output));
    }

    private void populateHeapTableView(ProgramState currentProgramState){
        MyIHeap<Value> heap = currentProgramState.getHeap();
        ArrayList<HeapEntry> heapEntries = new ArrayList<HeapEntry>();
        for(Map.Entry<Integer, Value> entry: heap.getContent().entrySet()){
            heapEntries.add(new HeapEntry(entry.getKey(), entry.getValue()));
        }
        heapTableView.setItems(FXCollections.observableArrayList(heapEntries));
    }

    private void populateSymbolTableView(ProgramState currentProgramState){
        MyIDictionary<String, Value> symbolTable = currentProgramState.getSymbolTable();
        ArrayList<SymbolTableEntry> symbolTableEntries = new ArrayList<SymbolTableEntry>();
        for(Map.Entry<String, Value> entry: symbolTable.getContent().entrySet()){
           symbolTableEntries.add(new SymbolTableEntry(entry.getKey(), entry.getValue()));
        }
        symbolTableView.setItems(FXCollections.observableArrayList(symbolTableEntries));
    }

    private ObservableList<Integer> getAllIdentifiers(){
        List<ProgramState> programStates = controller.getAllProgramStates();
        List<Integer> allIdentifiers = programStates.stream().map(ProgramState::getStateId).collect(Collectors.toList());
        return FXCollections.observableArrayList(allIdentifiers);
    }

    @FXML
    private void changeProgramState(MouseEvent event){
        List<ProgramState> states = controller.getAllProgramStates();
        int selectedIndex = programStatesIdentifiersListView.getSelectionModel().getSelectedIndex();
        ProgramState changedProgramState = states.get(selectedIndex);
        try{
            populateExecutionStack(changedProgramState);
            populateSymbolTableView(changedProgramState);
        } catch (MyException exception) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Execution Error");
            alert.setHeaderText("An execution error has occured!");
            alert.setContentText(exception.toString());

            alert.showAndWait();

        }
    }

    @FXML
    private void oneStep(MouseEvent event){
        try {
            List<ProgramState> states = controller.getAllProgramStates();
            if(states.size() > 0 || lastMainProgram != null)
                controller.oneStepOnly();
            populate();
        }  catch (MyException exception) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Execution Error");
            alert.setHeaderText("An execution error has occured!");
            alert.setContentText(exception.toString());

            alert.showAndWait();

        }

    }
}
