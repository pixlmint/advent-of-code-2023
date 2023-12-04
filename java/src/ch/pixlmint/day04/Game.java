package ch.pixlmint.day04;

import ch.pixlmint.util.FileParser;

import java.util.ArrayList;
import java.util.List;

public class Game {
    private List<String> lines;
    private List<Scratchcard> cards;

    public static void main(String[] args) throws Exception {
        Game game = new Game("resources/day04/scratchcards.txt");
        game.findWinningNumber();
    }

    public Game(String resourceFile) throws Exception {
        this.lines = this.parseResourceFile(resourceFile);
        this.cards = new ArrayList<>();
        this.parseScratchcards();
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
