package ch.pixlmint.day07;

import java.util.ArrayList;
import java.util.List;

public class Hand {
    private final List<Card> cards;
    private final int bidAmount;

    public Hand(List<Card> cards, int bidAmount) {
        this.cards = cards;
        this.bidAmount = bidAmount;
    }

    public static Hand parseHand(String strHand) {
        String[] splitStrHand = strHand.split(" ");
        String[] splitHand = splitStrHand[0].split("");
        int bidAmount = Integer.parseInt(splitStrHand[1]);
        List<Card> cards = new ArrayList<>();
        for (String strCard : splitHand) {
            cards.add(Card.parseCard(strCard));
        }

        return new Hand(cards, bidAmount);
    }

    public List<Card> getCards() {
        return cards;
    }

    public int getBidAmount() {
        return bidAmount;
    }
}
