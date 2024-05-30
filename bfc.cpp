#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

void generate_c_code(const string& bf_file, const string& c_file) {
    ifstream input(bf_file);
    ofstream output(c_file);

    output << "#include <stdio.h>\n";
    output << "#include <stdlib.h>\n";
    output << "#define MEMORY_SIZE 30000\n\n";
    output << "char memory[MEMORY_SIZE] = {0};\n";
    output << "char *ptr = memory;\n\n";
    output << "int main() {\n";
    
    char ch;
    while (input.get(ch)) {
        switch (ch) {
            case '>': output << "    ++ptr;\n";
                break;
            case '<': output << "    --ptr;\n";
                break;
            case '+': output << "    ++(*ptr);\n";
                break;
            case '-': output << "    --(*ptr);\n";
                break;
            case '[': output << "    while (*ptr) {\n";
                break;
            case ']': output << "    }\n";
                break;
            case '.': output << "    putchar(*ptr);\n";
                break;
            case ',': output << "    *ptr = getchar();\n";
                break;
            default: break;
        }
    }

    output << "    system(\"pause\");\n";

    output << "    return 0;\n}\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <brainfuck_file>\n";
        return 1;
    }

    string bf_file = argv[1];
    string c_file = bf_file.substr(0, bf_file.find_last_of('.')) + ".c";
    generate_c_code(bf_file, c_file);

    cout << "generated C code: " << c_file << endl;

    string exe_file = bf_file.substr(0, bf_file.find_last_of('.'));
    string compile_command = "gcc -o " + exe_file + " " + c_file;

    cout << "compiling C file with gcc...\n";
    int compile_result = system(compile_command.c_str());

    if (compile_result != 0) {
        cerr << "Compilation failed.\n";
        return 1;
    }

    cout << "compiled file: " << exe_file << ".exe\n";

    remove(c_file.c_str());
    cout << "temporary C file deleted.\n";

    return 0;
}