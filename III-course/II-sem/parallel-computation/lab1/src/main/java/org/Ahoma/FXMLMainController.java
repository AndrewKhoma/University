package org.Ahoma;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.layout.VBox;

import java.io.IOException;

public class FXMLMainController {
  @FXML public VBox MainWindow;

  public void loadFirst() throws IOException {
    MainWindow.getChildren()
        .setAll((Node) FXMLLoader.load(getClass().getResource("firstVar.fxml")));
  }

  public void loadSecond() throws IOException {
    MainWindow.getChildren()
        .setAll((Node) FXMLLoader.load(getClass().getResource("secondVar.fxml")));
  }

  public void quitApplication() {
    Platform.exit();
  }
}
