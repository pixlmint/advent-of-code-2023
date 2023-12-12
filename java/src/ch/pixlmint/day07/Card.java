package ch.pixlmint.day07;

import java.util.Objects;

public enum Card {
    A(12), K(11), Q(10), J(9), T(8),
    NINE("9"), EIGHT("8"),
    SEVEN("7"), SIX("6"),
    FIVE("5"), FOUR("4"),
    THREE("3"), TWO("2");

    private final String label;
    private final int strength;

    Card(int strength) {
        this.label = this.toString();
        this.strength = strength;
    }

    Card(String label) {
        this.label = label;
        this.strength = Integer.parseInt(label);
    }

    public String getLabel() {
        return this.label;
    }

    public int getStrength() {
        return this.strength;
    }

    public static Card parseCard(String cardString) {
        for (Card card : Card.values()) {
            if (card.getLabel().equals(cardString)) {
                return card;
            }
        }
        throw new IllegalArgumentException("invalid card label: " + cardString);
    }
}
