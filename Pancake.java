import java.awt.TextArea;
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;

import javafx.application.Application;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;
import javafx.stage.Stage;

import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

public class Pancake implements EventHandler<ActionEvent>{
    ArrayList<Integer> humanPancake;
    ArrayList<Integer> AIPancakes;
    ArrayList<Button> Buttons;
    ArrayList<Button> ButtonsAI;
    Pane layout;
    Text h;
    Text AI;
    Scene scene1;
    String winner;
    
    public Scene s() throws Exception
    {
    	Buttons = new ArrayList<>();
        AIPancakes = new ArrayList<>();
        humanPancake = new ArrayList<>();
        ButtonsAI = new ArrayList<>();
        layout = new Pane();
        h = new Text();
        AI = new Text();
        h.setFont(new Font(16));
        AI.setFont(new Font(16));
        read();
        attach_pancake();
        scene1 = new Scene(layout, 600, 600);
        return scene1;
    }

    @Override
    public void handle(ActionEvent event) {
        try {
            for (int i = 0; i < humanPancake.size(); i++) {
                if (event.getSource() == Buttons.get(i)) {
                    Writer out = new FileWriter("click.txt");
                    Integer num = i;
                    System.out.println(num);
                    out.write(num.toString());
                    out.close();
                    detach_pancake();
                    read();
                    attach_pancake();
                }
            }
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
    
    public Scene changeScreen(String name) {
    	//To do
    	Scene s1 = null;	
    	return s1;
    }

    public void detach_pancake(){
        for(int i = 0; i < humanPancake.size(); i++){
            layout.getChildren().remove(Buttons.get(i));
            layout.getChildren().remove(ButtonsAI.get(i));
        }
        Buttons.clear();
        ButtonsAI.clear();
        humanPancake.clear();
        AIPancakes.clear();
        layout.getChildren().remove(h);
        layout.getChildren().remove(AI);
    }

    public void attach_pancake(){
        int start_y = startposition(humanPancake.size());
        int width;
        int center = 115;
        String label;
        h.setText("Human:");
        h.setLayoutY(start_y - 15);
        h.setLayoutX(center - 20);
        layout.getChildren().add(h);
        for(int i = 0; i < humanPancake.size(); i++){
            label = humanPancake.get(i).toString();
            width = 30 + humanPancake.get(i) * 10;
            Button b = new Button(label);
            b.setLayoutX(center - width / 2);
            b.setLayoutY(start_y);
            b.setMinWidth(width);
            b.setMinHeight(40);
            b.setOnAction(this);
            Buttons.add(b);
            layout.getChildren().add(b);
            start_y += 50;
        }

        start_y = startposition(humanPancake.size());
        AI.setText("AI:");
        AI.setLayoutY(start_y - 15);
        AI.setLayoutX(center+340);
        layout.getChildren().add(AI);
        for(int i = 0; i < AIPancakes.size(); i++){
            label = AIPancakes.get(i).toString();
            width = 30 + AIPancakes.get(i) * 10;
            Button b = new Button(label);
            b.setLayoutX((center + 350) - width / 2);
            b.setLayoutY(start_y);
            b.setMinWidth(width);
            b.setMinHeight(40);
            b.setOnAction(this);
            ButtonsAI.add(b);
            layout.getChildren().add(b);
            start_y += 50;
        }
    }

    public int startposition(int n){
        int y = 320 - 40 * n;
        return y;
    }

    public void read() throws Exception{
        File file = new File("pancake.txt");
        Scanner sc = new Scanner(file);
        Scanner w = new Scanner(file);
        while(sc.hasNextInt()){
            humanPancake.add(sc.nextInt());
        }
        if(sc.hasNext()) {
        	winner = sc.nextLine();
        	changeScreen(winner);
        }
        File Afile = new File("AIpancake.txt");
        Scanner Asc = new Scanner(Afile);
        
        while(Asc.hasNextInt()){
            AIPancakes.add(Asc.nextInt());
        }

        for(int j = 0; j < humanPancake.size(); j++){
            System.out.println(humanPancake.get(j));
        }
    }


}
    
  
