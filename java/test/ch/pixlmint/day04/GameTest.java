package ch.pixlmint.day04;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

class GameTest {
    @Test
    public void testGame() {
        List<String> cardStrings = new ArrayList<>();
        cardStrings.add("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53");
        cardStrings.add("Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19");
        cardStrings.add("Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1");
        cardStrings.add("Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83");
        cardStrings.add("Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36");
        cardStrings.add("Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11");

        Game game = new Game(cardStrings);
        assertEquals(30, game.processRecursiveCopies());
    }

}