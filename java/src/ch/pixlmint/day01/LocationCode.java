package ch.pixlmint.day01;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class LocationCode {
    private final String strCode;
    private int parsedCode;

    private static final List<String> stringNumbers = new ArrayList<>(List.of(new String[]{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}));
    private static final String codeParser;

    static {
        StringBuilder regexBuilder = new StringBuilder("([1-9]");
        for (String stringNumber : stringNumbers) {
            regexBuilder.append("|(").append(stringNumber).append(")");
        }
        regexBuilder.append(")?");
        codeParser = regexBuilder.toString();
    }

    LocationCode(String strCode) {
        this.strCode = strCode;
        this.parseCode();
    }

    public int getParsedCode() {
        return this.parsedCode;
    }

    private void parseCode() {
        Pattern pattern = Pattern.compile(codeParser);
        Matcher matcher = pattern.matcher(this.strCode);
        List<String> numberStrings = new ArrayList<>();
        while (matcher.find()) {
            String match = matcher.group(0);
            if (match.isEmpty()) {
                continue;
            }
            if (numberStrings.isEmpty()) {
                numberStrings.add(match);
                numberStrings.add(match);
            } else {
                numberStrings.set(1, match);
            }
        }
        StringBuilder parsedCodeString = new StringBuilder();
        for (String numberString : numberStrings) {
            try {
                parsedCodeString.append(Integer.parseInt(numberString));
            } catch (NumberFormatException e) {
                parsedCodeString.append(matchStringNumber(numberString));
            }
        }
        this.parsedCode = Integer.parseInt(parsedCodeString.toString());
    }

    private static int matchStringNumber(String numberString) {
        return stringNumbers.indexOf(numberString) + 1;
    }
}
