#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAXLEN = 100;

class Node {
public:
    string label;
    Node* children[MAXLEN];
    int num_children;

    Node(string label) {
        this->label = label;
        num_children = 0;
    }

    void addChild(Node* child) {
        children[num_children++] = child;
    }

    void printDOT(ofstream& fout) {
        fout << "\"" << this << "\" [label=\"" << label << "\"]" << endl;        for (int i = 0; i < num_children; i++) {            fout << "\"" << this << "\" -> \"" << children[i] << "\"" << endl;
            children[i]->printDOT(fout);
        }
    }
};

class Parser {
public:
    char* input;
    int pos;

    Parser(char* input) {
        this->input = input;
        pos = 0;
    }

    Node* parseStatement() {
        if (input[pos] == 'i' && input[pos+1] == 'f') {
            pos += 2;
            Node* cond = parseExpression();
            Node* body = parseStatement();
            Node* node = new Node("if");
            node->addChild(cond);
            node->addChild(body);
            return node;
        } else if (input[pos] == 'w' && input[pos+1] == 'h' && input[pos+2] == 'i' && input[pos+3] == 'l' && input[pos+4] == 'e') {
            pos += 5;
            Node* cond = parseExpression();
            Node* body = parseStatement();
            Node* node = new Node("while");
            node->addChild(cond);
            node->addChild(body);
            return node;
        } else if (input[pos] == 'f' && input[pos+1] == 'o' && input[pos+2] == 'r') {
            pos += 3;
            Node* init = parseExpression();
            Node* cond = parseExpression();
            Node* step = parseExpression();
            Node* body = parseStatement();
            Node* node = new Node("for");
            node->addChild(init);
            node->addChild(cond);
            node->addChild(step);
            node->addChild(body);
            return node;
        } else if (input[pos] == '{') {
            pos++;
            Node* node = new Node("block");
            while (input[pos] != '}') {
                node->addChild(parseStatement());
            }
            pos++;
            return node;
        } else {
            Node* node = parseExpression();
            if (input[pos] == '=') {
                pos++;
                Node* value = parseExpression();
                Node* assign = new Node("=");
                assign->addChild(node);
                assign->addChild(value);
                return assign;
            } else {
                return node;
            }
        }
    }

    Node* parseExpression() {
        Node* node = parseTerm();
        while (input[pos] == '+' || input[pos] == '-') {
            char op = input[pos++];
            Node* rhs = parseTerm();
            Node* new_node = new Node(string(1, op));
            new_node->addChild(node);
            new_node->addChild(rhs);
            node = new_node;
        }
        return node;
    }

    Node* parseTerm() {
        Node* node = parseFactor();
        while (input[pos] == '*' || input[pos] == '/') {
            char op = input[pos++];
            Node * rhs = parseFactor();
        Node* new_node = new Node(string(1, op));
        new_node->addChild(node);
        new_node->addChild(rhs);
        node = new_node;
    }
    return node;
}

Node* parseFactor() {
    if (input[pos] >= '0' && input[pos] <= '9') {
        string num_str;
        while (input[pos] >= '0' && input[pos] <= '9') {
            num_str += input[pos++];
        }
        return new Node(num_str);
    } else if (input[pos] >= 'a' && input[pos] <= 'z') {
        string var_name;
        while (input[pos] >= 'a' && input[pos] <= 'z') {
            var_name += input[pos++];
        }
        return new Node(var_name);
    } else if (input[pos] == '(') {
        pos++;
        Node* node = parseExpression();
        pos++;
        return node;
    } else {
        cout << "Error: Invalid input" << endl;
        exit(1);
    }
}

};

int main() {
char input[MAXLEN];
cout << "Enter input: ";
cin.getline(input, MAXLEN);

Parser parser(input);
Node* parse_tree = parser.parseStatement();

ofstream fout("parse_tree.dot");
fout << "digraph {" << endl;
parse_tree->printDOT(fout);
fout << "}" << endl;
fout.close();

cout << "Parse tree saved to parse_tree.dot" << endl;

return 0;}
