import java.util.Random;

public class Coordinate {
	int x;
	int y;
	int max_x = 60;
	int max_y = 35;
	
	public Coordinate() {
		Random n = new Random();
		x = n.nextInt(max_x);
		y = n.nextInt(max_y);
	}
	
	public void Show() {
		System.out.println(x + ", " + y);
	}
}
