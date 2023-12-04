package ch.pixlmint.day03.helper;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class UniqueSymbolsExtractor {
    private final List<String> symbols = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        new UniqueSymbolsExtractor();
    }

    public UniqueSymbolsExtractor() throws Exception {
        this.findSymbols();
        System.out.println(this.symbols);
    }

    private void findSymbols() throws Exception {
        List<String> lines = FileParser.parse("resources/day03/symbols.txt");
        Pattern symbolPattern = Pattern.compile("[^\\.'-9]");
        for (String line : lines) {
            Matcher matcher = symbolPattern.matcher(line);
            while (matcher.find()) {
                String foundSymbol = matcher.group();
                if (!this.symbols.contains(foundSymbol)) {
                    this.symbols.add(foundSymbol);
                }
            }
        }
    }
}
