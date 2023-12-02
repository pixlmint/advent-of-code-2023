package ch.pixlmint.day02;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class GameDrawTest {
    @Test
    public void testParseGameDrawString() {
        String drawStr = "Game 82: 4 blue, 1 red, 7 green; 4 red, 14 blue, 8 green; 1 red, 11 blue, 6 green";
        GameDraw draw = GameDraw.parseGameDrawString(drawStr);
        System.out.println(draw);
        assertEquals(29, draw.countCubes(CubeColor.BLUE));
    }
}
