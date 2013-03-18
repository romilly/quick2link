package quick2zyme;

import static quick2zyme.MessageBuilder.*;

public class Arduino {
	private Asker asker;

	public Arduino(Asker asker) {
		this.asker = asker;
	}

	public void send(String string) {
		asker.send(string);
	}

	public void digitalWrite(int pin, Level level) {
		asker.send((build(command(pin, 'd'), command(level.level(),'o'))));
	}

}
