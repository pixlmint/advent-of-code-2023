package ch.pixlmint.util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class FileParser {
    private final File file;
    private static Map<String, List<String>> parsedFiles = new HashMap<>();

    public FileParser(File file) {
        this.file = file;
    }

    public void read() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(this.file));
        String st;
        List<String> lines = new ArrayList<>();
        while ((st = br.readLine()) != null) {
            lines.add(st.trim());
        }
        parsedFiles.put(this.file.getPath(), lines);
    }

    public static List<String> parse(String path) throws Exception {
        if (parsedFiles.containsKey(path)) {
            return parsedFiles.get(path);
        }

        File file = new File(path);
        FileParser parser = new FileParser(file);
        parser.read();
        return parsedFiles.get(file.getPath());
    }
}
