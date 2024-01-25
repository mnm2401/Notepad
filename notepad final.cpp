#include<iostream>
#include<string>
#include <conio.h> 
#include <windows.h>
#include<fstream>
using namespace std;
void gotoxy(int x, int y)
{

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

template<class t>
class node
{
public:
    node<t>* next;
    node<t>* prev;
    node<t>* up;
    node<t>* down;
    t data;
    node()
    {
        this->down = this->next = this->prev = this->up = nullptr;
        this->data = 0;
    }
    node(t data)
    {
        this->down = this->next = this->prev = this->up = nullptr;
        this->data = data;
    }
};
template<class t>
class linked_list
{
private:
    node<t>* head;
    node<t>* cursor;
public:
    linked_list() { this->head = nullptr; this->cursor = this->head; }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Insert_Vertical1(char data)
    {
        node<t>* new_node = new node<t>(data);

        if (head == nullptr)
        {
            head = new_node;
            cursor = new_node;
            
            return;
        }

        node<t>* currCol = head;

        // find the last node vertically
        while (currCol->down != nullptr)
            currCol = currCol->down;
       

        // inserting the new node
        currCol->down = new_node;
        new_node->up = currCol;
        new_node->next = nullptr;
        new_node->prev = nullptr;
        currCol = head;
        ///////////////////////////////
        cursor = new_node;
        cursor->up = new_node->up;
        cursor->next = nullptr;
        cursor->prev = nullptr;
        cout << "cursor data:" << cursor->data << " " << endl;

    }
    void Insert_Horizontal1(char data)
    {
        node<t>* new_node = new node<t>(data);

        if (head == nullptr)
        {
            head = new_node;
            cursor = new_node;
            return;
        }

        node<t>* curr_row_node = head;
        node<t>* curr_col_node = nullptr;

        // finding last node vertically
        node<t>* prev_row = nullptr;
        while (curr_row_node->down != nullptr) 
        {
            prev_row = curr_row_node;
            curr_row_node = curr_row_node->down;
        }
        curr_col_node = curr_row_node;

        // finding last node in last column
        node<t>* temp_col = nullptr;
        while (curr_col_node->next != nullptr)
        {
            temp_col = curr_col_node;
            curr_col_node = curr_col_node->next;
        }

        // inserting the new node
        curr_col_node->next = new_node;
        new_node->prev = curr_col_node;
        new_node->down = nullptr;
        if (prev_row and curr_row_node) 
        {
            /*while (prev_row&&curr_row_node)
            {
                cout << "temp and curr row:" << prev_row->data << " " << curr_row_node->data << endl;

                prev_row = prev_row->next;
                curr_row_node = curr_row_node->next;
            }*/

           
            while (prev_row->next && curr_row_node->next)
            {
                //  cout << "temp and curr row:" << prev_row->data << " " << curr_row_node->data << endl;

                prev_row = prev_row->next;
                curr_row_node = curr_row_node->next;
            }
            if (prev_row == nullptr)
                new_node->up = nullptr;
            else
            {
                new_node->up = prev_row;
                prev_row->down = new_node;
            }
        }
       


            ////////////////////////////////////////////
        cursor = new_node;
        cursor->next = nullptr;
        cursor->prev = new_node->prev;
        cursor->down = nullptr;
        cursor->up = new_node->up;
       // cout << "cursor data:" << cursor->data << " " << endl;
        /*cout << "cursor up:" << cursor->up->data << " " << endl;
        cout << "cursor down:" << cursor->down << " " << endl;
        cout << "cursor next:" << cursor->next->data << " " << endl;
        cout << "cursor prev:" << cursor->prev->data << " " << endl;*/
    }
    void printlinks(node<t>* head)
    {
        while (head)
        {
            if (cursor->up)
                cout << "cursor up:" << cursor->up->data << " " << endl;
            else
                cout << "no link\n";
            if (cursor->down)
                cout << "cursor down:" << cursor->down << " " << endl;
            else
                cout << "no link\n";
            head = head->next;
        }
    }
    void printlinks() {
        /*       node<t>* temp = cursor;
               while (temp->prev)
                   temp = temp->prev;*/
        printlinks(head);
    }
    void print()
    {
        node<t>* curr_row_node = this->head;
        node<t>* curr_col_node = nullptr;
        while (curr_row_node != nullptr)
        {
            curr_col_node = curr_row_node;
            while (curr_col_node != nullptr)
            {
                cout << curr_col_node->data << " ";
                curr_col_node = curr_col_node->next;
            }
            cout << endl;
            curr_row_node = curr_row_node->down;
        }
    }
    void insert_vertical_after(t data, t newData)
    {
        node<t>* curr_node = search(data);
        if (curr_node != nullptr) {
            node<t>* new_node = new node<t>(newData);

            new_node->down = curr_node->down;
            curr_node->down = new_node;
            new_node->up = curr_node;
            if (new_node->down != nullptr) 
                new_node->down->up = new_node;
            

            if (new_node->next != nullptr)
                new_node->next->prev = new_node;
     
            cursor = new_node;
            cursor->up = new_node->up;
            cursor->down = new_node->down;

            cursor->next = nullptr;
            cursor->prev = nullptr;
            cout << "cursor:" << cursor->data << endl;
        }
    }
    node<t>* search(t data)
    {
        node<t>* curr_row_node = head;
        node<t>* curr_col_node = nullptr;
        while (curr_row_node != nullptr)
        {
            curr_col_node = curr_row_node;
            while (curr_col_node != nullptr)
            {
                if (curr_col_node->data == data)
                    return curr_col_node;

                curr_col_node = curr_col_node->next;
            }
            curr_row_node = curr_row_node->down;
        }
        return nullptr;
    }

    void insert_after_horizontal(t data, t new_data) 
    {
        node<t>* curr_node = search(data);

        if (curr_node == nullptr)
            return;


        node<t>* new_node = new node<t>(new_data);

        new_node->prev = curr_node;
        new_node->next = curr_node->next;
        if (curr_node->next != nullptr)
            curr_node->next->prev = new_node;

        curr_node->next = new_node;

        //linking node to next column
        if (curr_node->down != nullptr && curr_node->next == nullptr)
        {
            node<t>* next_col = curr_node->down;
            while (next_col->next != nullptr) 
                next_col = next_col->next;
           
            new_node->down = next_col;
            next_col->up = new_node;
        }
        cursor = new_node;
        cursor->up = new_node->up;
        cursor->down = new_node->down;
        cursor->prev = new_node->prev;
        cursor->next = new_node->next;
        cout << "cursor:" << cursor->data << endl;
    }
    void insertBefore(t existingData, t newData)
    {
        node<t>* existingNode = search(existingData);
        if (existingNode == nullptr) 
            return;

        node<t>* new_node = new node<t>(newData);
        new_node->next = existingNode;
        new_node->prev = existingNode->prev;
        if (existingNode->prev)
        {
            existingNode->prev->next = new_node;
            existingNode->prev = new_node;
        }
        if (existingNode->down != nullptr && existingNode->next == nullptr) {
            node<t>* next_col = existingNode->down;
            while (next_col->next != nullptr) 
                next_col = next_col->next;
            
            new_node->down = next_col;
            next_col->up = new_node;
        }
        ///////////////////
        cursor = new_node;
        cursor->up = new_node->up;
        cursor->down = new_node->down;
        cursor->prev = new_node->prev;
        cursor->next = new_node->next;
        cout << "cursor:" << cursor->data << endl;
    }
    void savetofile(string filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            node<t>* curr_row_node = this->head;
            node<t>* curr_col_node = nullptr;
            while (curr_row_node != nullptr)
            {
                curr_col_node = curr_row_node;
                while (curr_col_node != nullptr)
                {
                    file << curr_col_node->data << " ";
                    curr_col_node = curr_col_node->next;
                }
                file << endl;
                curr_row_node = curr_row_node->down;
            }
            file.close();
            cout << " list saved" << endl;
        }
        else
        {
            cout << "file doesn't exist ." << endl;
        }
    }

    void readfromfile(const string& filename)
    {
        ifstream file(filename);
        if (!file) 
        {
            cout << "file doesn't exist " << filename << endl;
            return;
        }

        
        string line;
        while (getline(file, line))
        {
            for (char c : line)
            {
                if (c != ' ') 
                {
                    Insert_Horizontal1(c);
                }
            }
            Insert_Vertical1(' ');
        }

        file.close();
    }

    /////////////////////////////////////////////////
    /////////////////////////////////////////////////

    void Move_Left() 
    {
        if (cursor->prev != nullptr)
        {
            cursor = cursor->prev;
            //cout << "cursor data after moving prev:" << cursor->data << endl;
        }
        else
            cout << "no prev link found" << endl;
        
    }

    void Move_Right() 
    {
        if (cursor->next != nullptr) 
        {
            cursor = cursor->next;
            //cout << "cursor data after moving next:" << cursor->data << endl;
        }
        else
            cout << "no next link found" << endl;
 
    }

    void Move_Up()
    {
        if (cursor->up != nullptr)
        {
            cursor = cursor->up;
            //cout << "cursor data after moving up:" << cursor->data << endl;
        }
        else
            cout << "no up link found" << endl;
        
    }

    void Move_Down() 
    {
        if (cursor->down != nullptr)
        {
            cursor = cursor->down;
            //cout << "cursor data after moving down:" << cursor->data << endl;
        }
        else
            cout << "no down link found" << endl;
        
    }
    ~linked_list()
    {
        node<t>* curr_row_node = this->head;
        node<t>* curr_col_node = nullptr;
        while (curr_row_node != nullptr)
        {
            curr_col_node = curr_row_node;
            while (curr_col_node != nullptr)
            {
                node<t>* temp = curr_col_node;
                delete temp;
                curr_col_node = curr_col_node->next;
            }
            cout << endl;
            curr_row_node = curr_row_node->down;
        }
    }

    void Delete1()
    {

        if (cursor == nullptr)
            return;
        
        if (cursor == head)
        {
            if (head->down)
                head->down->up = head->next;
            if (head->next)
            {
                head->next->down = head->down;
                head = head->next;
            }
            if (head != nullptr) 
                head->prev = nullptr;
            
            delete cursor;
            cursor = head;
            if (cursor == nullptr)
            {
                    cout << "no elements left!" << endl << "To input more elements press a:" << endl;
                    char choice, input;
                    cin >> choice;
                    if (choice == 'a')
                    {
                        cin >> input;
                        Insert_Horizontal1(input);
                    }
            }
            return;
        }
        //first node in any row 
        if (cursor->prev == nullptr)
        {
            if (cursor->down != nullptr && cursor->down->up != nullptr)
                cursor->down->up = cursor->next;
            if (cursor->next)
                cursor->next->down = cursor->down;
        }
        if (cursor->up != nullptr)
            cursor->up->down = cursor->next;
        
        if (cursor->down != nullptr) 
           cursor->down->up = cursor->next;
        
        if (cursor->prev != nullptr)
            cursor->prev->next = cursor->next;
        
        if (cursor->next != nullptr) 
            cursor->next->prev = cursor->prev;
        
        ////////////////////////////////////

        ////////////////////////
        
        //if (cursor->next)
        //{
        //    node<t>* temp = cursor;
        //    //cursor = cursor->next;
        //    Move_Right();
        //    delete temp;
        //    return;
        //}
        if (cursor->prev /*&& cursor->next == nullptr*/)
        {
            node<t>* temp = cursor;
            Move_Left();
            delete temp;
            return;
        }
        //last element in row
        if (cursor->prev == nullptr)
        {
            if (cursor->up)
            {
                node<t>* temp = cursor->up;
                while (temp->next)
                    temp = temp->next;
                delete cursor;
                cursor = temp;
            }
            return;
        }
        //else if (cursor->prev == nullptr && cursor->next == nullptr || cursor->prev && cursor->prev->data == 'r' && cursor->next == nullptr)
        //{
        //    // move cursor to last node of above row
        //    Move_Up();
        //}

    }


    void insert(char c)
    {
        if (c == '\r')
        {
            // insert vertically
            if (cursor->next) 
            {
                node<char>* temp_prev = cursor;
                node<char>* temp = cursor->next;
                cursor->next = nullptr;
                insert_vertical_after(temp_prev->data, temp->data);
                cursor = cursor->down;
                while (temp->next) 
                {
                    node<t>* T = temp;
                    temp = temp->next;
                    insert_after_horizontal(T->data, temp->data);
                    //cursor = cursor->next;
                }
                //delete temp;
            }
            else {
                char x=_getch();
                Insert_Vertical1(x);

                //   cursor = cursor->down;
            }
        }
        else
        {
            // insert horizontally
            if((cursor&&cursor->next==nullptr)||head==nullptr)
                Insert_Horizontal1(c);
            if (cursor&&cursor->next) 
            {
                node<t>* temp = cursor;
                insert_after_horizontal(temp->data, c);
            }
        }
        cout << "printing:" << endl;
        print();
    }

    void MoveNode(node<t>*& cursor) 
    {
        // Get the current console cursor position
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int current_x = csbi.dwCursorPosition.X;
        int current_y = csbi.dwCursorPosition.Y;

        cout << "cursor data: " << cursor->data << endl;
        while (true) 
        {
            int key = _getch();
            if (key == 224)
            {
                key = _getch();
                switch (key) 
                {
                case 75: // left 
                    Move_Left();
                    current_x -= 1;
                    break;
                case 77: // right 
                    Move_Right();
                    current_x += 1;
                    break;
                case 72: // up
                    Move_Up();
                    current_y -= 1;
                    break;
                case 80: // down
                    Move_Down();
                    current_y += 1;
                    break;
                }
                // moving console cursor to curr position
                gotoxy(current_x, current_y);

                cout << "cursor data: " << cursor->data << endl;
            }
            else if (key == 27) 
                break; 
            
        }
    }

    void movenode()
    {
        MoveNode(this->cursor);
    }


    void insert_horizontal_cursor(char data)
    {
        node<t>* new_node = new node<t>(data);

        if (head == nullptr) {
            head = new_node;
            cursor = new_node;
            return;
        }

        node<t>* curr_row_node = head;
        node<t>* curr_col_node = nullptr;

        // find the last node in the current row
        node<t>* prev_row = nullptr;
        while (curr_row_node->down != nullptr) {
            prev_row = curr_row_node;
            curr_row_node = curr_row_node->down;
        }
        curr_col_node = curr_row_node;

        // find the last node in the current column
        node<t>* temp_col = nullptr;
        while (curr_col_node->next != nullptr) {
            temp_col = curr_col_node;
            curr_col_node = curr_col_node->next;
        }

        // insert the new node after the cursor
        if (cursor->next != nullptr) {
            new_node->next = cursor->next;
            cursor->next->prev = new_node;
        }
        cursor->next = new_node;
        new_node->prev = cursor;

        if (prev_row and curr_row_node)
            /*while (prev_row&&curr_row_node)
            {
                cout << "temp and curr row:" << prev_row->data << " " << curr_row_node->data << endl;

                prev_row = prev_row->next;
                curr_row_node = curr_row_node->next;
            }*/

            while (prev_row->next && curr_row_node->next)
            {
                //  cout << "temp and curr row:" << prev_row->data << " " << curr_row_node->data << endl;

                prev_row = prev_row->next;
                curr_row_node = curr_row_node->next;
            }
        if (prev_row == nullptr)
            new_node->up = nullptr;
        else
        {
            new_node->up = prev_row;
            prev_row->down = new_node;
        }
        new_node->down = nullptr;

        // update the up and down pointers of the new node
        if (cursor->down != nullptr) {
            new_node->down = cursor->down;
            cursor->down->up = new_node;
        }
        new_node->up = cursor;

        cursor = new_node;
        cursor->next = nullptr;
        cursor->down = nullptr;
    }

};
int main_0()
{

    linked_list<char> temp;
    temp.Insert_Horizontal1('h');
    temp.Insert_Horizontal1('e');
    temp.Insert_Horizontal1('l');
    temp.Insert_Horizontal1('l');
    temp.Insert_Horizontal1('o');
    /*    temp.Insert_Horizontal('\n');
        temp.Insert_Horizontal('\b');*/

    temp.Insert_Vertical1('p');
    temp.Insert_Horizontal1('e');
    temp.Insert_Horizontal1('t');
    temp.Insert_Horizontal1('e');
    temp.Insert_Horizontal1('r');

    temp.Insert_Vertical1('I');
    temp.Insert_Horizontal1('A');

    temp.Insert_Horizontal1('M');
    temp.Insert_Horizontal1('V');

    temp.Insert_Vertical1('G');
    temp.Insert_Horizontal1('r');
    temp.Insert_Horizontal1('o');
    temp.Insert_Horizontal1('o');
    temp.Insert_Horizontal1('t');

    temp.Insert_Vertical1('s');
    temp.Insert_Horizontal1('t');
    temp.Insert_Horizontal1('a');
    temp.Insert_Horizontal1('r');
    temp.Insert_Horizontal1('k');
    temp.insert_vertical_after('I', 'T');
   

    /*temp.insert_after_horizontal('L', 'y');
    temp.insertBefore('t', 'f');*/
    cout << "printing list:" << endl;
    temp.print();
    cout << "moving cursor:" << endl;
    /*  cout << "printing links:" << endl;
      temp.printlinks();*/
      /*temp.Move_Left();
      temp.Move_Left();*/



      /*   cout << "after deleting:\n";
         temp.Delete1();
         temp.print();
         cout << endl;
         temp.Move_Left();
         temp.Delete1();
         cout << endl;
         temp.print();
         temp.Move_Left();
         temp.Delete1();
         cout << endl;
         temp.print();*/
         /*   temp.Move_Up();
              temp.Move_Left();
              temp.Move_Left();
              temp.Move_Up();
              temp.Move_Right();
              temp.Move_Right();*/

              //  temp.Move_Up();

               /* temp.Move_Down();
                temp.Move_Down();*/

                /*   temp.Move_Right();
                   temp.Move_Right();*/


                   //temp.Delete1();
                   //cout << endl;
                   //temp.print();
    //temp.movenode();
    temp.savetofile("correct output2.txt");

    ///*temp.delete_node9('G');
    //temp.print();*/
    linked_list<char> temp2;
    temp2.readfromfile("correct output2.txt");
    cout << "temp2:" << endl;
    temp2.print();
    return 0;
}


int main()
{
    linked_list<char> notepad;
    while (1)
    {
        char c = _getch();
        if (c == -32)
            notepad.movenode();  
        
        else if (c == '\b')
        { 
            notepad.Delete1();
            cout << "after deleting:" << endl;
            notepad.print();
        }
        else if (c == 'S' || c == 's')   
            notepad.savetofile("output2.txt");
       
        else if (c == 'L' || c == 'l')
            notepad.readfromfile("output2.txt");
        else
        {
            notepad.insert(c);  
            system("cls");  
            notepad.print(); 
        }
    }
    return 0;
}

