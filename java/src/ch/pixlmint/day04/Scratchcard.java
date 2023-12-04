package ch.pixlmint.day04;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Scratchcard {
    private final int cardNumber;
    private final List<Integer> winningNumbers;
    private final List<Integer> havingNumbers;

    public Scratchcard(int cardNumber, List<Integer> winningNumbers, List<Integer> havingNumbers) {
        this.cardNumber = cardNumber;
        this.winningNumbers = winningNumbers;
        this.havingNumbers = havingNumbers;
    }

    public int getValue() {
        int value = 0;

        for (int num : this.winningNumbers) {
            if (this.havingNumbers.contains(num)) {
                if (value == 0) {
                    value = 1;
                } else {
                    value = value * 2;
                }
            }
        }

        return value;
    }

    public static Scratchcard parseCardCode(String cardCode) {
        String cardRegex = "Card\\s*(?<number>\\d+):(?<str1>(\\s*\\d*)*)|(?<str2>(\\s*\\d*)*)";
        Pattern cardPattern = Pattern.compile(cardRegex);
        Matcher cardMatcher = cardPattern.matcher(cardCode);

        int number = 0;
        List<Integer> winningNumbers = new ArrayList<>();
        List<Integer> numbers = new ArrayList<>();

        while (cardMatcher.find()) {
            if (cardMatcher.group("number") != null) {
                number = Integer.parseInt(cardMatcher.group("number"));
            }
            String match1 = cardMatcher.group("str1");
            if (match1 != null && !match1.isEmpty()) {
                String[] numStr = match1.trim().split("\\s+");
                for (String num : numStr) {
                    winningNumbers.add(Integer.parseInt(num.trim()));
                }
            }
            String match2 = cardMatcher.group("str2");
            if (match2 != null && !match2.isEmpty()) {
                String[] numStr = match2.trim().split("\\s+");
                for (String num : numStr) {
                    numbers.add(Integer.parseInt(num.trim()));
                }
            }
            if (!winningNumbers.isEmpty() && !numbers.isEmpty()) {
                break;
            }
        }

        return new Scratchcard(number, winningNumbers, numbers);
    }
}
