package test.quick2zyme;

import static org.junit.Assert.*;

import static quick2zyme.Level.*;

import org.junit.Test;

import quick2zyme.Arduino;
import quick2zyme.MockAsker;

public class ArduinoTester {
	private static final String FOO = "Foo";
	MockAsker asker = new MockAsker();
	Arduino arduino = new Arduino(asker);

	@Test
	public void sendsMessageViaAsker() {
		arduino.send(FOO);
		assertEquals(FOO, asker.sentString());
	}
	
	@Test
	public void setsAPin() {
		arduino.digitalWrite(13, HIGH);
		assertEquals("13d1o", asker.sentString());
	}
	
}

