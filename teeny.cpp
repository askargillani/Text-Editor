#include <iostream>
#include "Teeny.h"
using namespace std;

//Skeleton of class LinkedText
class LinkedText{
    struct Node {
        char ch;
        Node* next;
        Node* prev;
    } *head, * tail, * cursorPos, * c1, * c2, * subhead, * subtail;

    int textSize;
    int flag;
    
    public:
        void setCursorPosition()
        {
            Node* temp = tail;
            while (temp->prev != cursorPos)
            {
                moveScreenCursorLeft();
                temp = temp->prev;
            }
        }
        void straightPrint()
        {
            Node* temp = head->next;
            while (temp != tail)
            {
                cout << temp->ch;
                temp = temp->next;
            }
        }
        LinkedText(){
            head = new Node;
            head->prev = 0;
            head->next = new Node;
            tail = head->next;
            tail->prev = head;
            tail->next = 0;
            textSize = 0;
            cursorPos = head;
            c1 = 0;
            c2 = 0;
            flag = 3;
            subhead = 0;
            subtail = 0;
        }
        //some suggested methods
        //All these methods (except copying) are O(1) thanks to the linked list!
        void addCharAtCursorPos(char input)//when char entered
        {
            Node* temp = new Node;
            temp->ch = input;
            temp->next = cursorPos->next;
            temp->prev = cursorPos;
            cursorPos->next->prev = temp;
            cursorPos->next = temp;
            textSize++;
            moveCursorRight();
            system("cls");
            straightPrint();
            setCursorPosition();
        }

        void printAtPosition(Node* t)
        {
            system("cls");
            cout << t->ch << endl;
        }

        void delCharAtCursorPos()//when bksp pressed
        {
                if (cursorPos != head)
                {
                    Node* temp = cursorPos;
                    moveCursorLeft();
                    cursorPos->next = temp->next;
                    cursorPos->next->prev = cursorPos;
                    delete temp;
                    textSize--;
                    system("cls");
                    straightPrint();
                    setCursorPosition();
                    system("cls");
                    straightPrint();
                    setCursorPosition();
                }
        }
        
        void moveCursorRight()//right arrow
        {
            cursorPos = cursorPos->next;
        }
        
        void moveCursorLeft()//left arrow
        {
            cursorPos = cursorPos->prev;
        }
        /*the following method returns the sub-list after cutting,
        and also adjusts cursor position*/

        void selectText()
        {
            int k = 0;
            flag = 0;
            c1 = cursorPos;
            c2 = cursorPos;
            while (k != F1)
            {
                k = _getch();
                if (k == ARROW_RIGHT)
                {
                    if (flag>=0 && cursorPos->next != tail)
                    {
                        flag++;
                        moveCursorRight();
                        moveScreenCursorRight();
                        c2 = cursorPos;
                    }
                    else if(cursorPos->next != tail)
                    {
                        flag++;
                        moveCursorRight();
                        moveScreenCursorRight();
                        c1 = cursorPos;
                    }
                }
                else if (k == ARROW_LEFT)
                {
                    if (flag<=0 && cursorPos->prev!=head)
                    {
                        flag--;
                        moveCursorLeft();
                        moveScreenCursorLeft();
                        c1 = cursorPos;
                    }
                    else if (cursorPos->prev != head)
                    {
                        flag--;
                        moveCursorLeft();
                        moveScreenCursorLeft();
                        c2 = cursorPos;
                    }
                }
            }
        }

        void cutTextBetween()
        {
            subhead = c1;
            subtail = c2;
            subhead->prev->next = subtail->next;
            subtail->next->prev = subhead->prev;
            cursorPos = subhead->prev;
            system("cls");
            straightPrint();
            setCursorPosition();
        }
        /*the following method returns the duplicated sub-list after copying,
        and also adjusts cursor position*/
        void copyTextBetween()
        {
            if (subhead != 0)
            {
                subhead = 0;
                subtail = 0;
            }
            Node* temp = c1;
            while (temp != c2)
            {
                if (subhead == 0)
                {
                    subhead = new Node;
                    subhead->prev = 0;
                    subhead->ch = temp->ch;
                    subhead->next = 0;
                    subtail = subhead;
                }
                else
                {
                    subtail->next = new Node;
                    subtail->next->prev = subtail;
                    subtail = subtail->next;
                    subtail->ch = temp->ch;
                    subtail->next = 0;
                }
                temp = temp->next;
            }
            if (subhead==0)
            {
                subhead = new Node;
                subhead->prev = 0;
                subhead->ch = temp->ch;
                subhead->next = 0;
                subtail = subhead;
            }
            else
            {
                subtail->next = new Node;
                subtail->next->prev = subtail;
                subtail = subtail->next;
                subtail->ch = temp->ch;
                subtail->next = 0;
            }
        }
        void insertTextAtCursorPos()
        {
            if (subhead!=subtail)
            {
                Node* last = cursorPos->next;
                cursorPos->next = subhead;
                subhead->prev = cursorPos;
                subtail->next = last;
                last->prev = subtail;
                system("cls");
                cursorPos = last->prev;
                system("cls");
                straightPrint();
                setCursorPosition();
            }
            else
            {
                Node* last = cursorPos->next;
                cursorPos->next = subhead;
                subhead->prev = cursorPos;
                subhead->next = last;
                last->prev = subhead;
                cursorPos = last->prev;
                system("cls");
                straightPrint();
                setCursorPosition();
            }
        }
        /*Method returns the number of times key occurs
        in LinkedText*/
        int findInText(const string& key)
        {
            int c = 0;
            int kSize = key.size();
            Node* temp = head->next;
            while (temp != tail)
            {
                bool f = false;
                if (temp->ch == key[0])
                {
                    int i = 0;
                    f = true;
                    while (i < kSize)
                    {
                        if (temp->ch != key[i])
                        {
                            f = false;
                            break;
                        }
                        temp = temp->next;
                        i++;
                    }
                }
                else
                {
                    temp = temp->next;
                }
                if (f == 1)
                {
                    c++;
                }
            }
            return c;
        }

        //You may add appropriate printing methods and other methods below
        ~LinkedText()
        {
            Node* current = head;
            Node* next;

            while (current != NULL)
            {
                next = current->next;
                delete current;
                current = next;
            }
        };//delete the list


        /*The methods below will be used to keep
          the screen cursor inside the text area
          only.
        */
        inline bool textToLeft() 
		{
            return (cursorPos != head);
        }


        inline bool textToRight()
		{
            return (cursorPos->next!=tail);
        }
};

int main()
{
    GetConsoleWindowDims();
    /*This starter code is capable of detecting the
      left and right arrow keys; the backspace key;
      the escape key (for quit); the F1, F2 and F3 keys;
      and the regular text keys.
      Written for CS-218 "Data Structures" BCS-3A, FAST-NU, Lahore.
    */
    LinkedText text;
    int key=0;
    while (key != ESCAPE) {
        key = _getch();
        //either an arrow or function key is pressed
        if (SPECIAL_KEY(key)) {
            key = _getch();//get 2nd part of code from buffer
            switch (key) {
            case ARROW_LEFT:
                if(text.textToLeft()){
                moveScreenCursorLeft();
                text.moveCursorLeft();
              }
                break;
            case ARROW_RIGHT:
                if (text.textToRight()){
                moveScreenCursorRight();
                text.moveCursorRight();
              }
                break;
            case F1://start or end text selection
                text.selectText();
                break;
            case F2://cut option
                text.cutTextBetween();
                break;
            case F3://copy option
                text.copyTextBetween();
                break;
            case F5://for search
                system("cls");
                cout << "Please enter the key you want to check: ";
                char str[100];
                cin.getline(str,100);
                cout << "["<<str<<"]" << " existed in the text " << text.findInText(str) << " times!" << endl;
                cout << "Press any key to continue: ";
                int k;
                k = _getch();
                system("cls");
                text.straightPrint();
                text.setCursorPosition();
                break;
            case INSERT://to insert text
                text.insertTextAtCursorPos();
                break;
            };
        }
        else if (key == BACKSPACE) {
            text.delCharAtCursorPos();
        }
        else {
            text.addCharAtCursorPos(key);  
        }
    }
    return 0;
}
