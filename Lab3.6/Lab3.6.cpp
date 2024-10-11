#include <iostream>
#include <string>
#include <cctype>

using namespace std;  

class Stack {
private:
    int arr[100];  // масив для зберігання елементів стеку
    int top;       // вершина стеку
public:
    Stack() : top(-1) {}

    void push(int value) {
        if (top < 99) {
            arr[++top] = value;
        }//Добавляємо в стек
    }

    int pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return -1;  // стек порожній
    }

    bool isEmpty() {
        return top == -1;
    }

    // метод для доступу до вершини стеку
    int peek() {
        if (top >= 0) {
            return arr[top];
        }
        return -1;  // якщо стек порожній
    }
};

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void toRPN(const string& expr, string& output) {
    Stack ops;
    for (char ch : expr) {
        if (isdigit(ch)) {
            output += ch;
            output += ' ';
        }
        else if (ch == '(') {
            ops.push(ch);
        }
        else if (ch == ')') {
            while (!ops.isEmpty() && ops.peek() != '(') {
                output += ops.pop();
                output += ' ';
            }
            ops.pop();  // видаляємо '('
        }
        else {
            while (!ops.isEmpty() && precedence(ops.peek()) >= precedence(ch)) {
                output += ops.pop();
                output += ' ';
            }
            ops.push(ch);
        }
    }
    while (!ops.isEmpty()) {
        output += ops.pop();
        output += ' ';
    }
}

int evaluateRPN(const string& rpn) {
    Stack nums;
    for (char ch : rpn) {
        if (isdigit(ch)) {
            nums.push(ch - '0');
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int b = nums.pop();
            int a = nums.pop();
            switch (ch) {
            case '+':
                nums.push(a + b);
                break;
            case '-': 
                nums.push(a - b); 
                break;
            case '*':
                nums.push(a * b); 
                break;
            case '/': 
                nums.push(a / b);
                break;
            }
        }
    }
    return nums.pop();
}

int main() {
    string expr = "5+(7*9-7)/7";
    string rpn;
    toRPN(expr, rpn);

    cout << "RPN: " << rpn << endl;
    int result = evaluateRPN(rpn);
    cout << "Result: " << result << endl;

    return 0;
}
