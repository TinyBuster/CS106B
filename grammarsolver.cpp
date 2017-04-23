/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name: Tiny Buster
 * Section leader: Tiny Buster
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "random.h"
#include "map.h"
#include "error.h"

using namespace std;

string findGrammer(string symbol, Map<string, Vector<string> > &dict, string str);
string randomString(Vector<string> &v_str);
bool isTerminal(string symbol, Map<string, Vector<string> > &dict);

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    string line;
    Map<string, Vector<string> > dict;
    Vector<string> value;
    Vector<string> grammer;

    while (getline(input, line)) {
        Vector<string> v = stringSplit(line, "::");
        string key =v[0];
        string value_string = v[1];
        value = stringSplit(value_string.substr(1), "|");
        if(dict.containsKey(key)) {
            error("The input file is illegal, it has more than one same key");
        } else {
            dict[key] = value;
        }
    }

    for (int i = 0; i < times; i++) {
        grammer.add(findGrammer(symbol, dict, ""));
    }

    return grammer;
}

/*
 * I'm too lazy so that I don't want to write explation for 
 * this function. = =
 * --------------------------------------------------------
 * Yep, call me lazy tiny buster.
 * Usage: findGrammer(symbol, dict, str);
 */ 
string findGrammer(string symbol, Map<string, Vector<string> > &dict, string str) {
    if (symbol == "")
        error("The input file is illegal, it has more than one same key");
    if (!dict.containsKey(symbol))
        return symbol;
    if (isTerminal(symbol, dict)) {
        return randomString(dict[symbol]);
    } else {
        string tmp = randomString(dict[symbol]);
        Vector<string> next = stringSplit(tmp, " ");
        for (int i = 0; i < next.size(); i++) {
            str = trim(str) + " " + trim(findGrammer(next[i], dict, ""));
        }
        return str;
    }
}

/*
 * I'm too lazy so that I don't want to write explation for 
 * this function. = =
 * --------------------------------------------------------
 * Yep, call me lazy tiny buster.
 * Usage: isTerminal(symbol, dict);
 */ 
bool isTerminal(string symbol, Map<string, Vector<string> > &dict) {
    for (int i = 0; i < dict[symbol].size(); i++) {
        Vector<string> next = stringSplit(dict[symbol][i], " ");
        for (int j = 0; j < next.size(); j++) {
            if (dict.containsKey(next[j]))
                return false;
        }
    }
    return true;
}

/*
 * I'm too lazy so that I don't want to write explation for 
 * this function. = =
 * --------------------------------------------------------
 * Yep, call me lazy tiny buster.
 * Usage: randomString(v_str);
 */ 
string randomString(Vector<string> &v_str) {
    if (v_str.isEmpty()) return "";
    int i = randomInteger(0, v_str.size() - 1);
    return v_str[i];
}
