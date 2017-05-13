#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using std::string;

string get_argument(int argc, char* argv[], string argument_to_find) {
	string argument;
	for (int i = 1; i < argc; ++i) {
		if (string(argv[i]) == argument_to_find) {
			if (i + 1 < argc) {
				argument = argv[++i];
			} else {
				argument = "";
			}
		}
	}
	return argument;
}

int main(int argc, char* argv[]) {
	string input_file = get_argument(argc, argv, "-i");
	if (input_file == "") {
		std::cerr << "Please specify input file with -i flag." << std::endl;
	}

	const string TO_BRAINFUCK = "to_b";
	const string TO_SMILEY = "to_s";

	string output_file = get_argument(argc, argv, "-o");
	string transpiler_mode = get_argument(argc, argv, "-c");
	if (transpiler_mode == "") {
		// If transpile mode is empty, try to guess what the user wants
		if (output_file.substr(output_file.find_last_of(".") + 1) == "b") {
			// Output file ends with b, defaulting Smiley to Brainfuck mode
			transpiler_mode = TO_BRAINFUCK;
		} else if (output_file.substr(output_file.find_last_of(".") + 1)
				== "s") {
			// Output file ends with s, defaulting Brainfuck to Smiley mode
			transpiler_mode = TO_SMILEY;
		} else {
			std::cerr << "Please specify transcompile mode with -c flag." << std::endl;
		}
	} else if (transpiler_mode != TO_BRAINFUCK
			&& transpiler_mode != TO_SMILEY) {
		std::cerr << "Please specify a valid transcompile mode." << std::endl;
	}

	std::map<string, string> to_b;
	to_b[":>"] = ">";
	to_b[":<"] = "<";
	to_b[":)"] = "+";
	to_b[":("] = "-";
	to_b[":O"] = ".";
	to_b[";)"] = ",";
	to_b[":["] = "[";
	to_b[":]"] = "]";

	std::map<string, string> to_s;
	to_s[">"] = ":>";
	to_s["<"] = ":<";
	to_s["+"] = ":)";
	to_s["-"] = ":(";
	to_s["."] = ":O";
	to_s[","] = ";)";
	to_s["["] = ":[";
	to_s["]"] = ":]";

	std::map<string, string> m = (transpiler_mode == TO_BRAINFUCK ? to_b : to_s);

	std::ifstream in;
	in.open(input_file);

	if (in.is_open()) {
		string result;
		string line;
		if (transpiler_mode == TO_BRAINFUCK) {
			while (std::getline(in, line)) {
				// Transcompile Smiley to Brainfuck
				std::stringstream ss(line);
				string c;
				while (getline(ss, c, ' ')) {
					result += m[c];
				}
			}
		} else if (transpiler_mode == TO_SMILEY) {
			while (getline(in, line)) {
				// Transcompile Brainfuck to Smiley
				for (size_t i = 0; i < line.size(); ++i) {
					string c(1, line[i]);
					result += m[c] + " ";
				}
			}
		}

		std::ofstream out;
		if (output_file == "") {
			string extension = (transpiler_mode == TO_BRAINFUCK ? ".b" : ".s");
			output_file = "output" + extension;
		}
		out.open(output_file);
		out << result << std::endl;
		out.close();
	}

	return 0;
}
