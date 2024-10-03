%{
    #include <stdio.h>
    
    struct Node;
    Node* create_node(char type,int prod_rule);
    void add_child(struct Node* node,struct Node* child);
    void add_to_root(struct Node* node,int prod_rule  );

    void yyerror(const char *s);
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;

%}

%union{
    
    int val;
    struct Node* node;
    
}

%token<val> zero one D
%type<node>N M P T S X

%start S

%%
S:  P      { add_to_root($1,1); }
  | '+' P  { 
             struct Node* node1= create_node('+',0);
             add_to_root(node1,2);
             add_to_root($2,2);
                    }
  | '-' P  { struct Node* node1= create_node('-',0);
             add_to_root(node1,3);
             add_to_root($2,3);

           }
  ;

P : T        {   struct Node* node= create_node('P',4);
                 add_child(node,$1);
                 $$=node;

              }
   | T '+' P {   struct Node* node= create_node('P',5);
                 struct Node* node1= create_node('+',0);
                 add_child(node,$1);
                 add_child(node,node1);
                 add_child(node,$3);   
                 $$=node;
                 }
   | T '-' P {
                 struct Node* node= create_node('P',6);
                 struct Node* node1= create_node('-',0);
                 add_child(node,$1);
                 add_child(node,node1);
                 add_child(node,$3);   
                 $$=node;
              }
   ;

T : one        { struct Node* node= create_node('T',7);
                 struct Node* node1= create_node('1',0);
                 add_child(node,node1);
                 $$=node;
                }
   | N         {struct Node* node= create_node('T',8);
                 add_child(node,$1);
                 $$=node;
                }
   | X         {
                 struct Node* node= create_node('T',9);
                 add_child(node,$1);
                 $$=node;
               }
   | N X       {
                struct Node* node= create_node('T',10);
                 add_child(node,$1);
                 add_child(node,$2);
                 $$=node;

                }
   ;
X : 'x'         {
                 struct Node* node= create_node('X',11);
                 struct Node* node1= create_node('x',0);
                add_child(node,node1);
                $$=node;
                }
   | 'x' '^' N   {struct Node* node= create_node('X',12);
                 struct Node* node1= create_node('x',0);
                 struct Node* node2= create_node('^',0);
                add_child(node,node1);
                add_child(node,node2);
                add_child(node,$3);
                $$=node;

                }
   ;
N : D            {
                    struct Node* node= create_node('N',13);
                    char ch='0'+$1;
                    struct Node* node1= create_node(ch,0);
                    add_child(node,node1);
                    $$=node;
                 }
    | one M      { struct Node* node= create_node('N',14);
                 struct Node* node1= create_node('1',0);
                 add_child(node,node1);
                 add_child(node,$2);
                 $$=node;


    }
    | D M        {struct Node* node= create_node('N',15);
                    char ch='0'+$1;
                    struct Node* node1= create_node(ch,0);
                    add_child(node,node1);
                    add_child(node,$2);

                    $$=node;
                    }
    ;
M : zero          {
                    struct Node* node= create_node('M',16);
                    struct Node* node1= create_node('0',0);
                    add_child(node,node1);
                    $$=node;
                  }
    |one          {
                   
                    struct Node* node= create_node('M',17);
                    struct Node* node1= create_node('1',0);
                    add_child(node,node1);
                    $$=node;
    }
    |D            {struct Node* node= create_node('M',18);
                    char ch='0'+$1;
                    struct Node* node1= create_node(ch,0);
                    add_child(node,node1);
                    $$=node;
                    }
    | zero M      { struct Node* node= create_node('M',19);
                 struct Node* node1= create_node('0',0);
                 add_child(node,node1);
                 add_child(node,$2);
                 $$=node;

                  }
    | one M       { struct Node* node= create_node('M',20);
                 struct Node* node1= create_node('1',0);
                 add_child(node,node1);
                 add_child(node,$2);
                 $$=node;
                 }
    | D M         { struct Node* node= create_node('M',21);
                    char ch='0'+$1;
                    struct Node* node1= create_node(ch,0);
                    add_child(node,node1);
                    add_child(node,$2);
                    $$=node;
                   }
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
