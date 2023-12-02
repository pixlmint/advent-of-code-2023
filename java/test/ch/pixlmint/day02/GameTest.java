package ch.pixlmint.day02;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class GameTest {
    @Test
    public void testCubeCounts() throws Exception {
        Game game = new Game();
        game.play();
        assertEquals(2268, game.getSumIds());
    }
}
