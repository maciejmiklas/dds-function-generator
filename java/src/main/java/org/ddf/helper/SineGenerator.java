package org.ddf.helper;

public class SineGenerator {

    public String generate() {
	for (int angle = 0; angle < 360; angle += 2) {
	    double sin = Math.sin(Math.toRadians(angle));
	    System.out.println(angle + " -> " + sin);
	}
	return null;
    }

    public static void main(String[] args) {
	SineGenerator sg = new SineGenerator();
	sg.generate();
    }

}
