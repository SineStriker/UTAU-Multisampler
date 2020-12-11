#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include  <direct.h> 

// Made by ZJZJ 2020/12/01

using namespace std;

int def_index;
int global_index;
int global_flags_len;
string global_flags;
string def_prefix;
vector<bool> ava;

bool startWith(const string& s, const string& s2) {
	return (s.substr(0, s2.size()) == s2);
}

string getGlobalFlags(const string& dir) {

	string file = dir + "\\" + "temp.bat";
	string line, s, s2;
	int eq;

	fstream fs(file, ios::in);

	if (!fs) {
		return "";
	}

	//cout << "Batch file is \"" << file << "\"" << endl;

	s = "";

	while (getline(fs, line)) {
		if (startWith(line, "@set flag=")) {

			eq = line.find_first_of('=');
			if (eq != line.size() - 1) {
				s = line.substr(eq + 1);
			}
			break;
		}
	}

	s2 = "";

	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '\"') {
			continue;
		}
		if (s[i] == 'e' || s[i] == 'E') {
			s2 += '/';
		}
		s2 += s[i];
	}

	return s2;

}

bool validNums(const vector<int>& v) {

	int max = v.size();
	int i;
	vector<bool> b;
	bool flag = true;

	for (i = 0; i < max; ++i) {
		b.push_back(false);
	}
	for (i = 0; i < max; ++i) {
		if (v[i] < 0 || v[i] >= max) {
			flag = false;
			break;
		}
		else {
			b[v[i]] = true;
		}
	}

	for (i = 0; i < max; ++i) {
		flag = flag && b[i];
		if (!flag) {
			break;
		}
	}

	return flag;
}

int str2int(const string& s) {
	stringstream ss(s);
	int n;
	ss >> n;
	return n;
}

bool isNormal(const string& s) {

	int i;
	bool flag = true;

	for (i = 0; i < s.size(); ++i) {
		if (s[i] < '0' || s[i] > '9') {
			flag = false;
			break;
		}
	}

	return flag;
}

int getResamplerIndex(string& s, const string& prefix, const bool& g = false) {

	bool flag;
	int i, last;

	string s2, cur;
	vector<int> a;

	flag = false;
	cur = "";

	if (!g) {
		s = s.substr(0, s.size() - global_flags_len);
	}

	last = -1;  // Save the previous prefix position

	for (i = 0; i < s.size(); ++i) {

		if (i < s.size() - prefix.size() + 1 && s.substr(i, prefix.size()) == prefix) {
			flag = true;
			if (!cur.empty()) {
				a.push_back(str2int(cur));
			}
			cur = "";
			last = i;
			i += prefix.size() - 1;
			continue;
		}
		else if (s[i] < '0' || s[i] > '9') {
			flag = false;
		}

		if (flag) {
			cur += s[i];
		}
		else {
			s2 += s[i];
		}
	}

	if (!cur.empty()) {
		a.push_back(str2int(cur));
	}

	s = s2;

	if (a.empty()) {

		if (!g) {
			s = s + global_flags;
		}
		if (ava[global_index]) {
			return global_index;
		}
		else {
			return def_index;
		}
	}
	else {
		if (a[0] < ava.size() && ava[a[0]]) {
			return a[0];
		}
		else {
			if (ava[global_index]) {
				return global_index;
			}
			else {
				return def_index;
			}
		}
	}
}

inline bool exists_test(const string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main(int argc, char* argv[]) {

	// Get current working directory

	char buffer[512];
	string dir;

	_getcwd(buffer, 512);
	dir = buffer;

	// Judge the parameters completeness

	bool use = false;

	def_prefix = "r";
	def_index = 0;

	if (argc >= 6) {
		use = true;
	}

	// Open Configuration

	string config_file = "C:\\ProgramData\\UTAU Plugin\\Multisampler\\config.ini";

	fstream fs(config_file, ios::in);
	string line;

	if (!fs) {
		cout << "Multisampler configuration not found." << endl;
		cout << "Please check \"" << config_file << "\"";
		if (!use) {
			getchar();
		}
		return -1;
	}

	// Load Configuration

	int eq, i;
	string pre, post;
	int num;
	string ex;

	vector<int> nums;
	vector<string> strs;
	vector<string> resamplers;

	while (getline(fs, line)) {

		eq = line.find_first_of('=');
		pre = post = "";

		if (eq != string::npos) {
			pre = line.substr(0, eq);

			if (isNormal(pre)) {
				num = str2int(pre);
				nums.push_back(num);

				if (eq != line.size() - 1) {
					post = line.substr(eq + 1);
					strs.push_back(post);
				}
				else {
					strs.push_back("");
				}
			}
			else {
				if (pre == "Prefix") {
					if (eq != line.size() - 1) {
						post = line.substr(eq + 1);
						def_prefix = post;
					}
				}
				else if (pre == "Default") {
					if (eq != line.size() - 1) {
						post = line.substr(eq + 1);
						if (isNormal(post)) {
							def_index = str2int(post);
						}
					}
				}
			}
		}
	}

	if (def_index >= nums.size() || !validNums(nums)) {
		cout << "Multisampler configuration Error." << endl;
		cout << "Please check \"" << config_file << "\"";
		if (!use) {
			getchar();
		}
		return -2;
	}

	fs.close();
	resamplers.resize(nums.size());

	for (i = 0; i < nums.size(); ++i) {
		resamplers[nums[i]] = strs[i];
	}

	for (i = 0; i < resamplers.size(); ++i) {
		ava.push_back(exists_test(resamplers[i]));
	}

	if (!use) {

		cout << "UTAU Multi-resampler  |  ";
		cout << "Prefix : " << def_prefix << "  |  ";
		cout << "Default : " << def_index;
		cout << endl;
		cout << endl;

		for (i = 0; i < resamplers.size(); ++i) {
			ex = ava[i] ? "" : "(Not Found)";
			cout << i << "  " << resamplers[i] << "  " << ex << endl;
		}

		getchar();
		return 0;

	}

	// Preparation

	int x;
	string s;
	string flags;
	string exe;
	string cmd;
	vector<string> argvs;

	global_flags = getGlobalFlags(dir);
	global_flags_len = global_flags.size();

	global_index = def_index;
	global_index = getResamplerIndex(global_flags, def_prefix, true);

	for (i = 0; i < argc; ++i) {
		argvs.push_back(argv[i]);
	}

	flags = argv[5];
	x = getResamplerIndex(flags, def_prefix);
	argvs[5] = flags;

	// Resampler not found
	if (x >= resamplers.size() || !exists_test(resamplers[x])) {
		x = def_index;
	}

	exe = resamplers[x];

	if (!exists_test(exe)) {
		cout << "Resampler Not Found." << endl;

		if (!use) {
			getchar();
		}
		return -3;
	}

	argvs[0] = exe;

	cout << "Flags is \"" << flags << "\"" << endl;
	cout << "Resampler " << x << " is \"" << exe << "\"" << endl;

	for (i = 0; i < argvs.size(); ++i) {
		if (i == 0 || i == 1 || i == 2 || i == 5) {
			s += "\"";
		}
		s += argvs[i];
		if (i == 0 || i == 1 || i == 2 || i == 5) {
			s += "\"";
		}
		if (i < argvs.size() - 1) {
			s += " ";
		}
	}

	cmd = "call " + s;
	const char* p = cmd.c_str();

	system(p);
	return 0;
}
