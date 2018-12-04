import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.scene.layout.Pane;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;
import java.util.Scanner;
import java.io.*;

import javafx.stage.*;
import javafx.scene.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.geometry.*;

import javafx.scene.*;
import javafx.scene.paint.*;
import javafx.scene.shape.*;
import java.lang.Math;

public class highScores extends Application {

	Button foodButton;
	String message;
	Stage root;

	@Override
	public void start(Stage primaryStage) throws IOException {

		root = primaryStage;
		Scanner file = new Scanner(new File("scores.txt"));

		primaryStage.setTitle("Final Stage");

		Rectangle r = new Rectangle();
		r.setX(0);
		r.setY(0);
		r.setWidth(600);
		r.setHeight(600);
		Text t = new Text(170, 50, "High Scores");
		t.setFill(Color.RED);
		t.setFont(new Font(50));

		Text a = new Text(270, 100, "1. " + file.nextLine());
		a.setFill(Color.RED);
		Text b = new Text(270, 130, "2. " + file.nextLine());
		b.setFill(Color.RED);
		Text c = new Text(270, 160, "3. " + file.nextLine());
		c.setFill(Color.RED);
		Text d = new Text(270, 190, "4. " + file.nextLine());
		d.setFill(Color.RED);
		Text e = new Text(270, 220, "5. " + file.nextLine());
		e.setFill(Color.RED);

		Text f = new Text(220, 330, "Play Again?");
		f.setFill(Color.RED);
		f.setFont(new Font(30));

		Text m = new Text(200, 260, message);
		m.setFill(Color.RED);
		m.setFont(new Font(20));

		Button yesButton = new Button("Yes");
		yesButton.setLayoutX(260);
		yesButton.setLayoutY(400);

		Button noButton = new Button("No");
		noButton.setLayoutX(310);
		noButton.setLayoutY(400);

		String str = "";

		yesButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) {
				try {
					FileWriter file = new FileWriter("PlayAgain.txt");
					file.write("1");
					file.close();
					Setup setup = new Setup();
					setup.start(root);
				} catch (IOException e1) {
					e1.printStackTrace();
				}

			}
		});

		noButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) {
				try {
					FileWriter file = new FileWriter("PlayAgain.txt");
					file.write("0");
					file.close();
					primaryStage.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}
		});

		// TODO add button action

		Group g = new Group();
		g.getChildren().add(r);
		g.getChildren().add(t);
		g.getChildren().add(a);
		g.getChildren().add(b);
		g.getChildren().add(c);
		g.getChildren().add(d);
		g.getChildren().add(e);
		g.getChildren().add(f);
		g.getChildren().add(m);
		g.getChildren().add(yesButton);
		g.getChildren().add(noButton);

		Scene scene1 = new Scene(g, 600, 600);
		primaryStage.setScene(scene1);
		primaryStage.show();

	}

	public void setname(String name) {
		message = name;
	}

}