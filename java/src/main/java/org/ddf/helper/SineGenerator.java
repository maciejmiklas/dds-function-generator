package org.ddf.helper;

import java.awt.*;
import java.util.List;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import javax.swing.*;

public class SineGenerator extends JFrame {

	public static void main(String[] args) {
		SineGenerator generator = new SineGenerator();
		List<Point> points = generator.generateSine();
		generator.draw(points);
		// generator.printPoints(points);
		generator.printCArray(points);
	}

	public void printCArray(List<Point> points) {
		StringBuilder sb = new StringBuilder();
		sb.append("static int8_t const lookup_table[" + points.size() + "]={");
		points.forEach(p -> sb.append("0x").append(Integer.toHexString(p.y).toUpperCase()).append(","));
		System.out.print(sb.toString());
    }

	public List<Point> generateSine() {
	List<Point> sinePoints = IntStream
		.iterate(0, i -> i + 2)
		.limit(181)
		.mapToObj(
			angle -> new Point(
				angle,
				(int) Math.round(Math.sin(Math.toRadians(angle)) * 127.5 + 127.5)))
		.collect(Collectors.toList());

	return sinePoints;
    }

	public void printPoints(List<Point> points) {
	IntStream.range(0, points.size()).forEach(idx -> {
	    Point point = points.get(idx);
	    System.out.println(idx + " -> " + point.x + " -> " + point.y);
	});
    }

	public void draw(List<Point> points) {
		setLayout(new BorderLayout());
		setSize(800, 600);
		setTitle("WaveGenerator");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setVisible(true);
		add(new DrawPanel(points), BorderLayout.CENTER);
	}

	class DrawPanel extends JPanel {
		private final List<Point> points;

		DrawPanel(List<Point> points) {
			this.points = points;
		}

		@Override
	protected void paintComponent(Graphics g) {
	    super.paintComponent(g);

	    g.drawLine(50, 50, 50, 400);
	    g.drawLine(51, 50, 51, 400);

	    g.drawLine(50, 400, 600, 400);
	    g.drawLine(50, 401, 600, 401);

	    g.drawString("X", 620, 400);
	    g.drawString("Y", 50, 30);

	    Polygon polygon = points.stream().collect(
		    Collector.of(Polygon::new, (pol, point) -> pol.addPoint(point.x + 50, 400 - point.y), (
			    pol1,
			    pol2) -> pol1));
	    g.setColor(Color.red);
	    g.drawPolyline(polygon.xpoints, polygon.ypoints, polygon.npoints);
	}
	}

	public static final class Point {
		public final int x;
		public final int y;

		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

	}

}
