package ch.pixlmint.day02;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

public class Game {
    private String[] strRounds;
    private final List<GameRound> gameRounds;

    public static void main(String[] args) throws Exception {
        Game game = new Game();
        game.play();
        System.out.println(game);
    }

    public Game() throws Exception {
        this.gameRounds = new ArrayList<>();
        File file = new File("resources/day02/cubes.txt");
        this.parseGameDraws(file);
    }

    public void play() throws Exception {
        for (String round : strRounds) {
            this.gameRounds.add(GameRound.parseGameDrawString(round));
        }
    }

    public int getCubesPower() {
        int cubesPower = 0;

        for (GameRound round : this.gameRounds) {
            cubesPower += round.getCubesPower();
        }

        return cubesPower;
    }

    public int getSumIds() {
        int sumIds = 0;
        for (GameRound draw : this.gameRounds) {
            if (draw.isRoundValid()) {
                sumIds += draw.getRoundNumber();
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

    @Override
    public String toString() {
        return "SumIds: " + this.getSumIds() + System.lineSeparator() +
                "Power: " + this.getCubesPower() + System.lineSeparator();
    }
}
