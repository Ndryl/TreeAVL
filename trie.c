#include "trie.h"

TrieAvlNode *createAvlNode() {
    TrieAvlNode *newAvlNode = malloc(sizeof(*newAvlNode));
    for (int i = 0; i < NUM_CHARS; i++) {
        newAvlNode->children[i] = NULL;
    }
    

    newAvlNode->terminal = false;
    return newAvlNode;
}
void normalizar_string(const char* origem, char* destino) {
    const char* acentuados = "áàâãäéèêëíìîïóòôõöúùûüçÁÀÂÃÄÉÈÊËÍÌÎÏÓÒÔÕÖÚÙÛÜÇ";
    const char* nao_acentuados = "AAAAAEEEEIIIIOOOOOUUUUCAAAAAEEEEIIIIOOOOOUUUUC";

    int i, j;
    for (i = 0, j = 0; origem[i] != '\0'; i++) {
        char c = origem[i];
        const char* p = strchr(acentuados, c);
        if (p) {
            destino[j++] = toupper(nao_acentuados[p - acentuados]);
        } else {
            destino[j++] = toupper(c);
        }
    }
    destino[j] = '\0';  // Termina a string
}

bool trieinsert(TrieAvlNode **raiz, char *palavra) {
    if (*raiz == NULL) {
        *raiz = createAvlNode();  
    }

    char normalizada[100];  // Buffer para armazenar a palavra normalizada
    normalizar_string(palavra, normalizada);  // Normalizar a palavra (caps e sem acento)

    unsigned char *text = (unsigned char *)normalizada;  
    TrieAvlNode *atual = *raiz;                    
    int comprimento = strlen(normalizada);

    for (int i = 0; i < comprimento; i++) {
        int index = text[i] - 'A';  // Índice baseado em letras maiúsculas (A-Z)

        if (index < 0 || index >= NUM_CHARS) {
            printf("Palavra contém caracteres inválidos: %s\n", normalizada);
            return false; 
        }

        if (atual->children[index] == NULL) {
            atual->children[index] = createAvlNode();
        }

        atual = atual->children[index];
    }

    if (atual->terminal) {
        return false;  // Palavra já estava no trie
    } else {
        atual->terminal = true;  // Marca a palavra como terminal
        return true;
    }
}


bool trieSearch(TrieAvlNode *raiz, const char *palavra) {
    if (raiz == NULL) {
        return false;
    }

    TrieAvlNode *atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int index = palavra[i] - 'a';

        if (index < 0 || index >= NUM_CHARS || atual->children[index] == NULL) {
            return false;
        }

        atual = atual->children[index];
    }

    return atual->terminal;
}

//função de auxilio para printar a trie
void printTrie(TrieAvlNode *raiz, char *prefix, int comprimento) {
    if (raiz == NULL) return;  

    char newprefix[comprimento + 2];    
    memcpy(newprefix, prefix, comprimento); 
    newprefix[comprimento] = '\0';  

    if (raiz->terminal) {
        printf("%s\n", newprefix); 
    }

   
    for (int i = 0; i < NUM_CHARS; i++) {
        if (raiz->children[i] != NULL) {
         
            newprefix[comprimento] = 'A' + i;
            printTrie(raiz->children[i], newprefix, comprimento + 1); 
        }
    }
}

void liberarTrie(TrieAvlNode *raiz) {
    if (raiz == NULL) return;

    for (int i = 0; i < NUM_CHARS; i++) {
        liberarTrie(raiz->children[i]);
    }
    free(raiz);
}

TrieAvlNode* buscarNo(TrieAvlNode *raiz, const char *palavra) {
    if (raiz == NULL) {
        return NULL;
    }

    TrieAvlNode *atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int index = toupper(palavra[i]) - 'A';
        if (index < 0 || index >= NUM_CHARS || atual->children[index] == NULL) {
            return NULL;
        }
        atual = atual->children[index];
    }
    return atual;
}
