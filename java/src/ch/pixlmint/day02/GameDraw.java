package ch.pixlmint.day02;

import java.util.HashMap;
import java.util.Map;

public class GameDraw {
    private final Map<CubeColor, Integer> cubes;

    public GameDraw() {
        this.cubes = new HashMap<>();
    }

    public void setCubeCount(ColoredCube cube) throws Exception {
        if (this.cubes.containsKey(cube.getColor())) {
            throw new Exception("Draw already container color " + cube.getCount());
        }
        this.cubes.put(cube.getColor(), cube.getCount());
    }

    public int getCubeCount(CubeColor color) {
        if (this.cubes.containsKey(color)) {
            return this.cubes.get(color);
        }
        return 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (CubeColor color : this.cubes.keySet()) {
            if (!sb.toString().isEmpty()) {
                sb.append(", ");
            }
            sb.append(this.cubes.get(color).toString()).append(" ").append(color.toString());
        }

        return sb.toString();
    }
}
