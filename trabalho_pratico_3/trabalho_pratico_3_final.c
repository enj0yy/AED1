#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int MaiorCaminho( struct TreeNode * p )
{
    int esq, dir;

    if ( p == NULL )
        return 0;

    esq = MaiorCaminho(p->left);
    dir = MaiorCaminho(p->right);

    if ( esq > dir )
        return 1 + esq;
    else
        return 1 + dir;
}

int diameterOfBinaryTree( struct TreeNode * root )
{
    int mEsq, mDir, mRaiz;

    if ( root == NULL )
        return 0;

    mEsq = diameterOfBinaryTree(root->left);
    mDir = diameterOfBinaryTree(root->right);
    mRaiz = MaiorCaminho(root->left) + MaiorCaminho(root->right);

    if ( mRaiz >= mEsq && mRaiz >= mDir )
        return mRaiz;
    else if ( mEsq >= mRaiz && mEsq >= mDir )
        return mEsq;
    else
        return mDir;
}

void Central( struct TreeNode * p, int root )
{
    if ( p == NULL )
        return;
     
    Central(p->left,0);
    printf("%s %d\n",root ? "R" : " ",p->val);
    Central(p->right,0);
}

struct TreeNode * LimparArvore( struct TreeNode * p )
{
    if ( p == NULL )
        return NULL;

    p->left = LimparArvore(p->left);
    p->right = LimparArvore(p->right);
    free(p);

    return NULL;
}

int Inserir( struct TreeNode ** p, int val )
{
    if ( *p == NULL )
    {
        (*p) = malloc( sizeof(struct TreeNode) );
        (*p)->val = val;
        (*p)->left = NULL;
        (*p)->right = NULL;
        return 1;
    }
    else
    {
        if ( val < (*p)->val )
        {
            Inserir(&(*p)->left, val);  
        }
        else if ( val > (*p)->val )
        {
            Inserir(&(*p)->right, val);
        }
        else if ( val == (*p)->val )
        {
            printf("Chave %d ja existente na arvore.\n",val);
            return 0;
        }
        return 1;
    }
}

int main()
{
    struct TreeNode * raiz = NULL;
    
    Inserir(&raiz, 1);
    Inserir(&raiz, 2);
    printf("Caso 1:\n");
    Central(raiz,1);
    printf("Diametro: %d\n\n",diameterOfBinaryTree(raiz));
    raiz = LimparArvore(raiz);

    Inserir(&raiz, 2);
    Inserir(&raiz, 1);
    Inserir(&raiz, 3);
    printf("Caso 2:\n");
    Central(raiz,1);
    printf("Diametro: %d\n\n",diameterOfBinaryTree(raiz));
    raiz = LimparArvore(raiz);

    Inserir(&raiz, 10);
    Inserir(&raiz, 5);
    Inserir(&raiz, 3);
    Inserir(&raiz, 7);
    Inserir(&raiz, 4);
    Inserir(&raiz, 8);
    printf("Caso 3:\n");
    Central(raiz,1);
    printf("Diametro: %d\n\n",diameterOfBinaryTree(raiz));
    raiz = LimparArvore(raiz);

    Inserir(&raiz, 10);
    Inserir(&raiz, 15);
    Inserir(&raiz, 13);
    Inserir(&raiz, 20);
    Inserir(&raiz, 25);
    Inserir(&raiz, 30);
    Inserir(&raiz, 40);
    Inserir(&raiz, 18);
    Inserir(&raiz, 17);
    Inserir(&raiz, 16);
    printf("Caso 4:\n");
    Central(raiz,1);
    printf("Diametro: %d",diameterOfBinaryTree(raiz));
    raiz = LimparArvore(raiz);

    return 0;
}
