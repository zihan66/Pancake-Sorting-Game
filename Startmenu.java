import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Background;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.io.File;

public class Startmenu extends Application{
    Pane splash;
    Button start;
    Image background;
    Scene scene1;
    Stage root;
    ImageView image;
    @Override
    public void start(Stage primaryStage) throws Exception
    {
        root = new Stage();
        start = new Button("start");
        background = new Image(new File("startscreen.jpg").toURI().toURL().toExternalForm());
        image = new ImageView(background);
        splash = new Pane();
        start.setLayoutY(450);
        start.setLayoutX(40);
        start.setMinHeight(150);
        start.setMinWidth(600);
        start.setOnAction(new EventHandler<ActionEvent>() {
                              public void handle(ActionEvent event) {
                                  try {
                                      changeScreen();
                                  } catch (Exception e) {
                                      e.printStackTrace();
                                  }
                              }
                          }
        );

        splash.getChildren().add(image);
        start.setBackground(Background.EMPTY);
        start.setPickOnBounds(true);
        splash.getChildren().add(start);
        scene1 = new Scene(splash,600,600);
        root.setTitle("Pancake Game");
        root.setScene(scene1);
        root.show();
    }

    public void changeScreen(){
        Setup setup = new Setup();
        image.setImage(null);
        splash.getChildren().remove(image);
        setup.start(root);
    }

    public static void main(String[] args) {
        try {
            launch(args);
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }

}
