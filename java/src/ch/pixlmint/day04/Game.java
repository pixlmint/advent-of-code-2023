package ch.pixlmint.day04;

import ch.pixlmint.util.FileParser;

import java.util.ArrayList;
import java.util.List;

public class Game {
    private List<String> lines;
    private List<Scratchcard> cards;
    private List<Scratchcard> copiedCards;
    private int recursionDepth = 0;

    public static void main(String[] args) throws Exception {
        Game game = new Game("resources/day04/scratchcards.txt");
        game.findWinningNumber();
        System.out.println(game.processRecursiveCopies());
    }

    public Game(String resourceFile) throws Exception {
        this.lines = this.parseResourceFile(resourceFile);
        this.cards = new ArrayList<>();
        this.parseScratchcards();
    }

    public Game(List<String> cardCodes) {
        this.lines = cardCodes;
        this.cards = new ArrayList<>();
        this.parseScratchcards();
    }

    public int processRecursiveCopies() {
        this.copiedCards = new ArrayList<>();

        for (Scratchcard card : this.cards) {
            int cardIndex = this.cards.indexOf(card);
            card.copy();
            int cardOccurrences = card.countMatches();
            for (int x = 0; x < card.getCopiesCount(); x++) {
                for (int i = 1; i <= cardOccurrences; i++) {
                    int nextCardIndex = cardIndex + i;
                    if (nextCardIndex >= this.cards.size()) {
                        continue;
                    }
                    this.cards.get(nextCardIndex).copy();
                }
            }
        }

        int finalCount = 0;
        for (Scratchcard card : this.cards) {
            finalCount += card.getCopiesCount();
        }

        return finalCount;
    }

    public void copyCardsRecursively(Scratchcard card) {
        this.recursionDepth++;
        int occurrences = card.countMatches();
        for (int i = 1; i <= occurrences; i++) {
            int nextCardIndex = this.cards.indexOf(card) + i;
            if (nextCardIndex >= this.cards.size()) {
                return;
            }
            Scratchcard cardToCopy = this.cards.get(nextCardIndex);
            this.copiedCards.add(cardToCopy);
            this.copyCardsRecursively(cardToCopy);
        }
        System.out.println(this.recursionDepth);
    }

    public void findWinningNumber() {
        int totalValue = 0;
        for (Scratchcard card : this.cards) {
            totalValue += card.getValue();
        }
        System.out.println(totalValue);
    }

    private void parseScratchcards() {
        for (String line : this.lines) {
            cards.add(Scratchcard.parseCardCode(line));
        }
    }

    private List<String> parseResourceFile(String filePath) throws Exception {
        return FileParser.parse(filePath);
    }
}
