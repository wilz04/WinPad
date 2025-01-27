class Client {
	
	private var cx: XMLSocket;
	
	public function Client(ip: String) {
		cx = new XMLSocket();
		if (!cx.connect(ip, 4000)) {
			fscommand("quit", "");
		}
		cx.onData = recv;
	}
	
	private function recv(cmd: String): Void {
		if (cmd != "") {
			_global.textArea.text = cmd;
		}
	}
	
	public function fNew(fileName: String): Void {
		fClose();
		cx.send("1|" + fileName);
	}
	
	public function fOpen(fileName: String): Void {
		cx.send("2|" + fileName);
	}
	
	public function fSave(fileName: String): Void {
		if (fileName == null) {
			cx.send("3|" + _global.textArea.text);
		} else {
			cx.send("4|" + fileName + "|" + _global.textArea.text);
		}
	}
	
	public function fClose(): Void {
		_global.textArea.text = "";
	}
	
	public function exit(): Void {
		cx.send("5");
		cx.close();
		fscommand("quit", "");
	}
	
	public function replace(oldWord: String, newWord: String): Void {
		var oldText = _global.textArea.text;
		var newText = "";
		var temp: String = "";
		for (var i:Number=0; i<=length(oldText); i++) {
			if ((ord(oldText.charAt(i)) < 65) || (ord(oldText.charAt(i)) > 165)) {
				if (temp == oldWord) {
					newText += newWord + oldText.charAt(i);
				} else {
					newText += temp + oldText.charAt(i);
				}
				temp = "";
			} else {
				temp += oldText.charAt(i);
			}
		}
		_global.textArea.text = newText;
	}
	
}
