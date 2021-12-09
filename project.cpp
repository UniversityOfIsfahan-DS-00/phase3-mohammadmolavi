#include <bits/stdc++.h>
using namespace std;

template <typename T>
class node
{
public:
    T data;
    node *next;
};

template <typename T>
class linkedList
{
public:
    node<T> *head;
    linkedList() { head = NULL; }
    void insertElement(T data)
    {
        node<T> *temp = new node<T>;
        temp->data = data;
        temp->next = NULL;
        if (head == NULL)
            head = temp;
        else
        {
            temp->next = head;
            head = temp;
        }
    }
    void deleteElement() { head = head->next; }
    void print()
    {
        node<T> *cur = new node<T>;
        cur = head;
        while (cur != NULL)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

template <typename T>
class stack1
{
private:
    linkedList<T> s;
    int sz;

public:
    stack1<T>()
    {
        sz = 0;
    }
    bool empty() { return size() == 0; }
    T pop()
    {
        if (!empty())
        {
            T data = s.head->data;
            s.deleteElement();
            sz--;
            return data;
        }
        return NULL;
    }
    void push(T data) { s.insertElement(data), sz++; }
    int size() { return sz; }
    T top()
    {
        if (empty())
            return NULL;
        return s.head->data;
    }
};

string input;
string alpha = "A";
map<char, float> stof1;
void number_spliter(int);
int isOperator(char);
string infixToPostfix(string);
string calculate(string)
void preAlpha();

int main()
{
    getline(cin, input);
    stack1<char> parentheses;

    int i = 0;

    //if parentheses is wrong print error then finish
    bool flag = true;
    while (input[i] && flag)
    {
        switch (input[i])
        {
        case '(':
            parentheses.push(input[i]);
            break;
        case ')':
            if (parentheses.top() == '(')
                parentheses.pop();
            else
                flag = false;
            break;
        }
        i++;
    }
    if (!flag || !parentheses.empty())
    {
        cout << "error\n";
        return 0;
    }
    
    i = 0;
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    //remove spaces in string

    //convert numbers to letters for convert to postfix
    while (input[i] != NULL)
    {
        if ((input[i] >= '0' && input[i] <= '9') || (input[i] == '-' && input[i + 1] >= '0' && input[i + 1] <= '9'))
        {
            if ((input[i] == '-' && i != 0) && (input[i - 1] >= '0' && input[i - 1] <= '9'))
            {
                i++;
                continue;
            }
            else
            {
                number_spliter(i);
                while (input[i] >= '0' && input[i] <= '9' || input[i] == '.' || input[i] == '-')
                    i++;
            }
        }
        i++;
    }

    string postfix = infixToPostfix(input);
    postfix = calculate(postfix);
    if (postfix.size() > 1)
    {
        cout << "error";
        return 0;
    }
    //because if we have two char means we have a letter and operator or we have two letter without opertor

    //last letter is the answer
    preAlpha();
    cout << stof1[alpha[0]];
    return 0;

}

void number_spliter(int i)
{
    int copy_i = i;
    string num;
    num += input[i];
    if (input[i + 1] != NULL)
    {
        i++;
        int k = 1;
        while ((int)input[i] >= 48 && (int)input[i] <= 57 || input[i] == '.')
        {
            num += input[i];
            i++;
            k++;
        }
    }
    else
        i++;

    input.replace(copy_i, i - copy_i, alpha);
    //convert numbers to letter

    stof1[alpha[0]] = stof(num);
    //save number to map for revert when need

    if (alpha[0] > 'Z' && alpha[0] < 'a')
        alpha[0] = 'a';
    else
        alpha[0] = (char)((int)alpha[0] + 1);
}

int isOperator(char c)
{
    //order of operator
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPostfix(string infix)
{
    stack1<char> st;
    string result;

    for (int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            result += c;
        else if (c == '(')
            st.push('(');
        else if (c == ')')
        {
            while (st.top() != '(')
            {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
        else
        {
            while (!st.empty() && isOperator(infix[i]) <= isOperator(st.top()))
            {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty())
    {
        result += st.top();
        st.pop();
    }
    return result;
}

string calculate(string postfix)
{
    if (postfix.size() == 1)
        return postfix;

    stack1<char> postfix2;
    int pop_count = 0;
    int i = postfix.size();
    i--;

    //copy postfix to a stack(reverse)
    while (i >= 0)
    {
        postfix2.push(postfix[i]);
        i--;
    }

    //if postfix have 2 char means two condition
    //1: if one of ch is '-' means we have to multiply number by -1
    //1: else: means we have 2 operator or letters or one letters and one operator
    if (postfix.size() == 2)
    {
        float number = stof1[postfix2.pop()];
        if (postfix2.pop() == '-')
        {
            stof1[alpha[0]] = -1.0 * number;
            postfix.replace(0, 2, alpha);
            if(alpha[0] > 'Z' && alpha[0] < 'a')
                alpha[0] = 'a';
            else
                alpha[0] = (char)((int)alpha[0] + 1);
            return postfix;
        }
        else
            return postfix;
    }
    

    //letters convert to number and push in this stack
    stack1<float> number;
    float result;
    //calculate two operand with one opertor and replace it  
    while (postfix.size() > 2)
    {
        if ((postfix2.top() >= 'A' && postfix2.top() <= 'Z') || (postfix2.top() >= 'a' && postfix2.top() <= 'z'))
        {
            pop_count++;
            number.push(stof1[postfix2.pop()]);
        }
        else if (postfix2.top() == '-' && number.size() == 1)
        {
            stof1[alpha[0]] = -1.0 * number.top();
            postfix2.pop();
            pop_count++;
            postfix.replace(pop_count - 2, 2, alpha);
            if(alpha[0] > 'Z' && alpha[0] < 'a')
                alpha[0] = 'a';
            else
                alpha[0] = (char)((int)alpha[0] + 1);
            return calculate(postfix);
        }
        else
        {
            char temp2 = postfix2.pop();
            pop_count++;
            switch (isOperator(temp2))
            {
            case 3:
                result = pow(number.pop(), number.pop());
                break;
            case 2:
                if (temp2 == '*')
                    result = number.pop() * number.pop();
                else
                    result = 1.0 / (number.pop() / number.pop());
                break;
            case 1:
                if (temp2 == '-')
                    result = -1.0 * (number.pop() - number.pop());
                else
                    result = number.pop() + number.pop();
                break;
            default:
                break;
            }
            stof1[alpha[0]] = result;
            postfix.replace(pop_count - 3, 3, alpha);
            if(alpha[0] > 'Z' && alpha[0] < 'a')
                alpha[0] = 'a';
            else
                alpha[0] = (char)((int)alpha[0] + 1);
            break;
        }
    }
    return calculate(postfix);
}

void preAlpha()
{
    if( alpha[0] <= 'Z' || (alpha[0] > 'a' && alpha[0] <= 'z'))
        alpha[0] = (char)((int)alpha[0] - 1);
    else if((int)alpha[0] < (int)'a' + 1 && alpha[0] > 'Z')
        alpha[0] = 'z';
}