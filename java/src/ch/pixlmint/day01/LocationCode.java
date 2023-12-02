package ch.pixlmint.day01;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class LocationCode {
    private final String strCode;
    private int parsedCode;

    LocationCode(String strCode) {
        this.strCode = strCode;
        this.parseCode();
    }

    public int getParsedCode() {
        return this.parsedCode;
    }

    private void parseCode() {
        String codeParser = "([0-9]?)";
        Pattern pattern = Pattern.compile(codeParser);
        Matcher matcher = pattern.matcher(this.strCode);
        String firstNumber = "";
        String lastNumber = "";
        while (matcher.find()) {
            String match = matcher.group(0);
            if (match.isEmpty()) {
                continue;
            }
            if (firstNumber.isEmpty()) {
                firstNumber = match;
                lastNumber = match;
            } else {
                lastNumber = match;
            }
        }
        String parsedCodeString = firstNumber + lastNumber;
        this.parsedCode = Integer.parseInt(parsedCodeString);
    }
}
