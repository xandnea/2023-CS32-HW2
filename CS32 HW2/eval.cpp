int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    postfix = "";
    stack<char> operatorStack;

    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];

        switch(ch)
            case /*operand*/:
                postfix += ch;
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
            case /*operator*/:
                while ((!operatorStack.empty()) && (operatorStack.top() != '(') && precedence of ch <= precedence of operatorStack.top()) {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    stack<char> operandStack;
    for (int i = 0; i < postfix.size(); i++) {
        char ch = postfix[i];

        if (isalpha(ch))
            operandStack.push(ch);
        else {
            ch = postfix[i + 1];
            operandStack.push(ch);
            operandStack.pop();
            ch = postfix[i - 1];
            operandStack.push(ch);
            operandStack.pop();

        }
    }


                  And here is his pseudocode for the evaluation of the postfix expression :

              Initialize the operand stack to empty
                  For each character ch in the postfix string
                  if ch is an operand
                      push the value that ch represents onto the operand stack
                  else // ch is a binary operator
                      set operand2 to the top of the operand stack
                      pop the stack
                      set operand1 to the top of the operand stack
                      pop the stack
                      apply the operation that ch represents to operand1and
                      operand2, and push the result onto the stack
                      When the loop is finished, the operand stack will contain one item,
                      the result of evaluating the expression
}
// Evaluate a boolean expression
//   If infix is a syntactically valid infix boolean expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values sets), then postfix is set to the postfix
//   form of the expression.  If not, postfix might or might not be
//   changed, result is unchanged, and the function returns 1.
//
//   If infix is a syntactically valid infix boolean expression whose
//   only operands are single lower case letters:
//
//      If every operand letter in the expression appears in either
//      trueValues or falseValues but not both, then result is set to the
//      result of evaluating the expression (using for each letter in the
//      expression the value true if that letter appears in trueValues or
//      false if that letter appears in false values) and the function
//      returns 0.
//
//      Otherwise, result is unchanged and the value the function returns
//      depends on these two conditions:
//        at least one letter in the expression is in neither the
//            trueValues nor the falseValues sets; and
//        at least one letter in the expression is in both the
//            trueValues and the falseValues set.
//      If only the first condition holds, the function returns 2; if
//      only the second holds, the function returns 3.  If both hold
//      the function returns either 2 or 3 (and the function is not
//      required to return the same one if called another time with the
//      same arguments).

#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

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

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
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