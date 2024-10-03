#include <iostream>
#include<bits/stdc++.h>
#include<vector>
#include<string>
#include<utility>
#include<cstdio>
#include "lex.yy.c"
using namespace std;

/*
Attributes possesed
- + x ^ X S no attribute
digit val 
N val 
M both attributes
P T inh
*/


struct Node {
    
        int val;                   // Synthesized attribute (int)
        string inh;                  // Inherited attribute (char)
        std::pair<int, char> p;    // Both attributes (int and char)
    
    
    vector<Node*> child_arr;       // Child nodes array
    char type;                     // Node type
    int production_rule;
    
    // Constructor: Initializes the union based on the required type
    Node() : type('S'),production_rule(0) {}
   
    ~Node() {}
    void setInt(int value) {val = value;}

    // Set method for char attribute
    void setChar(char value) {inh = value;}

    // Set method for both int and char attributes (manually construct the pair)
    void setPair(int value, char ch) {
        new(&p) std::pair<int, char>(value, ch);  // Placement new for pair
    }

    // Explicitly destroy the pair when it is no longer needed
    void destroyPair() {
        p.~pair();  // Call the destructor of std::pair manually
    }
};

struct Node* root=new Node();


Node* create_node(char type,int prod_rule){
    struct Node* node=new Node;
    node->type=type;
    node->production_rule=prod_rule;
    return node;
}



void add_child(struct Node* node,struct Node* child){
node->child_arr.push_back(child);
return;
}

void add_to_root(struct Node* node,int prod_rule){
root->child_arr.push_back(node);
root->production_rule=prod_rule;
return;
}

vector<Node*> T_nodes; 

void print_tree(struct Node* node,int level){
    for(int i=1;i<=level;i++){cout<<"\t";}
    char type=node->type;
     switch(type){
        case 'S':     
        case '-':
        case '+':
        case 'x':
        case 'X':
        case '^': cout<<"==>"<<type<<"[ ]"<<"\n"; break;
        case 'T':
        case 'P': cout<<"==>"<<type<<"[ inh :"<<node->inh<<" ]\n";break;
        case 'M':cout<<"==>"<<type<<"[ inh :"<<node->inh<<" val :"<<node->val<< " ]\n";break;
        default :cout<<"==>"<<type<<"[ val :"<<node->val<<" ]\n";break;
               
     }
     if(type=='T') T_nodes.push_back(node);
     
     
     for(auto child:node->child_arr){
        print_tree(child,level+1);
     }
}

void set_attributes(struct Node* node ){
    
vector<Node* > v=node->child_arr;
   // cout<<node->production_rule<<"\n";
    if(node->production_rule==1){

        struct Node* n=v[0];
        n->inh="+";
        set_attributes(n);
    }

    if(node->production_rule==2){
        struct Node* n=v[1];
        n->inh="+";
        set_attributes(n);
     }
   if(node->production_rule==3){
    struct Node* n=v[1];
        n->inh="-";
        set_attributes(n);

   }
 if(node->production_rule==4){
     struct Node* n=v[0];
        n->inh=node->inh;
        set_attributes(n);
 }

 if(node->production_rule==5){
    struct Node* n1=v[0];
    struct Node* n2=v[2];
    n1->inh=node->inh;
    n2->inh="+";
    set_attributes(n1);
    set_attributes(n2);
}

if(node->production_rule==6){
    struct Node* n1=v[0];
    struct Node* n2=v[2];
    n1->inh=node->inh;
    n2->inh="-";
    set_attributes(n1);
    set_attributes(n2);
}

if(node->production_rule==7){
struct Node* n=v[0];
n->val=1;
}

if(node->production_rule==8){
    struct Node* n=v[0];
    set_attributes(n);
}

if(node->production_rule==9){struct Node* n=v[0];
                             set_attributes(n);}
if(node->production_rule==10)  {    struct Node* n1=v[0];
                                     struct Node* n2=v[1];
                                    set_attributes(n1);
                                    set_attributes(n2);
                                }   

if(node->production_rule==11){}
if(node->production_rule==12){struct Node* n2=v[2];
                               set_attributes(n2);}
if(node->production_rule==13){
                              struct Node* n1=v[0];
                              n1->val=(n1->type)-'0';
                              node->val=n1->val; 
                             }                  
if(node->production_rule==14){
                               struct Node* n1=v[0];
                               struct Node* n2=v[1];
                               n2->inh="1";
                               n1->val=1;
                               set_attributes(n2);
                               node->val=n2->val;

                             }  
if(node->production_rule==15) {
                               struct Node* n1=v[0];
                               struct Node* n2=v[1];
                               n1->val=(n1->type)-'0';
                               string str(1,n1->type);
                               n2->inh=str;
                               set_attributes(n2);
                               node->val=n2->val;

                             }    
if(node->production_rule==16){
                              struct Node* n1=v[0];
                              n1->val=0;
                              string s=(node->inh)+(n1->type);
                              node->val=stoi(s);

                             }  
if(node->production_rule==17){
                              struct Node* n1=v[0];
                              n1->val=1;
                              string s=(node->inh)+(n1->type);
                              node->val=stoi(s);
                             }                                                                                                                        
if(node->production_rule==18){struct Node* n1=v[0];
                              n1->val=int((n1->type)-'0');
                              string s=(node->inh)+(n1->type);
                              node->val=stoi(s);
                             }
if(node->production_rule==19||node->production_rule==20||node->production_rule==21){
                              struct Node* n1=v[0];
                              struct Node* n2=v[1];
                              string str=(node->inh)+(n1->type);
                              n2->inh=str;
                              n1->val=(n1->type)-'0';
                              set_attributes(n2);
                              node->val=n2->val;     

                             }   

    


}

int eval_X(int x,struct Node* node){

if(node->production_rule==11) return x;
else{
int p=node->child_arr[2]->val;
return pow(x,p);
}
}
//evaluates T node for given x
int eval_T(int x,struct Node* node){
    int ans=0;
    int sign_multiplier=(node->inh=="-")?-1:1;
if(node->production_rule==7||node->production_rule==8){
ans=sign_multiplier*(node->child_arr[0]->val);
}

if(node->production_rule==9){
ans=sign_multiplier*eval_X(x,node->child_arr[0]) ;
}
if(node->production_rule==10){
ans=sign_multiplier*eval_X(x,node->child_arr[1])*(node->child_arr[0]->val) ;
    
}
return ans;

}

int evalpoly(int x){
int ans=0;
//cout<<T_nodes.size()<<"\n";
for(auto T:T_nodes){
    ans+=eval_T(x,T);
 //   cout<<ans<<"\n";

}

return ans;
}

void print_derivative(){

for(auto T:T_nodes){
    if(T->production_rule==9){
     
     struct Node* node=T->child_arr[0];

     if(node->production_rule==11) cout<<T->inh<<1;
     if(node->production_rule==12){ 
        int p=(node->child_arr[2]->val-1);
        if(p!=0&&p!=1)cout<<T->inh<<(p+1) <<"x^"<<p;
        else if(p==0) cout<<T->inh<<(p+1) ;
        else if(p==1) cout<<T->inh<<(p+1) <<"x";
     }
    }

    if(T->production_rule==10){
        struct Node* node=T->child_arr[1];

     if(node->production_rule==11) cout<<T->inh<<(T->child_arr[0]->val);
     if(node->production_rule==12){
        int p=(node->child_arr[2]->val-1);
        if(p!=0&&p!=1)cout<<T->inh<<(T->child_arr[0]->val)*(p+1) <<"x^"<<p;
        else if(p==0) cout<<T->inh<<(T->child_arr[0]->val)*(p+1) ;
        else if(p==1) cout<<T->inh<<(T->child_arr[0]->val)*(p+1) <<"x";
        
        
        // cout<<T->inh<<(T->child_arr[0]->val)*(node->child_arr[2]->val) <<"x^"<<(node->child_arr[2]->val-1);
     }


    }

}



}



int main(int argc, char* argv[]){
  if (argc != 2) {
        cout<<"Usage: "<< argv[0]<<" <input_file>"<< endl;
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        cout <<"Error: Unable to open file "<<argv[1]<< endl;
        return 1;
    }
    yyin=input_file;
    
    yyparse();
     cout<<"\n";
    // cout<<"++parse_tree brfore Annotation++\n";
    //print_tree(root,0);
     cout<<"+++parse_tree after Annotation++\n";
     set_attributes(root);
     print_tree(root,0);

     for(int i=-5;i<=5;i++){
        cout<<" +++f( "<<i<<" ) = "<<evalpoly(i)<<"\n";
     }

     print_derivative();
     cout<<"\n";
 



    return 0;
}
