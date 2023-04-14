#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int MaiorCaminho(struct TreeNode * p)
{
    int esq,dir;

    if (p == NULL)
        return 0;

    esq = MaiorCaminho(p->left);
    dir = MaiorCaminho(p->right);

    if (esq > dir)
        return 1 + esq;
    else
        return 1 + dir;
}

int diameterOfBinaryTree(struct TreeNode * root){
    int mesq = 0;
    int mdir= 0;

    int mraiz = MaiorCaminho(root->left) + MaiorCaminho(root->right);

    if (root->left != NULL)
    mesq = MaiorCaminho(root->left->left) + MaiorCaminho(root->left->right);

    if (root->right != NULL)
    mdir = MaiorCaminho(root->right->left) + MaiorCaminho(root->right->right);

    if (mraiz >= mesq && mraiz >= mesq)
        return mraiz;
    else if (mesq >= mraiz && mesq >= mdir)
        return mesq;
    else
        return mdir;
}

void Central(struct TreeNode * p, int root)
{
    if (p == NULL)
        return;
     
    Central(p->left,0);
    printf("%s %d\n",root ? "R" : " ",p->val);
    Central(p->right,0);
}

struct TreeNode * LimparArvore(struct TreeNode * p)
{
    if (p == NULL)
        return NULL;

    p->left = LimparArvore(p->left);
    p->right = LimparArvore(p->right);
    free(p);

    return NULL;
}

int main()
{
    struct TreeNode * raiz = NULL;
    struct TreeNode * p = NULL;
    struct TreeNode * p2 = NULL;
    
    raiz = malloc(sizeof(struct TreeNode));
    raiz->val = 1;

    p = malloc(sizeof(struct TreeNode));
    p->val = 3;
    p->right = NULL;
    p->left = NULL;
    raiz->right = p;

    p = malloc(sizeof(struct TreeNode));
    p->val = 2;
    raiz->left = p;

    p2 = malloc(sizeof(struct TreeNode));
    p2->val = 4;
    p2->right = NULL;
    p2->left = NULL;
    p->left = p2;

    p2 = malloc(sizeof(struct TreeNode));
    p2->val = 5;
    p2->right = NULL;
    p2->left = NULL;
    p->right = p2;

    printf("Arvore Listada Centralmente (Caso 1): \n");
    Central(raiz,1);
    printf("Diametro: %d\n\n",diameterOfBinaryTree(raiz));
    raiz = LimparArvore(raiz);

    raiz = malloc(sizeof(struct TreeNode));
    raiz->val = 1;
    raiz->left = NULL;

    p = malloc(sizeof(struct TreeNode));
    p->val = 2;
    p->right = NULL;
    p->left = NULL;
    raiz->right = p;

    printf("Arvore Listada Centralmente (Caso 2): \n");
    Central(raiz,1);
    printf("Diametro: %d\n\n",diameterOfBinaryTree(raiz));
    raiz = LimparArvore(raiz);

    raiz = malloc(sizeof(struct TreeNode));
    raiz->val = 1;
    raiz->right = NULL;

    p = malloc(sizeof(struct TreeNode));
    p->val = 2;
    raiz->left = p;

    p2 = malloc(sizeof(struct TreeNode));
    p2->val = 4;
    p2->left = NULL;
    p->left = p2;

    p2 = malloc(sizeof(struct TreeNode));
    p2->val = 5;
    p2->left = NULL;
    p->right = p2;

    p = malloc(sizeof(struct TreeNode));
    p->val = 6;
    p->right = NULL;
    p->left = NULL;
    p2->right = p;

    p2 = malloc(sizeof(struct TreeNode));
    p2->val = 7;
    p2->right = NULL;
    p2->left = NULL;
    p->right = p2;

    printf("Arvore Listada Centralmente (Caso 3): \n");
    Central(raiz,1);
    printf("Diametro: %d\n",diameterOfBinaryTree(raiz));
    raiz = LimparArvore(raiz);

    return 0;
}
