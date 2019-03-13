package org.Ahoma;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.Spinner;
import javafx.scene.control.SpinnerValueFactory;
import javafx.scene.layout.VBox;

import java.io.IOException;

public class FXMLFirstVarController {
  @FXML public VBox mainWindow;
  @FXML public Spinner<Integer> firstThreadPriority;
  @FXML public Spinner<Integer> secondThreadPriority;
  @FXML public Slider slider;
  @FXML public Label sliderValue;

  private Thread firstThread, secondThread;

  public void initialize() {
    firstThreadPriority.setValueFactory(
        new SpinnerValueFactory.IntegerSpinnerValueFactory(1, 10, 5));
    secondThreadPriority.setValueFactory(
        new SpinnerValueFactory.IntegerSpinnerValueFactory(1, 10, 5));

    slider
        .valueProperty()
        .addListener(
            (observable, oldValue, newValue) ->
                sliderValue.setText(String.format("%.2f", newValue)));

    slider.setValue(50.0);

    firstThread =
        new Thread(
            () -> {
              while (true) {
                synchronized (slider) {
                  Platform.runLater(() -> slider.setValue(10.0));
                }

                try {
                  Thread.sleep(10);
                } catch (InterruptedException ex) {
                  ex.printStackTrace();
                }
              }
            });

    secondThread =
        new Thread(
            () -> {
              while (true) {
                synchronized (slider) {
                  Platform.runLater(() -> slider.setValue(90.0));
                }

                try {
                  Thread.sleep(10);
                } catch (InterruptedException ex) {
                  ex.printStackTrace();
                }
              }
            });

    firstThread.setDaemon(true);
    secondThread.setDaemon(true);

    firstThreadPriority
        .valueProperty()
        .addListener((observable, oldValue, newValue) -> firstThread.setPriority(newValue));

    secondThreadPriority
        .valueProperty()
        .addListener((observable, oldValue, newValue) -> secondThread.setPriority(newValue));
  }

  public void loadSecond() throws IOException {
    mainWindow
        .getChildren()
        .setAll((Node) FXMLLoader.load(getClass().getResource("secondVar.fxml")));
  }

  public void startTreads() {
    firstThread.start();
    secondThread.start();
  }

  public void quitApplication() {
    Platform.exit();
  }
}
