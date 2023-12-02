package ch.pixlmint.day02;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

public class Game {
    private String[] strRounds;
    private final List<GameDraw> gameDraws;

    public static void main(String[] args) throws Exception {
        Game game = new Game();
        game.play();
        System.out.println(game.getSumIds());
    }

    public Game() throws Exception {
        this.gameDraws = new ArrayList<>();
        File file = new File("resources/day02/cubes.txt");
        this.parseGameDraws(file);
    }

    public void play() {
        for (String round : strRounds) {
            this.gameDraws.add(GameDraw.parseGameDrawString(round));
        }
    }

    public int getSumIds() {
        int sumIds = 0;
        for (GameDraw draw : this.gameDraws) {
            if (draw.isDrawValid()) {
                sumIds += draw.getDrawNumber();
            }
        }

        return sumIds;
    }

    private void parseGameDraws(File file) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(file));
        String str;
        List<String> lines = new ArrayList<>();
        while ((str = br.readLine()) != null) {
            lines.add(str);
        }
        this.strRounds = lines.toArray(new String[0]);
    }
}
