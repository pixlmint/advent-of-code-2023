package ch.pixlmint.day01;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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

    @Test
    public void testCalculateLocationPart() {
        Map<String, Integer> codeStrings = new HashMap<>();
        codeStrings.put("two1nine", 29);
        codeStrings.put("eightwothree", 83);
        codeStrings.put("abcone2threexyz", 13);
        codeStrings.put("xtwone3four", 24);
        codeStrings.put("4nineeightseven2", 42);
        codeStrings.put("zoneight234", 14);
        codeStrings.put("7pqrstsixteen", 76);

        for (String code : codeStrings.keySet()) {
            LocationCode locCode = new LocationCode(code);
            assertEquals(codeStrings.get(code), locCode.getParsedCode());
        }
    }
}