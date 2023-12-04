package ch.pixlmint.day03;

import java.io.LineNumberReader;

public class SchematicLine {
    private String lineRepresentation;
    private SchematicLine previousLine = null;
    private SchematicLine nextLine = null;

    public SchematicLine(String lineRepresentation) {
        this.lineRepresentation = lineRepresentation;
    }

    public void setNextLine(SchematicLine nextLine) {
        this.nextLine = nextLine;
        nextLine.setPreviousLine(this);
    }

    public void setPreviousLine(SchematicLine previousLine) {
        this.previousLine = previousLine;
    }

    public boolean isSymbolAtPosition(int position) {
        return false;
    }
}
