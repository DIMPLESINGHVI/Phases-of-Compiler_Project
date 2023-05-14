#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stack>

using namespace std;

bool isPunctuator(char ch) // check if the given character is a punctuator or not
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|')
    {
        return true;
    }
    return false;
}

bool validIdentifier(char *str) // check if the given identifier is valid or not
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isPunctuator(str[0]) == true)
    {
        return false;
    } // if first character of string is a digit or a special character, identifier is not valid
    int i, len = strlen(str);
    if (len == 1)
    {
        return true;
    } // if length is one, validation is already completed, hence return true
    else
    {
        for (i = 1; i < len; i++) // identifier cannot contain special characters
        {
            if (isPunctuator(str[i]) == true)
            {
                return false;
            }
        }
    }
    return true;
}

bool isOperator(char ch) // check if the given character is an operator or not
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&')
    {
        return true;
    }
    return false;
}

bool isKeyword(char *str) // check if the given substring is a keyword or not
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "volatile") || !strcmp(str, "typedef") || !strcmp(str, "enum") || !strcmp(str, "const") || !strcmp(str, "union") || !strcmp(str, "extern") || !strcmp(str, "bool"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isNumber(char *str) // check if the given substring is a number or not
{
    int i, len = strlen(str), numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0; i < len; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        }
        else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
        {
            return false;
        }
    }
    return true;
}

char *subString(char *realStr, int l, int r) // extract the required substring from the main string
{
    int i;

    char *str = (char *)malloc(sizeof(char) * (r - l + 2));

    for (i = l; i <= r; i++)
    {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}

void parse(char *str) // parse the expression
{
    int left = 0, right = 0,count=0;
    int len = strlen(str);
    while (right <= len && left <= right)
    {
        if (isPunctuator(str[right]) == false) // if character is a digit or an alphabet
        {
            right++;
        }

        if (isPunctuator(str[right]) == true && left == right) // if character is a punctuator
        {
            if (isOperator(str[right]) == true)
            {
                std::cout << str[right] << " IS AN OPERATOR\n";
                count++;
            }
            right++;
            left = right;
        }
        else if (isPunctuator(str[right]) == true && left != right || (right == len && left != right)) // check if parsed substring is a keyword or identifier or number
        {
            char *sub = subString(str, left, right - 1); // extract substring

            if (isKeyword(sub) == true)
            {
                cout << sub << " IS A KEYWORD\n";
                count++;
            }
            else if (isNumber(sub) == true)
            {
                cout << sub << " IS A NUMBER\n";
                count++;
            }
            else if (validIdentifier(sub) == true && isPunctuator(str[right - 1]) == false)
            {
                cout << sub << " IS A VALID IDENTIFIER\n";
                count++;
            }
            else if (validIdentifier(sub) == false && isPunctuator(str[right - 1]) == false)
            {
                cout << sub << " IS NOT A VALID IDENTIFIER\n";
            }

            left = right;
        }
    }
    cout<<"\nTotal number of tokens: "<<count;
    return;
}

bool isOperand(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

bool isValidExpression(char c[])
{
    stack<char> stk;
    int n = strlen(c);
    for (int i = 0; i < n; i++)
    {
        if (isOperand(c[i]))
        {
            if (!isOperator(c[i + 1]) && c[i + 1] != ')' && i != n - 1)
                return false;
        }
        else if (isOperator(c[i]))
        {
            if (c[i + 1] == ')' || i == n - 1)
                return false;
        }
        else if (c[i] == '(')
        {
            stk.push(c[i]);
        }
        else if (c[i] == ')')
        {
            if (stk.empty() || stk.top() != '(')
                return false;
            else
                stk.pop();
        }
    }
    if (!stk.empty())
        return false;
    return true;
}


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
        cout << "\nError: Invalid input" << endl;
        exit(1);
    }
}

};


#define SIZE 100

char stk[SIZE];
int top = -1;

void push(char item)
{
    if (top >= SIZE - 1)
    {
        printf("\nStack Overflow.");
    }
    else
    {
        top = top + 1;
        stk[top] = item;
    }
}
char pop()
{
    char item;

    if (top < 0)
    {
        printf("\nStack under flow: invalid infix expression");
        getchar();
        exit(1);
    }
    else
    {
        item = stk[top];
        top = top - 1;
        return (item);
    }
}
int is_operator(char symbol)
{
    if (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-' || symbol == '=')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int precedence(char symbol)
{
    if (symbol == '^')
    {
        return (3);
    }
    else if (symbol == '*' || symbol == '/')
    {
        return (2);
    }
    else if (symbol == '+' || symbol == '-')
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

void InfixToPostfix(char infix_exp[], char postfix_exp[])
{
    int i, j;
    char item;
    char x;

    push('(');
    strcat(infix_exp, ")");

    i = 0;
    j = 0;
    item = infix_exp[i];

    while (item != '\0')
    {
        if (item == '(')
        {
            push(item);
        }
        else if (isdigit(item) || isalpha(item))
        {
            postfix_exp[j] = item;
            j++;
        }
        else if (is_operator(item) == 1)
        {
            x = pop();
            while (is_operator(x) == 1 && precedence(x) >= precedence(item))
            {
                postfix_exp[j] = x;
                j++;
                x = pop();
            }
            push(x);

            push(item);
        }
        else if (item == ')')
        {
            x = pop();
            while (x != '(')
            {
                postfix_exp[j] = x;
                j++;
                x = pop();
            }
        }
        else
        {
            printf("\nInvalid infix Expression.\n");
            getchar();
            exit(1);
        }
        i++;

        item = infix_exp[i];
    }
    if (top > 0)
    {
        printf("\nInvalid infix Expression.\n");
        getchar();
        exit(1);
    }
    if (top > 0)
    {
        printf("\nInvalid infix Expression.\n");
        getchar();
        exit(1);
    }

    postfix_exp[j] = '\0';
}



int main()
{
    // lexical analysis
    //char c[100] = "m=n+3*p";
    char c[100];
    cout << "Enter the expression: ";
    cin.getline(c, 100);
    cout<<"\n";
    parse(c);

    // syntax analysis
    if (isValidExpression(c))
        cout << "\n\nHence the given expression is a Valid Expression\n";
    else
    {    cout << "\n\nHence the given expression is an Invalid Expression\n";
         exit(0);
    }     


    //keyword removed
    char result[100]; int i=0,j=0;
    while (c[i]) {
        // Check if the current character and the next 4 characters form a keyword
        if (!isKeyword(&c[i]) || !isalpha(c[i+5])) {
            result[j++] = c[i]; // Add the current character to the result
        }
        i++;
    }
    result[j] = '\0'; // Terminate the result with null character

    cout << "\nExpression without keywords: " << result << endl;



    // parse tree
    Parser parser(result);
    Node *parse_tree = parser.parseStatement();
    ofstream fout("parse_tree.dot");
    fout << "digraph {" << endl;
    parse_tree->printDOT(fout);
    fout << "}" << endl;
    fout.close();

    cout << "\nParse tree saved to parse_tree.dot" << endl;

    // postfix
    char postfix[SIZE];
    InfixToPostfix(result, postfix);
    printf("\nPostfix Expression: ");
    puts(postfix);

    return 0;
}