#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string get_argument(int argc, char* argv[], string argument_to_find) {
	vector<string> arguments;
	string argument;
	for (int i = 1; i < argc; ++i) {
		if (string(argv[i]) == argument_to_find) {
			if (i + 1 < argc) {
				argument = argv[++i];
			} else {
				argument = "";
			}
		} else {
			arguments.push_back(argv[i]);
		}
	}
	return argument;
}

int main(int argc, char* argv[]) {
	string input_file = get_argument(argc, argv, "-i");
	if (input_file == "") {
		cerr << "Please specify input file with -i flag." << endl;
	}

	string output_file = get_argument(argc, argv, "-o");

	string transpiler_mode = get_argument(argc, argv, "-c");
	if (transpiler_mode == "") {
		// If transpile mode is empty, try to guess what the user wants
		if (input_file.substr(input_file.find_last_of(".") + 1) == "s") {
			// Input file ends with s, defaulting Smiley to Brainfuck mode
			transpiler_mode = "to_b";
		} else if (input_file.substr(input_file.find_last_of(".") + 1) == "b") {
			// Input file ends with b, defaulting Brainfuck to Smiley mode
			transpiler_mode = "to_s";
		} else {
			cerr << "Please specify transcompile mode with -c flag." << endl;
		}
	} else if (transpiler_mode != "to_b" && transpiler_mode != "to_s") {
		cerr << "Please specify a valid transcompile mode." << endl;
	}

	map<string, string> to_b;
	to_b[":>"] = ">";
	to_b[":<"] = "<";
	to_b[":-)"] = "+";
	to_b[":-("] = "-";
	to_b[":O"] = ".";
	to_b[";)"] = ",";
	to_b["<3"] = "]";
	to_b["</3"] = "[";

	map<string, string> to_s;
	to_s[">"] = ":>";
	to_s["<"] = ":<";
	to_s["+"] = ":-)";
	to_s["-"] = ":-(";
	to_s["."] = ":O";
	to_s[","] = ";)";
	to_s["]"] = "<3";
	to_s["["] = "</3";

	map<string, string> m = (transpiler_mode == "to_b" ? to_b : to_s);

	ifstream in;
	in.open(input_file);

	if (in.is_open()) {
		string result;
		string line;
		if (transpiler_mode == "to_b") {
			while (getline(in, line)) {
				// Transcompile Smiley to Brainfuck
				stringstream ss(line);
				string c;
				while (getline(ss, c, ' ')) {
					if (m.find(c) != m.end()) {
						result += m[c];
					}
				}
			}
		} else if (transpiler_mode == "to_s") {
			while (getline(in, line)) {
				// Transcompile Brainfuck to Smiley
				for (size_t i = 0; i < line.size(); ++i) {
					string c(1, line[i]);
					if (m.find(c) != m.end()) {
						result += m[c] + " ";
					}
				}
			}
		}
		in.close();

		ofstream out;
		if (output_file == "") {
			string extension = (transpiler_mode == "to_b" ? ".b" : ".s");
			output_file = "output" + extension;
		}
		out.open(output_file);
		out << result << endl;
		out.close();
	}
	return 0;
}
