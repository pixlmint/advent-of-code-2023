package ch.pixlmint.day02;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GameDraw {
    private final List<ColoredCube> cubes;
    private final int drawNumber;
    private boolean isDrawValid = true;

    public GameDraw(int drawNumber) {
        this.cubes = new ArrayList<>();
        this.drawNumber = drawNumber;
    }

    public static GameDraw parseGameDrawString(String gameDrawString) {
        String[] roundInformation = gameDrawString.split(":");
        String gameMeta = roundInformation[0].trim();
        String cubesCsv = roundInformation[1].trim();

        String numberRegex = "([0-9]+)";
        Pattern pattern = Pattern.compile(numberRegex);
        Matcher matcher = pattern.matcher(gameMeta);
        matcher.find();
        int roundNumber = Integer.parseInt(matcher.group());
        GameDraw draw = new GameDraw(roundNumber);

        String[] cubes = cubesCsv.split("[,;]");
        for (String cube : cubes) {
            Matcher cubeCountMatcher = pattern.matcher(cube);
            cubeCountMatcher.find();
            int count = Integer.parseInt(cubeCountMatcher.group(1));
            CubeColor color = CubeColor.parseColor(cube);
            if (count > color.getMaxCount()) {
                draw.setDrawValid(false);
            }
            ColoredCube newCube = new ColoredCube(color, count);
            draw.addCube(newCube);
        }

        return draw;
    }

    public int getDrawNumber() {
        return this.drawNumber;
    }

    public void setDrawValid(boolean isDrawValid) {
        this.isDrawValid = isDrawValid;
    }

    public boolean isDrawValid() {
        return isDrawValid;
    }

    public boolean checkValidStatus() {
        for (CubeColor color : CubeColor.values()) {
            if (this.countCubes(color) > color.getMaxCount()) {
                return false;
            }
        }

        return true;
    }

    public void addCube(ColoredCube cube) {
        this.cubes.add(cube);
    }

    public int countCubes(CubeColor color) {
        int count = 0;
        for (ColoredCube cube : this.cubes) {
            if (cube.getColor().equals(color)) {
                count += cube.getCount();
            }
        }

        return count;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Game ").append(this.drawNumber);
        for (ColoredCube cube : this.cubes) {
            sb.append(", ").append(cube.getColor().toString()).append(" ").append(cube.getCount());
        }
        return sb.toString();
    }
}
