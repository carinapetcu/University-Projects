package view;

import controller.Controller;
import exceptions.MyException;
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
import repository.IRepository;
import repository.Repository;

public class Interpretor {
    public static void main(String[] args){
        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));

        Statement example1 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));
        try{
            example1.typeCheck(new MyDictionary<>());
            ProgramState programState1 = ProgramState.empty(example1);
            IRepository repository1 = new Repository("log1.txt", programState1);
            Controller controller1 = new Controller(repository1);
            menu.addCommand(new RunExample("1", example1.toString(), controller1));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }


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
        try{
            example2.typeCheck(new MyDictionary<>());
            ProgramState programState2 = ProgramState.empty(example2);
            IRepository repository2 = new Repository("log2.txt", programState2);
            Controller controller2 = new Controller(repository2);
            menu.addCommand(new RunExample("2", example2.toString(), controller2));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example3 = new CompoundStatement(new VariableDeclarationStatement("a", new BooleanType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BooleanValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"),
                                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignmentStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));
        try{
            example3.typeCheck(new MyDictionary<>());
            ProgramState programState3 = ProgramState.empty(example3);
            IRepository repository3 = new Repository("log3.txt", programState3);
            Controller controller3 = new Controller(repository3);
            menu.addCommand(new RunExample("3", example3.toString(), controller3));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example4 = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompoundStatement(new OpenRFileStatement(new VariableExpression("varf")),
                                new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                                        new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                        new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseRFileStatement(new VariableExpression("varf"))))))))));
        try{
            example4.typeCheck(new MyDictionary<>());
            ProgramState programState4 = ProgramState.empty(example4);
            IRepository repository4 = new Repository("log4.txt", programState4);
            Controller controller4 = new Controller(repository4);
            menu.addCommand(new RunExample("4", example4.toString(), controller4));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example5 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new IntValue(5))),
                                new CompoundStatement(new AssignmentStatement("b", new ValueExpression(new IntValue(7))),
                                        new IfStatement(new RelationalExpression(">", new VariableExpression("a"),
                                                        new VariableExpression("b")),new PrintStatement(new VariableExpression("a")),
                                                new PrintStatement(new VariableExpression("b")))))));
        try{
            example5.typeCheck(new MyDictionary<>());
            ProgramState programState5 = ProgramState.empty(example5);
            IRepository repository5 = new Repository("log5.txt", programState5);
            Controller controller5 = new Controller(repository5);
            menu.addCommand(new RunExample("5", example5.toString(), controller5));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example6 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a",new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));
        try{
            example6.typeCheck(new MyDictionary<>());
            ProgramState programState6 = ProgramState.empty(example6);
            IRepository repository6 = new Repository("log6.txt", programState6);
            Controller controller6 = new Controller(repository6);
            menu.addCommand(new RunExample("6", example6.toString(), controller6));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example7 = new CompoundStatement(new VariableDeclarationStatement("v",new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression(1,
                                                        new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))),
                                                        new ValueExpression(new IntValue(5)))))))));
        try{
            example7.typeCheck(new MyDictionary<>());
            ProgramState programState7 = ProgramState.empty(example7);
            IRepository repository7 = new Repository("log7.txt", programState7);
            Controller controller7 = new Controller(repository7);
            menu.addCommand(new RunExample("7", example7.toString(), controller7));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example8 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                new CompoundStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression(1,new HeapReadingExpression(new VariableExpression("v")),
                                                new ValueExpression(new IntValue(5))))))));
        try{
            example8.typeCheck(new MyDictionary<>());
            ProgramState programState8 = ProgramState.empty(example8);
            IRepository repository8 = new Repository("log8.txt", programState8);
            Controller controller8 = new Controller(repository8);
            menu.addCommand(new RunExample("8", example8.toString(), controller8));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example9 = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a")))))))));
        try{
            example9.typeCheck(new MyDictionary<>());
            ProgramState programState9 = ProgramState.empty(example9);
            IRepository repository9 = new Repository("log9.txt", programState9);
            Controller controller9 = new Controller(repository9);
            menu.addCommand(new RunExample("9", example9.toString(), controller9));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        Statement example10 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                        new CompoundStatement(new WhileStatement(
                                new RelationalExpression(">", new VariableExpression("v"), new ValueExpression(new IntValue(0))),
                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                        new AssignmentStatement("v", new ArithmeticExpression(2,
                                                new VariableExpression("v"), new ValueExpression(new IntValue(1)))))),
                                new PrintStatement(new VariableExpression("v")))));
        try{
            example10.typeCheck(new MyDictionary<>());
            ProgramState programState10 = ProgramState.empty(example10);
            IRepository repository10 = new Repository("log10.txt", programState10);
            Controller controller10 = new Controller(repository10);
            menu.addCommand(new RunExample("10", example10.toString(), controller10));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

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

        try{
            example11.typeCheck(new MyDictionary<>());
            ProgramState programState11 = ProgramState.empty(example11);
            IRepository repository11 = new Repository("log11.txt", programState11);
            Controller controller11 = new Controller(repository11);
            menu.addCommand(new RunExample("11", example11.toString(), controller11));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        // example for typechecking, it returns an error since it tries to assign an int value to my boolean variable
        // bool v; v = 40;
        Statement example12 = new CompoundStatement(new VariableDeclarationStatement("v", new BooleanType()),
                new AssignmentStatement("v", new ValueExpression(new IntValue(40))));
        try{
            example12.typeCheck(new MyDictionary<>());
            ProgramState programState12 = ProgramState.empty(example12);
            IRepository repository12 = new Repository("log12.txt", programState12);
            Controller controller12 = new Controller(repository12);
            menu.addCommand(new RunExample("12", example12.toString(), controller12));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

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
        try{
            example13.typeCheck(new MyDictionary<>());
            ProgramState programState13 = ProgramState.empty(example13);
            IRepository repository13 = new Repository("log13.txt", programState13);
            Controller controller13 = new Controller(repository13);
            menu.addCommand(new RunExample("13", example13.toString(), controller13));
        } catch(MyException exception){
            System.out.println(exception.getMessage());
        }

        menu.show();

    }
}
