package quick2zyme;

public class MessageBuilder {
	
	public static String build(String...messages) {
		String result = "";
		for (String message: messages) {
			result += message;
		}
		return result;
	}
	
	public static String command(int value, char commandCharacter) {
		return String.format("%d%s", value, commandCharacter);
	}
	
	 

}
