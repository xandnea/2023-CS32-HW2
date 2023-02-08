
#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {

    string test = "";
    string alphas = "";

    if (infix.size() == 0)
        return 1;

    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];

        if (isalpha(ch))
            alphas += ch;

        if ((isalpha(ch) && islower(ch)) || (ch == '(') || (ch == ')') || (ch == '!') || (ch == '&') || (ch == '|'))
            test += ch;
        else if (ch == ' ')
            continue;
        else
            return 1;            
    }

    char curr;
    char next;
    int parenthesis = 0;

    for (int i = 0; i < test.size(); i++) {
        curr = test[i];
        next = test[i + 1];

        switch (curr) {
            case '(':
                if (isalpha(next) || (next == '!') || (next == '(')) {
                    parenthesis++;
                    break;
                }
                else
                    return 1;
            case ')':
                if (isalpha(next) || (next == '!')) 
                    return 1;
                else {
                    parenthesis--;
                    break;
                }
            case '!':
                if (isalpha(next) || next == '(')
                    break;
                else
                    return 1;
            case '&':
            case '|':
                if (isalpha(next) || (next == '!') || (next == '('))
                    break;
                else
                    return 1;
            default:                                                        // if character
                if (isalpha(next) || (next == '!') || (next == '('))
                    return 1;
                else
                    break;
        }
    }
    
    if (parenthesis != 0) // if parenthesis is not 0 (there is an uneven amount of open and closed parenthesis) then return 1
        return 1;

    for (int i = 0; i < alphas.size(); i++) {
        char ch = alphas[i];

        if ((trueValues.contains(ch) || falseValues.contains(ch)) && !(trueValues.contains(ch) && falseValues.contains(ch))) // if ch appears in either true values or false values but not both
            continue;
        else {
            if (!(trueValues.contains(ch) || falseValues.contains(ch)))
                return 2;
            if (trueValues.contains(ch) && falseValues.contains(ch))
                return 3;
        }
    }

    postfix = "";
    stack<char> operatorStack;

    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];

        switch (ch) {
        default:
            postfix += ch;
            break;
        case ' ':
            break;
        case '(':
            operatorStack.push(ch);
            break;
        case ')':
            while (operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
            break;
        case '|':
            while ((!operatorStack.empty()) && (operatorStack.top() != '(')) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(ch);
            break;
        case '&':
            while ((!operatorStack.empty()) && (operatorStack.top() != '(') && (operatorStack.top() != '|')) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(ch);
            break;
        case '!':
            while ((!operatorStack.empty()) && (operatorStack.top() != '(') && (operatorStack.top() != '&') && (operatorStack.top() != '|')) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(ch);
            break;
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }


    stack<bool> operandStack;
    for (int i = 0; i < postfix.size(); i++) {
        char ch = postfix[i];

        if (isalpha(ch)) {
            if ((falseValues.contains(ch)) && (postfix[i + 1] == '!'))
                operandStack.push(true);
            else if ((trueValues.contains(ch)) && (postfix[i + 1] == '!'))
                operandStack.push(false);
            else if (trueValues.contains(ch))
                operandStack.push(true);
            else if (falseValues.contains(ch))
                operandStack.push(false);
        }
        else {
            if (ch == '!')
                continue;
            bool operand2 = operandStack.top();
            operandStack.pop();
            bool operand1 = operandStack.top();
            operandStack.pop();
            switch (ch) {
            case '&':
                operandStack.push(operand1 && operand2);
                break;
            case '|':
                operandStack.push(operand1 || operand2);
                break;
            }
        }
    }
    result = operandStack.top();

    //cerr << "returning: 0, pf: " << postfix << ", answer: " << result << endl;

    return 0;
}



int main()
{
    string trueChars = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

 /*   string pf;
    bool answer;
    evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer);
    evaluate("!w&!t", trues, falses, pf, answer);
    evaluate("!w|!t", trues, falses, pf, answer);
    evaluate("(!t&f)|z", trues, falses, pf, answer);
    cerr << "should be pf == ff!tn&&| and is: " << pf << endl;
    cerr << answer << endl;*/

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("((", trues, falses, pf, answer) == 1);
    assert(evaluate("))", trues, falses, pf, answer) == 1);
    assert(evaluate("()z", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("n+y", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
        && pf == "ff!tn&&|" && !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x" && answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
    cout << "Passed all tests" << endl;
}