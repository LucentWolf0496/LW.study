#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

double evaluate(vector<string>& tokens, int& index) {
    string token = tokens[index];
    index++;
    if (token == "+") {
        double left = evaluate(tokens, index);
        double right = evaluate(tokens, index);
        return left + right;
    } else if (token == "-") {
        double left = evaluate(tokens, index);
        double right = evaluate(tokens, index);
        return left - right;
    } else if (token == "*") {
        double left = evaluate(tokens, index);
        double right = evaluate(tokens, index);
        return left * right;
    } else if (token == "/") {
        double left = evaluate(tokens, index);
        double right = evaluate(tokens, index);
        return left / right;
    } else {
        return atof(token.c_str());
    }
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<string> tokens;
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    int index = 0;
    double result = evaluate(tokens, index);
    printf("%f\n", result);
    return 0;
}