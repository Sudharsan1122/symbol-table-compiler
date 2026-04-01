#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Symbol {
    string name;
    string type;
    string value;
    string scope = "global";
    int line;
    bool updated = false;
};

vector<Symbol> symbols;
int errCount = 0;

// Trim spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

// Check integer
bool isInteger(const string& s) {
    if (s.empty()) return false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    for (; i < s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}

// Check number (float/double)
bool isNumber(const string& s) {
    if (s.empty()) return false;
    bool hasDot = false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    for (; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!isdigit(s[i])) return false;
    }
    return true;
}

// Validate variable name
bool isValidIdentifier(const string& name) {
    if (name.empty() || !isalpha(name[0])) return false;
    for (char c : name) {
        if (!isalnum(c) && c != '_') return false;
    }
    return true;
}

// Show Symbol Table
void showSymbolTable() {
    if (symbols.empty()) {
        cout << "\nNo symbols found.\n";
        return;
    }

    vector<Symbol> sorted = symbols;
    sort(sorted.begin(), sorted.end(), [](const Symbol& a, const Symbol& b) {
        if (a.type != b.type) return a.type < b.type;
        return a.name < b.name;
    });

    cout << "\n=== SYMBOL TABLE ===\n";
    cout << left << setw(12) << "Name" 
         << setw(10) << "Type" 
         << setw(18) << "Value" 
         << setw(10) << "Scope" 
         << "Line" << endl;
    cout << string(58, '-') << endl;

    for (const auto& s : sorted) {
        cout << left << setw(12) << s.name 
             << setw(10) << s.type 
             << setw(18) << s.value 
             << setw(10) << s.scope 
             << s.line;
        if (s.updated) cout << "   [updated]";
        cout << endl;
    }
    cout << string(58, '-') << endl;
}

// Compile each line
void compileLine(const string& raw, int lineNo) {
    string line = trim(raw);
    if (line.empty() || line[0] == '/') return;

    stringstream ss(line);
    vector<string> tokens;
    string token;

    while (ss >> token) {
        if (!token.empty() && token.back() == ';') {
            if (token.size() > 1)
                tokens.push_back(token.substr(0, token.size() - 1));
            tokens.push_back(";");
        } else {
            tokens.push_back(token);
        }
    }

    if (tokens.size() < 2) return;

    string type = tokens[0];

    // ✅ VALID TYPES
    vector<string> validTypes = {
        "int","float","double","char","string","bool","long","short"
    };

    if (find(validTypes.begin(), validTypes.end(), type) == validTypes.end()) {
        cout << "ERROR  (line " << lineNo << "): Invalid type '" << type << "'\n";
        errCount++;
        return;
    }

    string name, value = "undefined";

    // ✅ Handle a=5 and a = 5
    if (tokens[1].find('=') != string::npos) {
        size_t pos = tokens[1].find('=');
        name = tokens[1].substr(0, pos);
        value = tokens[1].substr(pos + 1);
    }
    else if (tokens.size() >= 4 && tokens[2] == "=") {
        name = tokens[1];
        value = tokens[3];
    }
    else {
        name = tokens[1];
    }

    // ✅ Identifier validation
    if (!isValidIdentifier(name)) {
        cout << "ERROR  (line " << lineNo << "): Invalid variable name '" << name << "'\n";
        errCount++;
        return;
    }

    // ✅ Value validation
    if (value != "undefined") {
        bool valid = true;
        string error = "";

        if (type == "string" && (value.front() != '"' || value.back() != '"')) {
            valid = false; error = "string expects \"...\"";
        } 
        else if (type == "char" && (value.front() != '\'' || value.back() != '\'')) {
            valid = false; error = "char expects 'x'";
        } 
        else if ((type == "int" || type == "long" || type == "short") && !isInteger(value)) {
            valid = false; error = "integer expected";
        } 
        else if ((type == "float" || type == "double") && !isNumber(value)) {
            valid = false; error = "number expected";
        } 
        else if (type == "bool" && value != "true" && value != "false") {
            valid = false; error = "bool expects true/false";
        }

        if (!valid) {
            cout << "ERROR  (line " << lineNo << "): " << error << " but got " << value << endl;
            errCount++;
            return;
        }

        if ((type == "float" || type == "double") && isInteger(value)) {
            value += ".0";
        }
    }

    // ✅ Update if exists
    for (auto& sym : symbols) {
        if (sym.name == name) {
            sym.value = value;
            sym.updated = true;
            cout << "UPDATE (line " << lineNo << "): " << name << " = " << value << endl;
            return;
        }
    }

    // ✅ Insert new symbol
    symbols.push_back({name, type, value, "global", lineNo, false});
    cout << "OK     (line " << lineNo << "): " << type << " " << name << " = " << value << endl;
}

// MAIN
int main() {
    cout << "==========================================\n";
    cout << "   Symbol Table Compiler (Final Version)\n";
    cout << "==========================================\n";
    cout << "Enter code line by line\n";
    cout << "Type 'compile' to finish\n\n";

    string input;
    int lineNo = 1;

    while (true) {
        cout << lineNo << "> ";
        getline(cin, input);

        if (input == "compile") break;

        compileLine(input, lineNo);
        lineNo++;
    }

    cout << "\n==========================================\n";
    cout << "              COMPILATION COMPLETE\n";
    cout << "==========================================\n";
    cout << "Total Symbols : " << symbols.size() << "\n";
    cout << "Errors        : " << errCount << "\n";

    showSymbolTable();

    cout << "\nProgram finished. Thank you!\n";
    return 0;
}