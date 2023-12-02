package ch.pixlmint.day01;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class TrebuchetTest {
    @Test
    public void testCalculateTargetLocation() {
        String[] codeStrings = new String[]{"two1nine", "eightwothree", "abcone2threexyz", "xtwone3four", "4nineeightseven2", "zoneight234", "7pqrstsixteen"};
        List<LocationCode> codes = new ArrayList<>();
        for (String code : codeStrings) {
            LocationCode locCode = new LocationCode(code);
            codes.add(locCode);
        }

        Trebuchet trebuchet = new Trebuchet(codes);

        int expected = 281;

        assertEquals(expected, trebuchet.calculateTargetLocation());
    }
}