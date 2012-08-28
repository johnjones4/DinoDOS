import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;


public class LineConverter {

	/**
	 * @param args
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		Scanner input = new Scanner(new File(args[0]));
		String file = "";
		while(input.hasNextLine())
		{
			file += input.nextLine() + '\r';
		}
		PrintWriter out = new PrintWriter(new FileWriter(new File(args[1])));
		out.print(file);
		out.close();
	}

}
