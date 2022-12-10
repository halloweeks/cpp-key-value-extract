#include <iostream>

int main() {
	char str[] = "name=hello\r\r\n\npass=12345\r\nuser_id=55555\nhhfdjkkjbvg=jjjhhh\rbjjjggg=hhh\rhhhffbnn";
	
	bool START = true, END = false;
	char KEY[1024] = {0};
	char VALUE[1024] = {0};
	int index = 0;
	
	for (int i = 0; i < sizeof(str); i++) {
		if (START) {
			if (str[i] == '=') {
				START = false;
				index = 0;
			} else {
				if (str[i] != '\r') {
					if (str[i] != '\n') {
						if (index != 1024) {
							KEY[index++] = str[i];
						}
					}
				}
			}
		} else if (!END) {
			if (str[i] == '\r' || str[i] == '\n' || str[i] == '\0') {
				END = true;
				index = 0;
			} else {
				if (str[i] != '\r') {
					if (str[i] != '\n') {
						if (index != 1024) {
							VALUE[index++] = str[i];
						}
					}
				}
			}
			if (END) {
				std::cout << "KEY: '" << KEY << "' VALUE: '" << VALUE << "'\n";
				memset(KEY, 0, 1024);
				memset(VALUE, 0, 1024);
				START = true;
				END = false;
				index = 0;
			}
		}
	}
	
	return 0;
}
