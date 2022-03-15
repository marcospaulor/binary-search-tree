#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct NO{
    int info;
    struct NO *left;
    struct NO *right;
};

typedef struct NO *ArvBin;

ArvBin* cria_arvbin();
void libera_arvbin(ArvBin* root);
void libera_NO(struct NO* no);
int vazia_arvbin(ArvBin* root);
int altura_arvbin(ArvBin* root);
int totalNO_arvbin(ArvBin* root);
void preOrdem_arvbin(ArvBin* root);
void emOrdem_arvbin(ArvBin* root);
void posOrdem_arvbin(ArvBin* root);
int insere_arvbin(ArvBin* root, int valor);
int remove_arvbin(ArvBin* root, int valor);
struct NO* remove_atual(struct NO* atual);
int busca_arvbin(ArvBin* root, int valor);
void imprime_arvbin(ArvBin* root);

int main(){
    srand(time(NULL));
        
    FILE *fbt_insert, *fbt_search, *fbt_remove;
    fbt_insert = fopen("bt_insert.csv", "w+");
    fprintf(fbt_insert, "Tamanho;Tempo\n");
    fbt_search = fopen("bt_search.csv", "w+");
    fprintf(fbt_search, "Tamanho;Tempo\n");    
    fbt_remove = fopen("bt_remove.csv", "w+");
    fprintf(fbt_remove, "Tamanho;Tempo\n");

    clock_t start, end;
    double time;

    int flag, value, count;
    count = 0;    
    ArvBin* root = cria_arvbin();
    while (count < 10000000){
        value = (rand() % (10000000 * 2 - 0 + 1)) + 0;
        start = clock();
        flag = insere_arvbin(root, value);
        end = clock();
        time = ((double) (end - start)) / CLOCKS_PER_SEC;
        if (flag == 1) {
            count++;
            if (count % 250000 == 0) fprintf(fbt_insert, "%d;%lf\n", count, time);
        }

        if (count > 0 && count % 250000 == 0) {
            value = (rand() % (10000000 * 2 - 0 + 1)) + 0;          
            start = clock();            
            busca_arvbin(root, value);
            end = clock();
            time = ((double) (end - start)) / CLOCKS_PER_SEC;
            fprintf(fbt_search, "%d;%lf\n", count, time);
        }   
    }
    printf("Tamanho: %d\n", count);

    while (count != 5000000) { 
        value = (rand() % (10000000 * 2 - 0 + 1)) + 0;     
        start = clock();
        flag = remove_arvbin(root, value);
        end = clock();
        time = ((double) (end - start)) / CLOCKS_PER_SEC;
        if (flag == 1) {
            count--;
            if (count % 250000 == 0) fprintf(fbt_remove, "%d;%lf\n", totalNO_arvbin(root), time);
        } 
    }
    printf("Tamanho: %d\n", totalNO_arvbin(root));

    fclose(fbt_insert);
    fclose(fbt_search);
    fclose(fbt_remove);
    
    return 0;
}

ArvBin* cria_arvbin(){
    ArvBin* root = (ArvBin*) malloc(sizeof(ArvBin));
    if (root != NULL)
        *root = NULL;
    return root;
}

void libera_arvbin(ArvBin* root){
    if (root == NULL)
        return;
    libera_NO(*root);
    free(root);
}

void libera_NO(struct NO* no){
    if (no == NULL)
        return;
    libera_NO(no->left);
    libera_NO(no->right);
    free(no);
    no = NULL;
}

int vazia_arvbin(ArvBin* root){
    if (root == NULL)
        return 1;
    if (*root == NULL)
        return 1;
    return 0;
}

int altura_arvbin(ArvBin* root){
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;
    int left = altura_arvbin(&((*root))->left);
    int right = altura_arvbin(&((*root))->right);
    if (left > right)
        return (left + 1);
    else
        return (right + 1);
}

int totalNO_arvbin(ArvBin* root){
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;
    int left = totalNO_arvbin(&((*root))->left);
    int right = totalNO_arvbin(&((*root))->right);
    return (left + right + 1);
}

void preOrdem_arvbin(ArvBin* root){
    if (root == NULL) return;
    if (*root != NULL){
        printf("%d ", (*root)->info);
        preOrdem_arvbin(&((*root))->left);
        preOrdem_arvbin(&((*root))->right);
    }
}

void emOrdem_arvbin(ArvBin* root){
    if (root == NULL) return;
    if (*root != NULL){
        emOrdem_arvbin(&((*root))->left);
        printf("%d ", (*root)->info);
        emOrdem_arvbin(&((*root))->right);
    }
}

void posOrdem_arvbin(ArvBin* root){
    if (root == NULL) return;
    if (*root != NULL){
        posOrdem_arvbin(&((*root))->left);
        posOrdem_arvbin(&((*root))->right);
        printf("%d ", (*root)->info);
    }
}

int insere_arvbin(ArvBin* root, int valor){
    if (root == NULL) return 0;
    struct NO* new = (struct NO*) malloc(sizeof(struct NO));
    if (new == NULL) return 0;
    new->info = valor;
    new->left = NULL;
    new->right = NULL;

    if(*root == NULL){
        *root = new;
    } else {
        struct NO* atual = *root;
        struct NO* anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if (valor < atual->info){
                atual = atual->left;
            } else {
                atual = atual->right;
            }
        }
        if (valor < anterior->info){
            anterior->left = new;
        } else {
            anterior->right = new;
        }
    }
    return 1;
}

int remove_arvbin(ArvBin* root, int valor){
    if(root == NULL) return 0;
    struct NO* anterior = NULL;
    struct NO* atual = *root;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *root){
                *root = remove_atual(atual);
            } else {
                if(anterior->left == atual){
                    anterior->left = remove_atual(atual);
                } else {
                    anterior->right = remove_atual(atual);
                }
            }
            return 1;
        }
        anterior = atual;
        if(valor > atual->info){
            atual = atual->right;
        } else {
            atual = atual->left;
        }
    }
}

struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->left == NULL){
        no2 = atual->right;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->left;
    while(no2->right != NULL){
        no1 = no2;
        no2 = no2->right;
    }
    if(no1 != atual){
        no1->right = no2->left;
        no2->left = atual->left;
    }

    no2->right = atual->right;
    free(atual);
    return no2;
}

int busca_arvbin(ArvBin* root, int valor){
    if(root == NULL) return 0;
    struct NO* atual = *root;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info){
            atual = atual->right;
        } else {
            atual = atual->left;
        }
    }
    return 0;
}

void imprime_arvbin(ArvBin* root){
    if(root == NULL) return;
    if(*root != NULL){
        printf("%d ", (*root)->info);
        imprime_arvbin(&((*root))->left);
        imprime_arvbin(&((*root))->right);
    }
}
