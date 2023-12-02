package ch.pixlmint.day02;

public class ColoredCube {
    private final CubeColor color;
    private final int count;

    public ColoredCube(CubeColor color, int count) {
        this.color = color;
        this.count = count;
    }

    public CubeColor getColor() {
        return this.color;
    }

    public int getCount() {
        return this.count;
    }
}
