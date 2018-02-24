#include <stdlib.h>
#include <stdio.h>

#ifdef WIN32 //se sistema operacional for windows
#define CLEAR_SCREEN "cls"
#define SET_COLOR "color 1f"
#else //senao
#define CLEAR_SCREEN "clear"
#define SET_COLOR "setterm -term linux -back white -fore blue -clear"
#endif

typedef struct no{
    int key;
    struct no *father;
    struct no *left;
    struct no *right;
    int fb;
}node;
typedef struct caracter{
	struct caracter *prev;
	char *str;
}caracter;

node *tree; /**"SEMENTE" DA ARVORE**/

/**PROTOTIPOS**/
int height(node *root); //calcula a altura de um n�
int fbCalc(node *root); //calcula o fb de um n�
void treeBalance(node *root); //verifica o fb do n� e realiza as rota��es necess�rias
int nodeCount(node *root); //conta a quantidade de n�s da �rvore
node* treeMaximum(node *root); //retorna o n� com o maior valor da �rvore
node* treeMinimum(node *root); //retorna o n� com o menor valor da �rvore
void rotationRight(node **root); //realiza uma rota��o a direita
void rotationLeft(node **root); //realiza uma rota��o a esqeuerda
void rotationDoubleRight(node **root); //realiza uma rota��o esquerda direita
void rotationDoubleLeft(node **root); //realiza uma rota��o direita esquerda
void caracterShow(caracter *p);                             //
void nodePrint(node *root, caracter *prev ,int is_left);    //fun��es para imprimir a �rvore from google
void treePrint(node *tree);                                 //
int treeSearch(node *root, int value); //verifica se o elemento est� na �rvore
void treeClear(node **root); //exclui todos os nos da arvore
void treeInsert(node **root, int value); //insere um elemento na �rvore
void treeRemove(node **root, int value); //remove um elemento da �rovre
/**PROTOTIPOS_END**/

/**----------------------------------MAIN MENU-----------------------------------**/
int main(void){

    system(SET_COLOR);
    tree = NULL;
    int x;
    int op = 1, generated = 0;
    srand((unsigned)time(NULL));

    while(op != 0){
        op = Menu();
        system(CLEAR_SCREEN);
        switch(op){
            case 0:{ //sair
                printf("Aplicacao encerrada!\n");
                break;
            }
            case 1:{ //inserir um novo elemento
                printf("Digite o numero que deseja inserir...");
                scanf("%d",&x);
                treeInsert(&tree,x);
                generated = 1;
                break;
            }
            case 2:{ //remover um elemento
                if(tree == NULL){
                    printf("A arvore esta vazia!!");
                    break;
                }
                printf("Digite o valor que deseja remover...");
                scanf("%d", &x);
                treeRemove(&tree, x);
                if(nodeCount(tree) == 0) generated = 0;
                break;
            }
            case 3:{ //imprimir a arvore
                if(tree == NULL)
                    printf("A arvore esta vazia!!");
                else
                    treePrint(tree);
                break;
            }
            case 4:{ //procurar por um valor na arvore
                if(generated){
                    printf("Digite o valor que deseja pesquisar...");
                    scanf("%d",&x);
                    if(treeSearch(tree, x))
                        printf("O valor %d ja esta na arvore!\n",x);
                    else
                        printf("Valor nao encontrado na arvore\n");
                }
                else
                    printf("A arvore esta vazia!!");
                break;
            }
            case 5:{ //infroma��es gerais sobre a arvore
                if(generated){
                    printf("\nAltura total......: %d", height(tree));
                    printf("\nQuantidade de nos.: %d", nodeCount(tree));
                    printf("\nMenor valor.......: %d", treeMinimum(tree)->key);
                    printf("\nMaior valor.......: %d\n", treeMaximum(tree)->key);
                }
                else
                    printf("A arvore esta vazia!!");
                break;
            }
            case 6:{ //gerar uma arvore aleatoria com n com valores entre min-max
                int i=0, n, min, max, mod;
                if(generated)
                    printf("Uma arvore ja foi gerada!!");
                else{
                    generated = 1;
                    printf("Digite a quantidade de nos...");
                    scanf("%d", &n);
                    printf("Valor minimo...");
                    scanf("%d", &min);
                    printf("Valor maximo...");
                    scanf("%d", &max);
                    mod = max-min+1;

                    while(nodeCount(tree)!=n)
                        treeInsert(&tree, min + rand()%mod);
                }
                break;
            }
            case 7:{
                if(generated == 0){
                    printf("A arvore esta vazia!!");
                    break;
                }
                treeClear(&tree);
                printf("Arvore excluida com sucesso!!");
                generated = 0;
                break;
            }
        }
        getchar();
        getchar();
    }

    return EXIT_SUCCESS;
}
int Menu(void){
    int op;

    system(CLEAR_SCREEN);
    printf("\n\\-----------------------ARVORE AVL------------------------/\n\n\n");
    printf("Digite o numero correspondente a operacao para executa-la...\n\n");
    printf(" 1) Inserir elemento\n");
    printf(" 2) Remover elemento\n");
    printf(" 3) Visualizar arvore\n");
    printf(" 4) Buscar elemento\n");
    printf(" 5) Informacoes gerais sobre a arvore\n");
    printf(" 6) Gerar arvore aleatoria\n");
    printf(" 7) Limpar arvore\n");
    printf(" 0) Sair\n\n");
    scanf("%d",&op);

    while((op < 0)||(op > 7)){
        printf("\nOpcao invalida, digite novamente...");
        scanf("%d",&op);
    }

    return op;
}
/**-----------------------------MAIN MENU_END------------------------------------**/

/**UTILIDADES**/
int height(node *root){
    int h_left, h_right;
    if(root == NULL)
        return -1;
    else{
        h_left = height(root->left);
        h_right = height(root->right);
        if(h_left > h_right)
            return h_left+1;
        else
            return h_right+1;
    }
}
int fbCalc(node *root){
    int x;
    x = height(root->right)-height(root->left);
    return x;
}
void treeBalance(node *root){
    switch(root->fb){
        case -2:{
            switch(root->left->fb){
                case -1:{
                    rotationRight(&root);
                    break;
                }
                case 0:{
                    rotationDoubleRight(&root);
                    break;
                }
                case 1:{
                    rotationDoubleRight(&root);
                    break;
                }
            }
            break;
        }
        case 2:{
            switch(root->right->fb){
                case 1:{
                    rotationLeft(&root);
                    break;
                }
                case 0:{
                    rotationDoubleLeft(&root);
                    break;
                }
                case -1:{
                    rotationDoubleLeft(&root);
                }
            }
            break;
        }
    }
}
int nodeCount(node *root){
   if(root == NULL)
        return 0;
   else
        return 1 + nodeCount(root->left) + nodeCount(root->right);
}
node* treeMaximum(node *root){
    node *aux = root;
    while(aux->right != NULL)
        aux = aux->right;

    return aux;
}
node* treeMinimum(node *root){
    node *aux = root;
    while(aux->left != NULL)
        aux = aux->left;

    return aux;
}
/**UTILIDADES_END**/

/**ROTA�OES**/
void rotationRight(node **root){
    node *aux,*p_temp;

    aux = (*root)->left;
    p_temp = (*root)->father;
    (*root)->left = aux->right;
    if(aux->right != NULL)
        aux->right->father = (*root);
    aux->right = (*root);
    aux->father = p_temp;
    (*root)->father = aux;          //
    (*root)->fb = fbCalc(*root);    // atualiza fb's dos n�s alterados
    aux->fb = fbCalc(aux);          //
    if(p_temp == NULL) //se o n� for a ra�z da �rvore
        tree = aux;    //a ra�z se torna aux
    else{
        if(p_temp->left == (*root)) //se aux � filho esquerdo de seu pai
            p_temp->left = aux; //atualiza o filho esquerdo do pai
        else
            p_temp->right = aux;    //sen�o, atualiza o filho direito do pai
        p_temp->fb = fbCalc(p_temp); //atualiza o fb do pai
    }
}
void rotationLeft(node **root){
    node *aux,*p_temp;

    aux = (*root)->right;
    p_temp = (*root)->father;
    (*root)->right = aux->left;
    if(aux->left != NULL)
        aux->left->father = (*root);
    aux->left = (*root);
    aux->father = p_temp;
    (*root)->father = aux;          //
    (*root)->fb = fbCalc(*root);    //atualiza fb's dos n�s alterados
    aux->fb = fbCalc(aux);          //
    if(p_temp == NULL) //se o n� for a ra�z da �rvore
        tree = aux;    //a ra�z se torna aux
    else{
        if(p_temp->left == (*root)) //se aux � filho esquerdo de seu pai
            p_temp->left = aux; //atualiza o filho esquerdo do pai
        else
            p_temp->right = aux;    //sen�o, atualiza o filho direito do pai
        p_temp->fb = fbCalc(p_temp); //atualiza o fb do pai
    }
}
void rotationDoubleRight(node **root){
    rotationLeft(&(*root)->left);
    rotationRight(root);
}
void rotationDoubleLeft(node **root){
    rotationRight(&(*root)->right);
    rotationLeft(root);
}
/**ROTA�OES_END**/

/**IMPRIMIR ARVORE**/
void caracterShow(caracter *p){
	if(!p)
        return;
	caracterShow(p->prev);
	printf("%s", p->str);
}
void nodePrint(node *root, caracter *prev ,int is_left){
	if (root == NULL)
        return;

	caracter this_disp = {prev,"        "};
	char *prev_str = this_disp.str;

	nodePrint(root->right, &this_disp, 1);
	if(!prev)
		this_disp.str = "-----";
	else{
        if(is_left){
            this_disp.str = ".----";
            prev_str = "       |";
        }
        else{
            this_disp.str = "`----";
            prev->str = prev_str;
        }
	}
	caracterShow(&this_disp);
	printf("[%2d|%2d]\n",root->key,root->fb);

	if(prev)
        prev->str = prev_str;
	this_disp.str = "       |";

	nodePrint(root->left,&this_disp,0);
	if(!prev)
        puts("");
}
void treePrint(node *tree){
    system(CLEAR_SCREEN);
    printf("[Chave | Fator de Balanceamento]\n\n");
    nodePrint(tree,0,0);
}
/**IMPRIMIR ARVORE_END**/

/**OPERA�OES**/
int treeSearch(node *root, int value){
    if(root == NULL)
        return 0;
    else{
        if(value < root->key)
            treeSearch(root->left, value);
        else if(value > root->key)
            treeSearch(root->right, value);
        else
            return 1;
    }
}
void treeClear(node **root){
    if((*root) == NULL)
        return;

    treeClear(&(*root)->left);
    treeClear(&(*root)->right);
    free(*root);
    (*root) = NULL;
}
void treeInsert(node **root, int value){
    node *aux;
    if(*root == NULL){ //   insere o novo n�
        aux = (node*)malloc(sizeof(node));
        aux->key = value;
        aux->left = NULL;
        aux->right = NULL;
        aux->father = NULL;
        aux->fb = 0;
        *root = aux;
        printf("\n%d inserido com sucesso!",value);
    }
    else{
        if(value < (*root)->key){
            treeInsert(&(*root)->left, value);
            if(((*root)->left->left == NULL)&&((*root)->left->right == NULL))
                (*root)->left->father = *root; //atualiza o pai do novo n� inserido
        }
        else if(value > (*root)->key){
            treeInsert(&(*root)->right, value);
            if(((*root)->right->left == NULL)&&((*root)->right->right == NULL))
                (*root)->right->father = *root; //atualiza o pai do novo n� inserido
        }

        (*root)->fb = fbCalc(*root);    //atualiza o fb do novo n�
        treeBalance(*root); //balanceia o novo n�, se necess�rio
    }
}
void treeRemove(node **root, int value){
    node *aux;

    if((*root) == NULL)
        printf("\nValor nao encontrado!\n");
    else{
        if(value < (*root)->key)    //se value for for menor que (*root)->key,
            treeRemove(&(*root)->left, value);  //chamada recursiva a esquerda
        else if(value > (*root)->key)   //se value for for maior que (*root)->key,
            treeRemove(&(*root)->right, value); //chamada recursiva a direita
        else{   //(*root)->key � igual a value
            aux = (*root);
            if(((*root)->left == NULL)&&((*root)->right == NULL)) //(*root) � uma folha
                (*root) = NULL;
            else if((*root)->left == NULL){ //(*root) s� possui filho a direita
                (*root) = (*root)->right;   //substitui o n� exclu�do pelo filho da direita
                (*root)->father = aux->father;  //atualiza o pai do n�
            }
            else if((*root)->right == NULL){    //(*root) s� possui filho a esquerda
                (*root) = (*root)->left;    //substitui o n� exclu�do pelo filho da esquerda
                (*root)->father = aux->father;   //atualiza o pai do n�
            }
            else{   //(*root) possui 2 filhos
                int x;
                x = treeMinimum((*root)->right)->key;   //x recebe o valor do sucessor
                treeRemove(&tree, x); //remove o n� sucessor
                aux->key = x;   //atribui o valor do sucessor ao n�
            }
            aux = NULL;
        }
        if((*root) != NULL){ // atualiza o fb do n� e verifica o balan�o
            (*root)->fb = fbCalc(*root);
            treeBalance(*root);
        }
    }
}
/**OPERA�OES_END**/
