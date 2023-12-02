package ch.pixlmint.day01;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class LocationCodeTest {
    @Test
    public void testCodeParsingInteger() {
        String code = "asdf49as5ed";
        LocationCode parsed = new LocationCode(code);
        assertEquals(45, parsed.getParsedCode());
    }
}