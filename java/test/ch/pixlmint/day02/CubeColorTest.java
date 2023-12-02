package ch.pixlmint.day02;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class CubeColorTest {
    @Test
    public void testParseColor() {
        String color = "asdfgreenasdf3";
        assertEquals(CubeColor.GREEN, CubeColor.parseColor(color));
    }
}
