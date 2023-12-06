package ch.pixlmint.day05;

import java.util.ArrayList;
import java.util.List;

public class ResourceMap {
    private String name;
    private List<Integer> sourceValues;
    private List<Integer> destinationValues;
    private List<Integer> rangeSizes;

    public ResourceMap(String name) {
        this.name = name;
        this.sourceValues = new ArrayList<>();
        this.destinationValues = new ArrayList<>();
        this.rangeSizes = new ArrayList<>();
    }
}
