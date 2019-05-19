//
// Created by admin on 20.05.2019.
//

#ifndef SETTINGUPGOOGLETESTS_HAFFMAN_H
#define SETTINGUPGOOGLETESTS_HAFFMAN_H
#include  <stdio.h>
#include  <windows.h>
#include  <conio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <string.h>
#include  <iostream>
using namespace std;

bool RED=true;
bool BLACK=false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int redColor=4;
const int blackColor=1;
const int normalColor=10;


class haf_Tree{
private:

    struct bit
    {
        bit *next;
        bool data;
    };

    class RB_Tree{
    private:
        struct node
        {
            char key;
            bit *bitHead;
            bool color;
            node *lft;
            node *rht;
            node *parent;
        };


        bool getColor(node * n)
        {
            if(n!=NULL)
            {
                if(n->color == RED)
                    return RED;
            }
            return BLACK;
        }
    public:
        node *head;
        void printKodes(node *n)
        {
            if (n!=NULL)
            {
                printKodes(n->rht);
                bit * tmpBit = n->bitHead;
                cout<<"| "<<n->key<<" | ";
                while(tmpBit!=NULL)
                {
                    printf("%d",((tmpBit->data==true)?1:0));
                    tmpBit=tmpBit->next;
                }
                cout<<endl;
                printKodes(n->lft);
            }
        }

        RB_Tree()
        {
            head=NULL;
        };
        ~RB_Tree(){};

        node *grandparent(node *n)
        {
            if ((n != NULL) && (n->parent != NULL))
                return n->parent->parent;
            else
                return NULL;
        }

        node *uncle(node *n)
        {
            node *g = grandparent(n);
            if (g == NULL)
                return NULL;

            if (n->parent == g->lft)
                return g->rht;
            else
                return g->lft;
        }

        node *brother(node *n)
        {
            if (n == n->parent->lft)
                return n->parent->rht;
            else
                return n->parent->lft;
        }

        void rotate_left(node *n)
        {
            node *p = n->rht;

            p->parent = n->parent;
            if (n->parent != NULL)
            {
                if (n->parent->lft==n)
                    n->parent->lft = p;
                else
                    n->parent->rht = p;
            }
            else
                head=p;

            n->rht = p->lft;
            if (p->lft != NULL)
                p->lft->parent = n;

            n->parent = p;
            p->lft = n;
        }

        void rotate_right(node *n)
        {
            node *p = n->lft;

            p->parent = n->parent;
            if (n->parent != NULL)
            {
                if (n->parent->lft==n)
                    n->parent->lft = p;
                else
                    n->parent->rht = p;
            }
            else
                head=p;

            n->lft = p->rht;
            if (p->rht != NULL)
                p->rht->parent = n;

            n->parent = p;
            p->rht = n;
        }

        void insert_case1(node *n)
        {
            if (n->parent == NULL)
                n->color = BLACK;
            else
                insert_case2(n);
        }


        void insert_case2(node *n)
        {
            if (getColor(n->parent)!= BLACK)
                insert_case3(n);
        }

        void insert_case3(node *n)
        {
            node *uncle_n = uncle(n);
            node *grandparent_n=grandparent(n);

            if (getColor(uncle_n))
            {
                n->parent->color = BLACK;
                uncle_n->color = BLACK;
                grandparent_n->color = RED;
                insert_case1(grandparent_n);
            }
            else
            {
                insert_case4(n);
            }
        }


        void insert_case4(node *n)
        {
            node *grandparent_n = grandparent(n);

            if ((n == n->parent->rht) && (n->parent == grandparent_n->lft)) {
                rotate_left(n->parent);
                n = n->lft;
            }
            else
            if ((n == n->parent->lft) && (n->parent == grandparent_n->rht)) {
                rotate_right(n->parent);
                n = n->rht;
            }
            insert_case5(n);
        }


        void insert_case5(node *n)
        {
            node *grandparent_n = grandparent(n);

            n->parent->color = BLACK;
            grandparent_n->color = RED;
            if ((n == n->parent->lft) && (n->parent == grandparent_n->lft))
            {
                rotate_right(grandparent_n);
            }
            else
            {
                rotate_left(grandparent_n);
            }
        }
        /* 1 */
        void insert(char addKey,bit * addValue)
        {

            node *addingNode;
            addingNode = new node;
            addingNode->key=addKey;
            addingNode->bitHead=addValue;
            addingNode->color=RED;
            addingNode->lft=NULL;
            addingNode->rht=NULL;
            addingNode->parent=NULL;


            if (head!=NULL)
            {
                node *searchPlace = head;
                while (searchPlace!=NULL)
                {
                    if (addKey<searchPlace->key)
                    {
                        if (searchPlace->lft==NULL)
                        {
                            addingNode->parent=searchPlace;
                            searchPlace->lft=addingNode;
                            break;
                        }


                        searchPlace=searchPlace->lft;
                    }
                    else
                    {
                        if (searchPlace->rht==NULL)
                        {
                            addingNode->parent=searchPlace;
                            searchPlace->rht=addingNode;
                            break;
                        }

                        searchPlace=searchPlace->rht;
                    }
                }
            }
            else
                head=addingNode;

            insert_case1(addingNode);
        }

        int find (char findKey)
        {
            int size=0;

            node *searchNode = head;
            while (searchNode!=NULL)
            {
                if (findKey<searchNode->key)
                    searchNode=searchNode->lft;
                else
                if (findKey>searchNode->key)
                    searchNode=searchNode->rht;
                else
                    break;
            }
            if	(searchNode!=NULL)
            {
                bit * tmpBit = searchNode->bitHead;
                while(tmpBit!=NULL)
                {
                    printf("%d",((tmpBit->data==true)?1:0));
                    size++;
                    tmpBit=tmpBit->next;
                }
            }

            else
                cout<<"Item not found\n";

            return size;
        }

        bit * get (char findKey)
        {
            node *searchNode = head;
            while (searchNode!=NULL)
            {
                if (findKey<searchNode->key)
                    searchNode=searchNode->lft;
                else
                if (findKey>searchNode->key)
                    searchNode=searchNode->rht;
                else
                    break;
            }
            if	(searchNode!=NULL)
               return searchNode->bitHead;
            else
                return NULL;
        }

    };


    class node
    {
    public:
        char name;
        node *rht;
        node *lft;
        node *prnt;
        unsigned int frequency;
        node *next;

        node(int nodeFrequency, char nodeName[],int startName)
        {
            frequency=nodeFrequency;
            rht=NULL;
            lft=NULL;
            prnt=NULL;
            next=NULL;
            name=nodeName[startName];
        };

        node(node * son1, node * son2)
        {
            frequency=son1->frequency + son2->frequency;
            name='\0';
            rht=son1;
            lft=son2;
            son1->prnt=this;
            son2->prnt=this;
            prnt=NULL;
            next=NULL;
        };
        ~node(){};

    };
    bit *bitHead;
    node *leafHead;
    RB_Tree kode;
public:
    friend class RB_Tree;
    haf_Tree()
    {
        bitHead=NULL;
        leafHead=NULL;
    };
    ~haf_Tree(){};

    char * makeTree (char input[], int sizeInput)
    {
        if (sizeInput>0) {

            char differentCharacters[sizeInput];
            for (int i = 0; i < sizeInput; i++)
                differentCharacters[i] = '\0';


            int difCarSize = 0;
            for (int i = 0; i < sizeInput; i++) {
                bool uniqueness = true;
                for (int j = 0; (j < sizeInput) && (uniqueness); j++) {
                    if (input[i] == differentCharacters[j])
                        uniqueness = false;
                }
                if (uniqueness) {
                    differentCharacters[difCarSize] = input[i];
                    difCarSize++;
                }
            }

            unsigned int frequency[difCarSize];
            for (int i = 0; i < difCarSize; i++)
                frequency[i] = 0;


            for (int i = 0; i < difCarSize; i++) {
                for (int j = 0; j < sizeInput; j++) {
                    if (differentCharacters[i] == input[j])
                        frequency[i]++;
                }
            }

            cout << "Entered string: " << input << endl;
            cout << "Entered string size: " << sizeInput << endl;
            cout << "Occupied memory: " << sizeInput << " * 8" << " = " << sizeInput * 8 << endl;

            node *nodeHead;
            node *pointerToNext = NULL;
            node *newLeafPointer;
            for (int i = 0; i < difCarSize; i++) {
                newLeafPointer = new node(frequency[i], differentCharacters, i);
                newLeafPointer->next = pointerToNext;
                pointerToNext = newLeafPointer;
            }
            nodeHead = pointerToNext;

            node *deletingNode1;
            node *deletingNode2;
            node *comparedNode;
            node *tmpNode;
            while (nodeHead->next != NULL) {
                if (nodeHead->frequency < (nodeHead->next->frequency)) //åñëè ïåðâûé ìåíüøå âòîðîãî
                {
                    deletingNode1 = nodeHead->next;
                    deletingNode2 = nodeHead;
                } else {
                    deletingNode2 = nodeHead->next;
                    deletingNode1 = nodeHead;
                }
                comparedNode = nodeHead->next->next;
                while (comparedNode != NULL) {
                    if (deletingNode1->frequency > comparedNode->frequency) {
                        if (deletingNode2->frequency > comparedNode->frequency) {
                            tmpNode = deletingNode2;
                            deletingNode2 = comparedNode;
                            deletingNode1 = tmpNode;
                        } else {
                            deletingNode1 = comparedNode;
                        }
                    }
                    comparedNode = comparedNode->next;
                }
                node *addNode = new node(deletingNode1, deletingNode2);
                addNode->next = nodeHead;
                nodeHead = addNode;
                deleteNodeFromList(deletingNode1, nodeHead);
                deleteNodeFromList(deletingNode2, nodeHead);

            }

            enterKeys(nodeHead->rht, 1);
            enterKeys(nodeHead->lft, 0);

            cout << "Character codes:\n";
            kode.printKodes(kode.head);
            int encryptedStringSize = 0;

            cout << "Encrypted string:";
            for (int i = 0; i < sizeInput; i++)
                encryptedStringSize = encryptedStringSize + kode.find(input[i]);
            cout << endl;
            cout << "String size: " << encryptedStringSize << endl;
            cout << "Occupied memory: " << encryptedStringSize << " * 1" << " = " << encryptedStringSize << endl;
            cout << "Memory saved: " << sizeInput * 8 << " - " << encryptedStringSize << " = "
                 << sizeInput * 8 - encryptedStringSize << endl;
        }
        char * strOut =new char[1000];
        for(int i=0;i<1000;i++)  strOut[i]='\0';
            int k=0;
        for(int i=0;i<sizeInput;i++)
         {
             bit * tmpBit=kode.get(input[i]);
             while(tmpBit!=NULL)
             {
                strOut[k]=((tmpBit->data==true)?'1':'0');
                 k++;
                 tmpBit=tmpBit->next;
              }
        }
        return strOut;
    }

    void enterKeys(node *n,bool key)
    {
        if (n!=NULL)
        {
            bit * newBit= new bit;
            newBit->data=key;
            newBit->next=bitHead;
            bitHead=newBit;
            if (n->rht!=NULL)
            {
                enterKeys(n->rht,1);
                enterKeys(n->lft,0);
            }
            else
            {
                bit * tmp=bitHead;
                bit * bitHeadCopy=NULL;
                while (tmp!=NULL)
                {
                    bit * bitCopy=new bit;
                    bitCopy->data=tmp->data;
                    bitCopy->next=bitHeadCopy;
                    bitHeadCopy=bitCopy;
                    tmp=tmp->next;
                }
                kode.insert(n->name,bitHeadCopy);
            }

            bit * removeBit= bitHead;
            bitHead=bitHead->next;
            removeBit->next=NULL;
            delete removeBit;
        }
    }

    void deleteNodeFromList (node * deletingNode, node * head)
    {
        node *tmp=head;
        bool done=false;
        while ((tmp!=NULL)&&(!done))
        {
            if (tmp->next==deletingNode)
            {
                tmp->next=deletingNode->next;
                done=true;
            }
            tmp=tmp->next;
        }
    }

};
#endif //SETTINGUPGOOGLETESTS_HAFFMAN_H
