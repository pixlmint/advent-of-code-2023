package ch.pixlmint.day01;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Trebuchet {
    private List<LocationCode> codes;

    public static void main(String[] args) {
        File mapFile = new File("resources/day01/codes.txt");
        Trebuchet trebuchet;
        try {
            trebuchet = new Trebuchet(mapFile);
            System.out.println(trebuchet.calculateTargetLocation());
        } catch (Exception e) {
            System.out.println("Error creating trebuchet: " + e.getMessage());
        }
    }

    public Trebuchet(File mapFile) throws Exception {
        this.codes = new ArrayList<>();
        this.parseFile(mapFile);
    }

    public int calculateTargetLocation() {
        int finalNumber = 0;
        for (LocationCode code : this.codes) {
            finalNumber += code.getParsedCode();
        }

        return finalNumber;
    }

    private void parseFile(File mapFile) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(mapFile));

        String st;

        while ((st = br.readLine()) != null) {
            this.codes.add(new LocationCode(st));
        }
    }
}
