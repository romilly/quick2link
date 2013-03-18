package quick2zyme;

public class MockAsker implements Asker {

	private String sentString;

	public String sentString() {
		return sentString;
	}

	@Override
	public void send(String string) {
		sentString = string;	
	}

}
