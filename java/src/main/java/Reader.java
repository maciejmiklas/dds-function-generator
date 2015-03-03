import java.io.InputStream;
import java.net.URL;

/** @author Maciej Miklas */
public class Reader {

	public static void main(String ... a) throws Exception{
		URL path = Thread.currentThread().getContextClassLoader().getResource("test.txt");
		System.out.println(path);
		InputStream io =  path.openStream();
		byte[] buf = new byte[10];
		io.read(buf);
		System.out.println(new String(buf));
		io.close();

	}
}
