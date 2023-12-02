package ch.pixlmint.day02;

public enum CubeColor {
    GREEN(13), BLUE(14), RED(12);

    private final int maxCount;

    CubeColor(int maxCount) {
        this.maxCount = maxCount;
    }

    public int getMaxCount() {
        return this.maxCount;
    }

    public static CubeColor parseColor(String strColor) {
        for (CubeColor color : CubeColor.values()) {
            String replaced = strColor.toLowerCase().replace(color.toString().toLowerCase(), "");
            if (replaced.length() != strColor.length()) {
                return color;
            }
        }

        throw new RuntimeException("no matching color found for string " + strColor);
    }
}
