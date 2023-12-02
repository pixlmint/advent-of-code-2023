package ch.pixlmint.day02;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class GameRoundTest {
    @Test
    public void testParseGameDrawString() throws Exception {
        String drawStr = "Game 82: 4 blue, 1 red, 7 green; 4 red, 14 blue, 8 green; 1 red, 11 blue, 6 green";
        GameRound round = GameRound.parseGameDrawString(drawStr);
        System.out.println(round);
        // assertEquals(29, round.countCubes(CubeColor.BLUE));
    }

    @Test
    public void testGetMinAmount() throws Exception {
        String drawStr = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
        String draw2Str = "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue";
        GameRound round = GameRound.parseGameDrawString(drawStr);
        GameRound round2 = GameRound.parseGameDrawString(draw2Str);
        assertEquals(4, round.getMinAmount(CubeColor.RED));
        assertEquals(2, round.getMinAmount(CubeColor.GREEN));
        assertEquals(6, round.getMinAmount(CubeColor.BLUE));
        assertEquals(48, round.getCubesPower());

        assertEquals(1, round2.getMinAmount(CubeColor.RED));
        assertEquals(3, round2.getMinAmount(CubeColor.GREEN));
        assertEquals(4, round2.getMinAmount(CubeColor.BLUE));
        assertEquals(12, round2.getCubesPower());
    }
}
