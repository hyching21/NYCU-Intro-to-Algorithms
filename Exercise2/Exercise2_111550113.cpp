#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int data;
    Node* parent;
    Node* left;
    Node* right;
    int color; //0 black, 1 red
};

class RBT{
private:
    Node* root;
    Node* tnull;
    void left_rotate(Node*cur){
        Node* y =cur->right;
        cur->right=y->left;
        if(y->left!=tnull){
            y->left->parent=cur;
        }
        y->parent=cur->parent;
        if(cur->parent==nullptr){ //set y as root
            this->root=y;
        }
        else if(cur==cur->parent->left){
            cur->parent->left=y;
        }
        else{
            cur->parent->right=y;
        }
        y->left = cur;
        cur->parent = y;
    }
    void right_rotate(Node*cur){
        Node* y =cur->left;
        cur->left=y->right;
        if(y->right!=tnull){
            y->right->parent=cur;
        }
        y->parent=cur->parent;
        if(cur->parent==nullptr){ //set y as root
            this->root=y;
        }
        else if(cur==cur->parent->left){
            cur->parent->left=y;
        }
        else{
            cur->parent->right=y;
        }
        y->right = cur;
        cur->parent = y;
    }
    void transplant(Node*u, Node*v){
        if(u->parent==nullptr){
            root=v;
        }
        else if(u==u->parent->left){
            u->parent->left=v;
        }
        else{
            u->parent->right=v;
        }
        v->parent=u->parent;
    }
    void delete_helper(Node*cur, int key){
        Node* x; //x:delete node's child,
        Node* y; //y:real delete node
        Node* z=tnull; //delete node
        //search delete node
        while(cur!=tnull){
            if(key==cur->data){
                z=cur;
                break;
            }
            else if(key<cur->data){
                cur=cur->left;
            }
            else{
                cur=cur->right;
            }
        }
        y=z;
        int y_original_color = y->color;
        if(z->left==tnull){ // case:zero or one child
            x=z->right;
            transplant(z,z->right);
        }
        else if(z->right==tnull){ // case:one child
            x=z->left;
            transplant(z,z->left);
        }
        else{ // case:two children
            y=minimum(z->right);
            y_original_color=y->color;
            x=y->right;
            if(y->parent==z){ // y is directly delete node's child
                x->parent=y;
            }
            else{
                transplant(y,y->right); // y-right replace y
                y->right=z->right; // let original z's child be y's child
                y->right->parent=y;
            }
            transplant(z,y);
            y->left=z->left;
            y->left->parent=y;
            y->color=z->color;
        }
        delete z;
        if(y_original_color==0){
            delete_fix(x);
        }
    }
    void delete_fix(Node* cur){
        while(cur!=root && cur->color==0){ //cur is black and not root->draw it as red
            if(cur==cur->parent->left){ // cur is left
                Node* s=cur->parent->right; //sibilings
                if(s->color==1){ //case 1: sibilings is red
                    s->color=0;
                    cur->parent->color=1;
                    left_rotate(cur->parent);
                    s=cur->parent->right;
                }
                if(s->left->color==0 && s->right->color==0){ //case 2: both sibilings' children are black
                    s->color=1;
                    cur=cur->parent;
                }
                else{ //sibilings' children: 1 black 1 red
                    if(s->right->color==0){ //case 3: right black left red
                        s->left->color=0;
                        s->color=1;
                        right_rotate(s);
                        s=cur->parent->right;
                    }
                    s->color=cur->parent->color; //case 4: right red left black
                    cur->parent->color=0;
                    s->right->color=0;
                    left_rotate(cur->parent);
                    cur=root;
                }
            }
            else{               // cur is right
                Node* s=cur->parent->left;
                if(s->color==1){ //case 1: sibilings is red
                    s->color=0;
                    cur->parent->color=1;
                    right_rotate(cur->parent);
                    s=cur->parent->left;
                }
                if(s->right->color==0 && s->left->color==0){ //case 2: both sibilings' children are black
                    s->color=1;
                    cur=cur->parent;
                }
                else{ //sibilings' children: 1 black 1 red
                    if(s->left->color==0){ //case 3: right black left red
                        s->right->color=0;
                        s->color=1;
                        left_rotate(s);
                        s=cur->parent->left;
                    }
                    s->color=cur->parent->color; //case 4: right red left black
                    cur->parent->color=0;
                    s->left->color=0;
                    right_rotate(cur->parent);
                    cur=root;
                }
            }
        }
        cur->color=0; // black
    }
    void insert_fix(Node* cur){
        while(cur->parent->color==1){
            if(cur->parent==cur->parent->parent->left){ //parent is left
                Node* u=cur->parent->parent->right; //uncle
                if(u->color==1){ //case 1
                    cur->parent->color=0;
                    u->color=0;
                    cur->parent->parent->color=1;
                    cur=cur->parent->parent;
                }
                else {
                    if(cur==cur->parent->right){ // case 2
                        cur=cur->parent;
                        left_rotate(cur);
                    }
                    cur->parent->color=0;
                    cur->parent->parent->color=1;
                    right_rotate(cur->parent->parent);
                }
            }
            else{ //parent is right
                Node* u=cur->parent->parent->left; //uncle
                if(u->color==1){ //case 1
                    cur->parent->color=0;
                    u->color=0;
                    cur->parent->parent->color=1;
                    cur=cur->parent->parent;
                }
                else {
                    if(cur==cur->parent->left){ // case 2
                        cur=cur->parent;
                        right_rotate(cur);
                    }
                    cur->parent->color=0;
                    cur->parent->parent->color=1;
                    left_rotate(cur->parent->parent);
                }
            }
            if (cur==root) {
                break;
            }
        }
        root->color=0; // ensure root's color is black
    }
    void print_helper(Node* root){
        if(root!=tnull){
            print_helper(root->left);
            string par;
            if(root->parent==nullptr){
                par=" ";
            }else{
                Node* p=root->parent;
                par=to_string(p->data);
            }
            string col;
            if(root->color==0){
                col="black";
            }else{
                col="red";
            }
            cout<<"key: "<<root->data<<" parent: "<<par<<" color: "<<col<<"\n";
            print_helper(root->right);
        }
    }

public:
    RBT(){
        tnull=new Node;
        tnull->left=nullptr;
        tnull->right=nullptr;
        tnull->color=0; //black
        root=tnull;
    }
    Node* minimum(Node* node){
        while(node->left!=tnull){
            node=node->left;
        }
        return node;
    }
    void INSERT(int key){
        Node*node = new Node;
        node->data=key;
        Node* y=nullptr;
        Node* x=this->root;

        while(x!=tnull){
            y=x;
            if(node->data < x->data){
                x=x->left;
            }
            else{
                x=x->right;
            }
        }
        node->parent=y;
        if(y==nullptr){ //x is tnull, set node to root
            root=node;
        }
        else if(node->data < y->data){
            y->left=node;
        }
        else{y->right=node;}
        node->left=tnull;
        node->right=tnull;
        node->color=1; //red
        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }
        insert_fix(node);
    }
    void DELETE(int key){
        delete_helper(this->root, key);
    }
    void print(){
        print_helper(root);
    }

};
int main(){
    int t; // task
    cin>>t;
    RBT rbt;
    while(t!=0){
        int op, n; // operation, num of element
        cin>>op>>n;
        vector<int> nodelist(n);
        for(int i=0;i<n;i++){
            int node;
            cin>>node;
            nodelist[i]=node;
        }
        if(op==1){
            cout<<"Insert: ";
            for(int i=0;i<n;i++){
                if(i!=n-1){
                    cout<<nodelist[i]<<", ";
                }
                else{cout<<nodelist[i]<<"\n";}
            }
            for(int i=0;i<n;i++){
                rbt.INSERT(nodelist[i]);
            }
        }
        else {
            cout<<"Delete: ";
            for(int i=0;i<n;i++){
                if(i!=n-1){
                    cout<<nodelist[i]<<", ";
                }
                else{cout<<nodelist[i]<<"\n";}
            }
            for(int i=0;i<n;i++){
                rbt.DELETE(nodelist[i]);
            }
        }
        rbt.print();  //output:key parent color (inorder traversal)
        t--;
    }
    return 0;
}
