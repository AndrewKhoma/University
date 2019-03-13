package org.Ahoma;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.VBox;

import java.io.IOException;

public class FXMLSecondVarController {
  @FXML public VBox mainWindow;
  @FXML public Slider slider;
  @FXML public Label label;
  @FXML public Button incBtn;
  @FXML public Button decBtn;

  private ConcurrentValue cv;

  @FXML
  public void initialize() {
    slider.setValue(50.0);

    cv = new ConcurrentValue(slider);
  }

  @FXML
  public void loadFirst() throws IOException {
    mainWindow
        .getChildren()
        .setAll((Node) FXMLLoader.load(getClass().getResource("firstVar.fxml")));
  }

  @FXML
  private void startFirst() {
    cv.setDecIsRunning(true);
    int semaphore = cv.getSemaphore();
    if (semaphore == 1) {
      label.setText("First is still running");
    } else if (semaphore == 2) {
      label.setText("Second is still running");
    } else {
      decBtn.setDisable(false);
      incBtn.setDisable(true);
      cv.startDec();
      cv.setSemaphore(1);
      cv.setPriorityToDec(Thread.MIN_PRIORITY);
      label.setText("First is running");
    }
  }

  @FXML
  private void startSecond() {
    cv.setIncIsRunning(true);
    int semaphore = cv.getSemaphore();
    if (semaphore == 1) {
      label.setText("First is still running");
    } else if (semaphore == 2) {
      label.setText("Second is still running");
    } else {
      incBtn.setDisable(false);
      decBtn.setDisable(true);
      cv.startInc();
      cv.setSemaphore(2);
      cv.setPriorityToInc(Thread.MAX_PRIORITY);
      label.setText("Second is running");
    }
  }

  @FXML
  private void stopFirst() {
    incBtn.setDisable(false);
    cv.setSemaphore(0);
    cv.setDecIsRunning(false);
    label.setText("Stop");
  }

  @FXML
  private void stopSecond() {
    decBtn.setDisable(false);
    cv.setSemaphore(0);
    cv.setIncIsRunning(false);
    label.setText("Stop");
  }

  @FXML
  public void quitApplication() {
    Platform.exit();
  }
}
