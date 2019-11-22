#include <iostream>
#include <fstream>
#include<cstring>

using namespace std;

class node // class of node for creating new nodes
{
public:
    char ch;
    int fq;
    string code;
    node *right, *left, *leftc, *rightc;
    node *new_node(char data, int frequency, node *lc, node *rc)
    {
        node *p;
        p = new node;
        p->ch = data;
        p->fq = frequency;
        p->right = NULL;
        p->left = NULL;
        p->leftc = lc;  // stores left child
        p->rightc = rc; // stores right child
        p->code = "";
        return p;
    }
};

    node *t = t->new_node('t', 0, NULL, NULL); // creating nodes for each character
    node *h = h->new_node('h', 0, NULL, NULL);
    node *f = f->new_node('f', 0, NULL, NULL);
    node *k = k->new_node('k', 0, NULL, NULL);
    node *p = p->new_node('p', 0, NULL, NULL);
    node *x = x->new_node('x', 0, NULL, NULL);

class process // class containing all the steps to create huffman tree
{
public:

    node *front = NULL, *rear = NULL;
    void enq(node *c)
    {
        node *temp_ry = temp_ry->new_node(c->ch, c->fq, c->leftc, c->rightc); // temporary node to place
        if (front == NULL)                                                    // if queue is empty directly stores the node
        {
            front = temp_ry;
            rear = temp_ry;
            temp_ry->right = NULL;
        }
        else
        {
            if (c->fq <= front->fq) // if less than front then stored as the front element
            {
                temp_ry->right = front;
                front->left = temp_ry->right;
                front = temp_ry;
            }
            else if (c->fq > rear->fq) // if greater than last element then stored at the last
            {
                temp_ry->right = NULL;
                rear->right = temp_ry;
                temp_ry->left = rear->right;
                rear = temp_ry;
            }
            else // deals with the cases when element is in between front and rear
            {
                node *start = front;
                if (start->right == rear) // when only two elemnets remain in the queue
                {
                    temp_ry->right = start->right;
                    (start->right)->left = temp_ry->right;
                    start->right = temp_ry;
                    temp_ry->left = start->right;
                }
                else // when more than two elements remain the queue
                {
                    node *start = front->right;
                    while (start->fq > c->fq)
                        start = start->right;
                    temp_ry->right = start->right;
                    (start->right)->left = temp_ry->right;
                    start->right = temp_ry;
                    temp_ry->left = start->right;
                }
            }
        }
    }

    void show() // function which displays the contents of the queue
    {
        node *ptr = front;
        while (ptr != NULL)
        {
            cout << ptr->ch << " -> " << ptr->fq << endl;
            ptr = ptr->right;
        }
    }

    void showcode(node *temp)       // displays variable length codes and assigns them to their respective leaf nodes
    {
        cout << temp->ch << " ->" << temp->code << endl;
        if(temp->ch==t->ch)
        t->code=temp->code;
        else if (temp->ch==h->ch)
        h->code=temp->code;
        else if (temp->ch==p->ch)
        p->code=temp->code;
        else if (temp->ch==x->ch)
        x->code=temp->code;
        else if (temp->ch==f->ch)
        f->code=temp->code;
        else 
        k->code=temp->code;
    }

    node *deq() // function which removes element form the starting of the queue
    {
        node *temp = front;
        if (front->right == NULL) // when only one element remains in the queue
        {
            front = NULL;
            return temp;
        }
        else // when more than one elemnts remain in the queue
        {
            front = front->right;
            front->left = NULL;
            return temp;
        }
    }

    void hufftree()
    {
        while (front->right != NULL) // up to second last element
        {
            node *lc = NULL, *rc = NULL; // nodes to store left and right child
            lc = deq();
            rc = deq();
            node *nn = nn->new_node('z', (lc->fq) + (rc->fq), lc, rc); // new node containing left and right childs
            enq(nn);                                                   // passes to the queue
        }
    }

    void traverse(node *temp, string str)
    {

         if (temp->leftc == NULL && temp->rightc == NULL)
        {
            temp->code = str;
            showcode(temp);
        }
        
        else
        {
            traverse(temp->leftc, str+'0');
            traverse(temp->rightc, str+'1');
        }
        
    }

    void encoder()
    {
        cout<<endl<<endl<<"Variable length codes are : "<<endl<<endl;
        string str="";
        traverse(front, str);
    }
};

int main()
{

    int freq[] = {0, 0, 0, 0, 0, 0}; // array for storing frequencies
    fstream newfile, file;           //file-by user,newfile-we mingle with
    int osize=0;
    newfile.open("newfile.txt", ios::out);
    if (!newfile)
    {
        cout << "Error in creating file!!!";
        return 0;
    }

    file.open("file.txt", ios::in);
    if (!file)
    {
        cout << "Unable to open file." << endl;
        return -1;
    }
    while (true)
    {
        char chr;
        file >> chr;
        if (file.eof())
            break;
        if (chr == 't' || chr == 'h' || chr == 'f' || chr == 'k' || chr == 'p' || chr == 'x') // reading from original file
        {
            newfile << chr; // writing into new file
            osize++;
        }
    }
    file.close();
    newfile.close();

    newfile.open("newfile.txt", ios::in);
    if (!newfile)
    {
        cout << "Unable to open file." << endl;
        return -1;
    }
    while (true) // reading from the new file
    {
        char y;
        newfile >> y;
        if (newfile.eof())
            break;
        if (y == 't')
            freq[0]++;
        else if (y == 'h')
            freq[1]++;
        else if (y == 'f')
            freq[2]++;
        else if (y == 'k')
            freq[3]++;
        else if (y == 'p')
            freq[4]++;
        else
        {
            if (y == 'x')
                freq[5]++;
        }
    }
    newfile.close();

    t->fq=freq[0]; // creating nodes for each character
    h->fq=freq[1];
    f->fq=freq[2];
    k->fq=freq[3];
    p->fq=freq[4];
    x->fq=freq[5];

    process prqu;
    prqu.enq(t);
    prqu.enq(h);
    prqu.enq(f);
    prqu.enq(k);
    prqu.enq(p);
    prqu.enq(x);
    cout<<endl<<endl<<"Letters w/ frequencies : "<<endl<<endl;
    prqu.show();
    prqu.hufftree();
    prqu.encoder(); // start encoding
    

    fstream cfile;           //file-by user,newfile-we mingle with
    cfile.open("cfile.txt", ios::out);
    if (!cfile)
    {
        cout << "Error in creating file!!!";
        return 0;
    }

    newfile.open("file.txt", ios::in);
    if (!newfile)
    {
        cout << "Unable to open file." << endl;
        return -1;
    }
    
    string s="";

    while (true)
    {
        char y;
        newfile >> y;       // reading characters from file
        if (newfile.eof())
            break;
        if (y == 't')
            s+=t->code;
        else if (y == 'h')
            s+=h->code;
        else if (y == 'f')
            s+=f->code;
        else if (y == 'k')
            s+=k->code;
        else if (y == 'p')
            s+=p->code;
        else
        {
            if (y == 'x')
                s+=x->code;
        }
    }

    cfile<<s;       // writing string of 0's and 1's in compressed file

    cfile.close();
    newfile.close();

    int csize=s.size()/8;


    cout<<endl<<" Size of original file is : "<<osize<<" bytes."<<endl;
    cout<<" Size of Compressed file is : "<<csize<<" bytes."<<endl<<endl;

}
