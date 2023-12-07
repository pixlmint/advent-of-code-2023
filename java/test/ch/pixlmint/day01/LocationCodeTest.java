package ch.pixlmint.day01;

import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

class LocationCodeTest {
    @Test
    public void testCodeParsingInteger() {
        String code = "asdf49as5ed";
        LocationCode parsed = new LocationCode(code);
        assertEquals(45, parsed.getParsedCode());
    }

    @Test
    public void testCodeParsing() {
        Map<String, Integer> codesMap = new HashMap<>();
        codesMap.put("asdf49as5ed", 45);
        codesMap.put("b5", 55);
        codesMap.put("two1nine", 29);
        codesMap.put("threeonepzltnzdninefive45two", 32);
        codesMap.put("sixfourfivefour9xfvrdzfgjnjhzjkzcbpfpqkzfg", 69);
        codesMap.put("cfivekng6", 56);
        codesMap.put("five", 55);
        codesMap.put("6hglld", 66);
        codesMap.put("qtwone1bssfvxsdd28qhone", 21);
        codesMap.put("37", 37);
        codesMap.put("22two3rkpxjvkhflqfjgf", 23);
        codesMap.put("fpccz628p3", 63);
        codesMap.put("4543fiveptzlmzpblflvqklseven", 47);
        codesMap.put("fpgppvsl2fivesevenslhbjqsf5one2", 22);
        codesMap.put("fjeightwo9xtxrmfive5three", 83);
        codesMap.put("4vd", 44);
        codesMap.put("6nine7lthcjbbqskktvnmnz6four8nine", 69);
        codesMap.put("691", 61);
        codesMap.put("383nineeight9eightjfdhmjfrj", 38);
        codesMap.put("85one7szmffjstpbdssixpfqbbcljn6", 86);
        codesMap.put("twone", 21);

        for (String codeString : codesMap.keySet()) {
            LocationCode code = new LocationCode(codeString);
            assertEquals(codesMap.get(codeString), code.getParsedCode());
        }
    }
}