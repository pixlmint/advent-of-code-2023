package ch.pixlmint.day02;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GameRound {
    private final int roundNumber;
    private final List<GameDraw> draws;
    private boolean isRoundValid = true;

    public GameRound(int drawNumber) {
        this.draws = new ArrayList<>();
        this.roundNumber = drawNumber;
    }

    public static GameRound parseGameDrawString(String gameDrawString) throws Exception {
        String[] roundInformation = gameDrawString.split(":");
        String gameMeta = roundInformation[0].trim();
        String cubesCsv = roundInformation[1].trim();

        String numberRegex = "([0-9]+)";
        Pattern pattern = Pattern.compile(numberRegex);
        Matcher matcher = pattern.matcher(gameMeta);
        matcher.find();
        int roundNumber = Integer.parseInt(matcher.group());
        GameRound round = new GameRound(roundNumber);

        String[] draws = cubesCsv.split(";");
        for (String strDraw : draws) {
            GameDraw draw = new GameDraw();
            String[] cubes = strDraw.split(",");
            for (String cube : cubes) {
                Matcher cubeCountMatcher = pattern.matcher(cube);
                cubeCountMatcher.find();
                int count = Integer.parseInt(cubeCountMatcher.group(1));
                CubeColor color = CubeColor.parseColor(cube);
                if (count > color.getMaxCount()) {
                    round.setRoundValid(false);
                }
                ColoredCube newCube = new ColoredCube(color, count);
                draw.setCubeCount(newCube);
            }
            round.addGameDraw(draw);
        }

        return round;
    }

    public int getMinAmount(CubeColor color) {
        int minAmount = 1;
        for (GameDraw draw : this.draws) {
            int drawCubeCount = draw.getCubeCount(color);
            if (minAmount < drawCubeCount) {
                minAmount = drawCubeCount;
            }
        }

        return minAmount;
    }

    public int getCubesPower() {
        int power = 1;
        for (CubeColor color : CubeColor.values()) {
            power *= this.getMinAmount(color);
        }

        return power;
    }

    public void addGameDraw(GameDraw gameDraw) {
        this.draws.add(gameDraw);
    }

    public int getRoundNumber() {
        return this.roundNumber;
    }

    public void setRoundValid(boolean isRoundValid) {
        this.isRoundValid = isRoundValid;
    }

    public boolean isRoundValid() {
        return isRoundValid;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Game ").append(this.roundNumber).append(": ");
        for (GameDraw draw : this.draws) {
            sb.append(draw.toString()).append("; ");
        }
        return sb.toString();
    }
}
