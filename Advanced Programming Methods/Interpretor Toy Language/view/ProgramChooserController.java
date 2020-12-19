package view;

import controller.Controller;
import exceptions.MyException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import model.adt.MyDictionary;
import model.adt.ProgramState;
import model.expressions.*;
import model.statements.*;
import model.types.BooleanType;
import model.types.IntType;
import model.types.ReferenceType;
import model.types.StringType;
import model.values.BooleanValue;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;
import repository.IRepository;
import repository.Repository;

import java.util.LinkedList;

public class ProgramChooserController {
    @FXML
    private ListView<Statement> programsListView;

    @FXML
    private Button programChooserButton;

    @FXML
    public void initialize() {
        programsListView.setItems(getAllStatements());
        programsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }

    @FXML
    private void startProgram(ActionEvent event){
        Statement currentStatement = programsListView.getSelectionModel().getSelectedItem();
        int identifier = programsListView.getSelectionModel().getSelectedIndex();
        try{
            currentStatement.typeCheck(new MyDictionary<>());
            ProgramState programState = ProgramState.empty(currentStatement);
            IRepository repository = new Repository("log" + ( identifier + 1 ) + ".txt", programState);
            Controller currentController = new Controller(repository);

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("programExecutor.fxml"));
            ProgramExecutorController executorController = new ProgramExecutorController(currentController);
            loader.setController(executorController);
            StackPane executorRoot = (StackPane) loader.load();
            Scene executorScene = new Scene(executorRoot, 750, 500);
            executorScene.getStylesheets().add(getClass().getResource("style.css").toExternalForm());
            Stage executorStage = new Stage();
            executorStage.setScene(executorScene);
            executorStage.setTitle("Program Execution");
            executorStage.show();

        } catch(Exception exception){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error encountered");
            alert.setContentText(exception.getMessage());
            alert.showAndWait();
        }

    }

    private ObservableList<Statement> getAllStatements(){
        LinkedList<Statement> allStatements = new LinkedList<>();
        Statement example1 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));
        allStatements.add(example1);

        Statement example2 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new AssignmentStatement("a",
                                new ArithmeticExpression(1, new ValueExpression(new IntValue(2)),
                                        new ArithmeticExpression(3, new ValueExpression(new IntValue(3)),
                                                new ValueExpression(new IntValue(2))))),
                                new CompoundStatement(new AssignmentStatement("b",
                                        new ArithmeticExpression(1, new VariableExpression("a"),
                                                new ValueExpression(new IntValue(1)))), new PrintStatement(
                                        new VariableExpression("b"))))));
        allStatements.add(example2);

        Statement example3 = new CompoundStatement(new VariableDeclarationStatement("a", new BooleanType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BooleanValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"),
                                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignmentStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));
        allStatements.add(example3);

        Statement example4 = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompoundStatement(new OpenRFileStatement(new VariableExpression("varf")),
                                new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                                        new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                        new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseRFileStatement(new VariableExpression("varf"))))))))));
        allStatements.add(example4);

        Statement example5 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new IntValue(5))),
                                new CompoundStatement(new AssignmentStatement("b", new ValueExpression(new IntValue(7))),
                                        new IfStatement(new RelationalExpression(">", new VariableExpression("a"),
                                                new VariableExpression("b")),new PrintStatement(new VariableExpression("a")),
                                                new PrintStatement(new VariableExpression("b")))))));

        allStatements.add(example5);


        Statement example6 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a",new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));
        allStatements.add(example6);


        Statement example7 = new CompoundStatement(new VariableDeclarationStatement("v",new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression(1,
                                                        new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))),
                                                        new ValueExpression(new IntValue(5)))))))));
        allStatements.add(example7);


        Statement example8 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                new CompoundStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression(1,new HeapReadingExpression(new VariableExpression("v")),
                                                new ValueExpression(new IntValue(5))))))));
        allStatements.add(example8);


        Statement example9 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a")))))))));
        allStatements.add(example9);


        Statement example10 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                        new CompoundStatement(new WhileStatement(
                                new RelationalExpression(">", new VariableExpression("v"), new ValueExpression(new IntValue(0))),
                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                        new AssignmentStatement("v", new ArithmeticExpression(2,
                                                new VariableExpression("v"), new ValueExpression(new IntValue(1)))))),
                                new PrintStatement(new VariableExpression("v")))));
        allStatements.add(example10);


        Statement example11 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                        new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(new ForkStatement(
                                                new CompoundStatement(new HeapWritingStatement("a", new ValueExpression(new IntValue(30))),
                                                        new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                                        new PrintStatement(new HeapReadingExpression(new VariableExpression("a"))))))),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                        new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))))))));

        allStatements.add(example11);


        // example for typechecking, it returns an error since it tries to assign an int value to my boolean variable
        // bool v; v = 40;
        Statement example12 = new CompoundStatement(new VariableDeclarationStatement("v", new BooleanType()),
                new AssignmentStatement("v", new ValueExpression(new IntValue(40))));
        allStatements.add(example12);

        Statement example13 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                        new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(new ForkStatement(
                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                        new CompoundStatement(new HeapWritingStatement("a", new ValueExpression(new IntValue(30))),
                                                                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                                                new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))))))),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                        new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))))))));
        allStatements.add(example13);

        Statement example14 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                                        new CompoundStatement(
                                                new ForkStatement(
                                                        new CompoundStatement(
                                                                new ForkStatement(
                                                                        new CompoundStatement(new ForkStatement(new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v", new ValueExpression(new IntValue(5))))),
                                                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v", new ValueExpression(new IntValue(6)))))),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignmentStatement("v", new ValueExpression(new IntValue(7)))))),
                                                new PrintStatement(new VariableExpression("v")))));
        allStatements.add(example14);

        return FXCollections.observableArrayList(allStatements);
    }
}
