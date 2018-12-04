import java.awt.TextArea;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
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

import java.util.ArrayList;
import java.util.Scanner;

public class Pancake implements EventHandler<ActionEvent> {
    ArrayList<Integer> humanPancake;
    ArrayList<Integer> AIPancakes;
    ArrayList<Button> Buttons;
    ArrayList<Button> ButtonsAI;
    Pane layout;
    Text h;
    Text AI;
    Scene scene1;
    String winner;
    Stage root;
    int StackSize;

    public void start(Stage primaryStage) throws Exception {
        root = primaryStage;
        Buttons = new ArrayList<>();
        AIPancakes = new ArrayList<>();
        humanPancake = new ArrayList<>();
        ButtonsAI = new ArrayList<>();
        layout = new Pane();
        h = new Text();
        AI = new Text();
        h.setFont(new Font(16));
        AI.setFont(new Font(16));
        File file = new File("setup.txt");
        Scanner scanner = new Scanner(file);
        String temp = scanner.nextLine();
        temp = scanner.nextLine();
        StackSize = Integer.valueOf(temp);
        scanner.close();
        read();
        attach_pancake();
        scene1 = new Scene(layout, 600, 600);
        primaryStage.setScene(scene1);
    }

    @Override
    public void handle(ActionEvent event) {
        try {
            for (int i = 0; i < humanPancake.size(); i++) {
                if (event.getSource() == Buttons.get(i)) {
                    Writer out = new FileWriter("click.txt");
                    Integer num = i;
                    out.write(num.toString());
                    out.close();
                    detach_pancake();
                    read();
                    attach_pancake();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void changeScreen(String name) {
        highScores h = new highScores();
        try {
            h.setname(name);
            h.start(root);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void detach_pancake() {
        for (int i = 0; i < humanPancake.size(); i++) {
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

    public void attach_pancake() {
        int start_y = startposition(humanPancake.size());
        int width;
        int center = 115;
        String label;
        h.setText("Human:");
        h.setLayoutY(start_y - 15);
        h.setLayoutX(center - 20);
        layout.getChildren().add(h);
        for (int i = 0; i < humanPancake.size(); i++) {
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
        AI.setLayoutX(center + 340);
        layout.getChildren().add(AI);
        for (int i = 0; i < AIPancakes.size(); i++) {
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

    public int startposition(int n) {
        int y = 400 - 40 * n;
        return y;
    }

    public void read() throws Exception {
        boolean gameOver = false;
        while (true) {
            File over = new File("GameOver.txt");
            Scanner o = new Scanner(over);
            if(o.hasNext()) {
                winner = o.nextLine();
                System.out.println(winner);
                gameOver = true;
                break;
            }
            o.close();
            File file = new File("pancake.txt");
            AIPancakes.clear();
            humanPancake.clear();
            if (file.length() == 0)
                continue;
            Scanner sc = new Scanner(file);
            Scanner w = new Scanner(file);
            while (sc.hasNextInt()) {
                humanPancake.add(sc.nextInt());
            }
            sc.close();
            w.close();
            File Afile = new File("AIpancake.txt");
            Scanner Asc = new Scanner(Afile);

            while (Asc.hasNextInt()) {
                AIPancakes.add(Asc.nextInt());
            }
            Asc.close();
            if (AIPancakes.size() < StackSize || humanPancake.size() < StackSize)
                continue;
            PrintWriter pw = new PrintWriter("pancake.txt");
            pw.print("");
            pw.close();

            PrintWriter pai = new PrintWriter("pancake.txt");
            pai.print("");
            pai.close();
            break;
        }
        if(gameOver == true)
            changeScreen(winner);
    }
}