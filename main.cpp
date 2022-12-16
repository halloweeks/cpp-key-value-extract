#include <iostream>
#include <vector>
#include <sstream>

class config {
	private:
	char KEY[100] = {0};
	char VALUE[100] = {0};
	bool START = true, END = false;
	int index = 0;
	std::vector <std::string> keys, values;
	std::string data;
	public:
	bool parse(const char *);
	bool isset(std::string);
	config& value(std::string);
	bool Bool();
	int Int();
	unsigned int Uint();
	long Long();
	unsigned long Ulong();
	long long LongLong();
	unsigned long long UlongLong();
	float Float();
	double Double();
	long double LongDouble();
	std::string String();
};

// extract key value
bool config::parse(const char *str) {
	for (long int i = 0; i < strlen(str)+1; i++) {
		if (START) {
			if (str[i] == '=') {
				START = false;
				index = 0;
			} else {
				if (str[i] != '\r') {
					if (str[i] != '\n') {
						// key must be less than 100 characters
						if (index != 100) {
							KEY[index++] = str[i];
						} else {
							return false;
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
						// value must be less than 100 characters
						if (index != 100) {
							VALUE[index++] = str[i];
						} else {
							return false;
						}
					}
				}
			}
			if (END) {
				keys.push_back(KEY);
				values.push_back(VALUE);
				memset(KEY, 0, 100);
				memset(VALUE, 0, 100);
				START = true;
				END = false;
			}
		}
	}
	return true;
}

bool config::isset(std::string key) {
	for (unsigned int index = 0; index < keys.size(); index++) {
		if (key == keys[index]) {
			return true;
		}
	}
	return false;
}


config& config::value(std::string key) {
	for (unsigned int index = 0; index < keys.size(); index++) {
		if (key == keys[index]) {
			data = values[index];
			break;
		}
	}
	return *this;
}


bool config::Bool() {
	if (data == "1" || data == "true") {
		return true;
	}
	
	if (data == "0" || data == "false") {
		return false;
	}
	return false;
}

int config::Int() {
	std::istringstream reader(data);
    int val = 0;
    reader >> val;
    return val;
}

unsigned int config::Uint() {
	std::istringstream reader(data);
    unsigned int val = 0;
    reader >> val;
    return val;
}

long config::Long() {
	std::istringstream reader(data);
    long val = 0;
    reader >> val;
    return val;
}

unsigned long config::Ulong() {
    std::istringstream reader(data);
    unsigned int val = 0;
    reader >> val;
    return val;
}

long long config::LongLong() {
	std::istringstream reader(data);
    long long val = 0;
    reader >> val;
    return val;
}

unsigned long long config::UlongLong() {
	std::istringstream reader(data);
    unsigned long long val = 0;
    reader >> val;
    return val;
}

float config::Float() {
	std::istringstream reader(data);
    float val = 0.0;
    reader >> val;
    return val;
}

double config::Double() {
	std::istringstream reader(data);
    double val = 0.0;
    reader >> val;
    return val;
}

long double config::LongDouble() {
	std::istringstream reader(data);
    long double val = 0.00;
    reader >> val;
    return val;
}

std::string config::String() {
	return data;
}

config config;

int main() {
	const char *str = "username=user123\r\nemail=email@email.com\r\npassword=123100";
	
	if (config.parse(str)) {
		std::cout << "Key value parse done\n";
	} else {
		std::cout << "Failed to parse key value\n";
		return -1;
	}
	
	std::cout << std::boolalpha;
	std::cout << "key username exist: '" << config.isset("username") << "'\n";
	std::cout << "value of username: '" << config.value("username").String() << "'\n";
	
	std::cout << "key email exist: '" << config.isset("email") << "'\n";
	std::cout << "value of email: '" << config.value("email").String() << "'\n";
	
	std::cout << "key password exist: '" << config.isset("password") << "'\n";
	std::cout << "value of password: '" << config.value("password").String() << "'\n";
	
	return 0;
}
