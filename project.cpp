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
    cout << input;
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
