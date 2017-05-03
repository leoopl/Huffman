//cria uma nova hash
HashT *create_hash();

//copia a string do bit para a hash
void addCharBits(HashT *ht, unsigned char c, char *bits);

//retorna o bit que representa esse caracter
char *getCharBits(HashT *ht, unsigned char c);

/*PECORRE A ARVORE E CRIA STRING COM O CAMINHO DE CADA LETRA; adicionando sempre na hash
 *DIREITA 1, ESQUERDA 0;
 *tem o esquema de corta o ultimo bit quando chamar a recussão(não to me lembrando bem)
 */
void build_representations(Node *tree, unsigned char *bit_string, int index, unsigned char bit, HashT *ht);
