package ch.pixlmint.day04;

import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

class ScratchcardTest {
    @Test
    public void testGetValue() {
        Map<String, Integer> codes = new HashMap<>();
        codes.put("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53", 8);
        codes.put("Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19", 2);
        codes.put("Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1", 2);
        codes.put("Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83", 1);
        codes.put("Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36", 0);
        codes.put("Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11", 0);

        for (String code : codes.keySet()) {
            Scratchcard card = Scratchcard.parseCardCode(code);
            assertEquals(codes.get(code), card.getValue());
        }
    }

}