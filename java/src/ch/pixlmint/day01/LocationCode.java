package ch.pixlmint.day01;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class LocationCode {
    private final String strCode;
    private int parsedCode;

    LocationCode(String strCode) {
        this.strCode = filterCode(strCode);
        this.parseCode();
    }

    private static String filterCode(String strCode) {
        Map<String, String> replaceMap = new HashMap<>();
        replaceMap.put("o1e", "one");
        replaceMap.put("t2o", "two");
        replaceMap.put("t3e", "three");
        replaceMap.put("f4r", "four");
        replaceMap.put("f5e", "five");
        replaceMap.put("s6x", "six");
        replaceMap.put("s7n", "seven");
        replaceMap.put("e8t", "eight");
        replaceMap.put("n9e", "nine");

        for (String replace : replaceMap.keySet()) {
            strCode = strCode.replaceAll(replaceMap.get(replace), replace);
        }

        return strCode;
    }

    public int getParsedCode() {
        return this.parsedCode;
    }

    private void parseCode() {
        Pattern pattern = Pattern.compile("([0-9]?)");
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
            }
            lastNumber = match;
        }
        String parsedCodeString = firstNumber + lastNumber;
        this.parsedCode = Integer.parseInt(parsedCodeString);
    }
}
