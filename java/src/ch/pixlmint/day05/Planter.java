package ch.pixlmint.day05;

import ch.pixlmint.util.FileParser;

import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Planter {
    private List<String> mapLines;

    public static void main(String[] args) throws Exception {
        Planter planter = new Planter("resources/day05/maps.txt");
    }

    public Planter(String mapFilePath) throws Exception {
        this.mapLines = FileParser.parse(mapFilePath);
        this.parseMap();
    }

    private void parseMap() {
        for (String line : this.mapLines) {

        }
    }

    public static boolean isEmptyLine(String line) {
        String emptyLineRegex = "^\\n$";
        Pattern emptyLinePattern = Pattern.compile(emptyLineRegex);

        Matcher emptyLine = emptyLinePattern.matcher(line);

        while (emptyLine.find()) {
            if (!emptyLine.group().isEmpty()) {
                return true;
            }
        }

        return false;
    }
}
