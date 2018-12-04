import javafx.animation.FadeTransition;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Duration;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Main extends Application {

	private Stage primaryStage;
	private Button r;
	private Button text;
	private Label userName;
	private TextField user_name;
	private Label numberPancake;
	private TextField number_pancake;
	private Label AIDifficulty;
	private TextField AI_diff;
	private Label RandomOr;
	private TextField random;
	private String s = "";
	private GridPane grid;
	private Pane pane;
	private Scene scene;
	private Button btn;
	private Label message;
	private FadeTransition ft;

	public void initialize() {

		pane = new Pane();
		grid = new GridPane();
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(25, 25, 25, 25));

		scene = new Scene(grid, 600, 600);

		userName = new Label("Enter Initial:");
		grid.add(userName, 0, 2);

		user_name = new TextField();
		grid.add(user_name, 1, 2);

		numberPancake = new Label("Enter number of pancakes:");
		grid.add(numberPancake, 0, 3);

		number_pancake = new TextField();
		grid.add(number_pancake, 1, 3);

		AIDifficulty = new Label("Enter AI difficulty");
		grid.add(AIDifficulty, 0, 4);

		AI_diff = new TextField();
		grid.add(AI_diff, 1, 4);

		RandomOr = new Label("Random order ?");
		grid.add(RandomOr, 0, 5);

		r = new Button("Random");
		HBox h = new HBox(5);
		h.getChildren().add(r);
		grid.add(h, 1, 5);

		text = new Button("Self defined");
		HBox h1 = new HBox(5);
		h1.getChildren().add(text);
		grid.add(h1, 2, 5);

	}

	public void set_action() {

		r.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent e) {
				s = "yes";
			}
		});

		text.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent e) {
				random = new TextField();
				grid.add(random, 1, 6);
				// s=random.getText();
				s = "enter";
			}
		});

	}

	public void button_effect() {
		message = new Label("");

		btn = new Button("Continue");
		HBox hbBtn = new HBox(10);
		hbBtn.setAlignment(Pos.BOTTOM_RIGHT);
		hbBtn.getChildren().add(btn);
		grid.add(hbBtn, 5, 7);

		ft = new FadeTransition(Duration.millis(3000), btn);
		ft.setFromValue(1.0);
		ft.setToValue(0.1);
		ft.setCycleCount(Timeline.INDEFINITE);
		ft.setAutoReverse(true);
		ft.play();

	}

	public void start(Stage primaryStage) {
		this.primaryStage = primaryStage;
		primaryStage.setTitle("JavaFX Welcome");

		initialize();

		set_action();

		button_effect();

		btn.setOnAction(new EventHandler<ActionEvent>() {

			public void handle(ActionEvent e) {

				if (user_name.getText().equals("") | number_pancake.getText().equals("")
						| AI_diff.getText().equals("")) {
					message.setText("You need fill everything in blank");
				} else if (Integer.parseInt(number_pancake.getText()) < 2
						| Integer.parseInt(number_pancake.getText()) > 9) {
					message.setText("You can only enter pancakes 2 to 9 ");
				} else if (Integer.parseInt(AI_diff.getText()) > Integer.parseInt(number_pancake.getText())) {
					message.setText("AI difficulty is wrong");
				} else if (!s.equals("yes") && !s.equals("enter")) {
					message.setText("Press either random or self-defined button");
				} else {
					try {
						FileWriter fstream = new FileWriter("setup.txt");
						BufferedWriter writer = new BufferedWriter(fstream);
						writer.write(user_name.getText());
						writer.newLine();
						writer.write(number_pancake.getText());
						writer.newLine();
						writer.write(AI_diff.getText());
						writer.newLine();

						if (s.trim().toLowerCase() == "yes") {
							writer.write("1");
						} else {
							String w = "", s = random.getText();
							for(int i = 0; i < s.length(); i++) {
								w += s.charAt(i) + " ";
							}
							writer.write("0");
							writer.write(w);
						}

						writer.close();

					} catch (IOException e1) {
						e1.printStackTrace();
					}

					File f = new File("pancake.txt");
					File f1 = new File("AIPancake.txt");
					// while(f.isFile() && f1.isFile())
					// {
					// changeScenes();
					// }
					try {
						changeScenes();
					} catch (Exception e1) {
						e1.printStackTrace();
					}
				}

			}
		});
		grid.getChildren().add(message);

		final Text actiontarget = new Text();
		grid.add(actiontarget, 1, 6);
		primaryStage.setScene(scene);
		primaryStage.show();
	}

	private void changeScenes() throws Exception {

		Pancake ci = new Pancake();
		Scene scene1 = ci.s();

		primaryStage.setTitle("login page");
		primaryStage.setScene(scene1);

	}

	public static void main(String[] args) {
		launch();
	}

}
