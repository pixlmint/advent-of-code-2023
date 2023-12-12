package ch.pixlmint.day07;

import java.util.*;

public enum WinningHand {
    FIVE_OF_A_KIND, FOUR_OF_A_KIND, FULL_HOUSE, THREE_OF_A_KIND, TWO_PAIR, ONE_PAIR, HIGH_CARD;

    static WinningHand parseCards(Card[] cards) {
        Arrays.sort(cards);
        Map<Card, Integer> matchesCount = new HashMap<>();
        for (Card card : cards) {
            matchesCount.putIfAbsent(card, 0);
            matchesCount.put(card, matchesCount.get(card) + 1);
        }

        for (Card card : matchesCount.keySet()) {

        }
    }
}
