package ch.pixlmint.day07;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class HandTest {
    @Test
    void testParseHand() {
        String handString = "3T 765";
        Hand hand = Hand.parseHand(handString);
        assertEquals(Card.THREE, hand.getCards().get(0));
        assertEquals(Card.T, hand.getCards().get(1));

        assertEquals(765, hand.getBidAmount());
    }
}