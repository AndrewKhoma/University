module lab {
    requires javafx.controls;
    requires javafx.fxml;

    opens org.Ahoma to javafx.fxml;
    exports org.Ahoma;
}