package ch.pixlmint.day05;

import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

class PlanterTest {
    @Test
    public void testEmptyLineCheck() {
        Map<String, Boolean> lines = new HashMap<>();
        lines.put("\n", true);
        lines.put("some content", false);

        for (String line : lines.keySet()) {
            assertEquals(lines.get(line), Planter.isEmptyLine(line));
        }
    }
}