package ch.pixlmint.day07;

import ch.pixlmint.util.FileParser;

import java.util.List;

public class CamelCase {
    private final List<String> cardLines;
    public static void main(String[] args) throws Exception {
        CamelCase game = new CamelCase("resources/day07/camelcase.txt");
    }

    public CamelCase(String resourceFile) throws Exception {
        this.cardLines = FileParser.parse(resourceFile);
    }
}
