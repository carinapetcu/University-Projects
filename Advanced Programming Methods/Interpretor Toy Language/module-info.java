module AssignmentGUI {
    requires javafx.graphics;
    requires javafx.fxml;
    requires javafx.controls;
    requires javafx.base;

    opens view;
    opens model.adt;
}
