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
    return 0;
}