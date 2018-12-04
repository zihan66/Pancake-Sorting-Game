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

	public  void start(Stage primaryStage)
	{     
		this.primaryStage = primaryStage;
		  primaryStage.setTitle("JavaFX Welcome");
		         
		Pane pane = new Pane();
		GridPane grid =new GridPane();
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(25,25,25,25));
		
		Scene scene = new Scene(grid,600,600);    
		
	
		Label userName = new Label("Enter Initial:");
		grid.add(userName, 0, 1);

		TextField user_name = new TextField();
		grid.add(user_name, 1, 1);

		Label numberPancake = new Label("Enter number of pancakes:");
		grid.add(numberPancake, 0, 2);

		TextField number_pancake = new TextField();
		grid.add(number_pancake, 1, 2);
		
		Label AIDifficulty = new Label("Enter AI difficulty");
		grid.add(AIDifficulty, 0, 3);

		TextField AI_diff = new TextField();
		grid.add(AI_diff, 1, 3);
		
		Label RandomOr = new Label("Random order?");
		grid.add(RandomOr, 0, 4);

		TextField random = new TextField();
		grid.add(random, 1, 4);
	
		final Label message = new Label("");
		
		Button btn = new Button("Continue");
		HBox hbBtn = new HBox(10);
		hbBtn.setAlignment(Pos.BOTTOM_RIGHT);
		hbBtn.getChildren().add(btn);
		grid.add(hbBtn, 2, 5);
		
	
		FadeTransition ft = new FadeTransition(Duration.millis(3000), btn);
		ft.setFromValue(1.0);
		ft.setToValue(0.1);
		ft.setCycleCount(Timeline.INDEFINITE);
		ft.setAutoReverse(true);
		ft.play();
		
		
	btn.setOnAction(new EventHandler<ActionEvent>() {
		
		    public void handle(ActionEvent e) {
		 
		       if(user_name.getText().equals("")| number_pancake.getText().equals("")|
		    		   AI_diff.getText().equals("")|random.getText().equals("")
		    		   )
		       {
		    	   message.setText("You need fill everything in blank");
		       }
		       else if(Integer.parseInt(number_pancake.getText()) <2 |Integer.parseInt(number_pancake.getText()) >9   )
		       {
		    	   message.setText("You can only enter pancakes 2 to 9 ");
		       }
		       else if(Integer.parseInt(AI_diff.getText()) > Integer.parseInt(number_pancake.getText()))
		       {
		    	   message.setText("AI difficulty is wrong");
		       } 
		       else { 
		    	   try {
		    		   FileWriter fstream = new FileWriter("setup.txt");
		    		   BufferedWriter writer = new BufferedWriter(fstream);
		    		   writer.write(user_name.getText());
		    		   writer.newLine();
		    		   writer.write(number_pancake.getText());
		    		   writer.newLine();
		    		   writer.write(AI_diff.getText());
		    		   writer.newLine();
		    		   
		    		   if(!("yes".equals(random.getText().trim().toLowerCase())))
		    		   {
		    			  writer.write("0");
		    			  writer.newLine();
		    			  String w = "", s = random.getText();
							for(int i = 0; i < s.length(); i++)
								w += s.charAt(i) + " ";
							writer.write(w);
		    		   }
		    		   else
		    			   writer.write("1");
		    			   
					   writer.close();
						
					} catch (IOException e1) {
						e1.printStackTrace();
					}
		    	   
		    	   File f = new File("pancake.txt");
		    	   File f1= new File("AIPancake.txt");
		    	try {
		    		
					changeScenes();
				} catch (Exception e1) {
					e1.printStackTrace();
				}  
		       }

		    }
		}
	);
     	grid.getChildren().add(message);

		final Text actiontarget = new Text();
        grid.add(actiontarget, 1, 6);
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	
	private void changeScenes() throws Exception 
	{
		Pancake ci = new Pancake();
	   Scene scene1 = ci.s();
	   
	    primaryStage.setTitle("Pancake Game");
	    primaryStage.setScene(scene1);
	   
	}
	
	public static void main(String[] args) {
		launch();	
	}
		
}
