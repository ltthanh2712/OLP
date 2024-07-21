#include <iostream>
#include <vector>
#include "string"
#include <stack>
using namespace std;
int operatorPrecedence(string Operator){
    if(Operator == "^"){
        return 3;
    }
    if(Operator == "*" || Operator == "/"){
        return 2;
    }
    if(Operator == "+" || Operator == "-"){
        return 1;
    }
    return 0;
}
bool isNumber(string input){
    if(input == "+" || input == "-" || input == "*" || input == "/" || input == "(" || input == ")"){
        return false;
    }
    return true;
}
bool isOperator(string input){
    return input == "+" || input == "-" || input == "*" || input == "/";
}
vector<string> infixToPostFix(vector<string>& infix){
    vector<string> postfix;
    stack<string> st;
    for(int i = 0; i < infix.size();i++){
        // If the string is an operand, push back it to vector "postfix"
        if(isNumber(infix[i])){
            postfix.push_back(infix[i]);
        }
            // If the string is "(", push it to stack
        else if(infix[i] == "("){
            st.push(infix[i]);
        }
            // If the string is ")", push to postfix and pop the topmost item of the stack until an "(" is encountered
        else if(infix[i] == ")"){
            while(!st.empty() && st.top() != "("){
                postfix.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
            /* If the string is Operator, push to postfix and pop the topmost item of the stack if it has
            greater than or equal precedence with this operator */
        else if(isOperator(infix[i])){
            while(!st.empty() && operatorPrecedence(infix[i]) <= operatorPrecedence(st.top())){
                postfix.push_back(st.top());
                st.pop();
            }
            st.push(infix[i]);
        }
    }
    // push to postfix and pop the topmost item of the stack until the stack is empty
    while(!st.empty()){
        postfix.push_back(st.top());
        st.pop();
    }
    return postfix;
}
double calculator(string s,double num1,double num2){
    if (s == "+")
    {
        return num1+=num2;
    }
    if (s == "-")
    {
        return num2-=num1;
    }
    if (s == "*")
    {
        return num1*=num2;
    }
    if (s == "/")
    {
        return num2/=num1;
    }
}
double calPostfix(vector<string>& postfix){
    stack<double> st;
    for(int i = 0; i < postfix.size(); i++)
    {
        if (isNumber(postfix[i]))
        {
            int soNguyen = stoi(postfix[i]);
            st.push(soNguyen);
        }
        else
        {
            double num1 = st.top();
            st.pop();
            double num2 = st.top();
            st.pop();
            double result = calculator(postfix[i],num1,num2);
            st.push(result);
        }
    }
    return st.top();
}
int main()
{
    vector<string> infix;
    while(true){
        string input;
        cin >> input;
        if(input == "e") //Enter the character "e" to stop typing
        {
            break;
        }
        infix.push_back(input);
    }
    vector<string> postfix = infixToPostFix(infix);
    for(int i = 0; i < postfix.size(); i++){
        cout << postfix[i] << " ";
    }
    cout <<  endl;
    cout << calPostfix(postfix);
    return 0;
}
