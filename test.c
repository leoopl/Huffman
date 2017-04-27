void freq_count(FILE* file, int *freq_count)
{
	file = fopen(file, "rb");
	unsigned int c;
	while(c = gets(file) !=EOF)
		freq_count[c]++;
	fclose(file);
}

int size_huff(Node *huff)
{
	if(is_empty(huff))
		return 0;
	else
		return 1 + size_huff(huff->left) + size_huff(huff->right);
}

fseek(saida,0,SEEK_SET);
trash = trash | tree_size >> 8;
fprintf(saida, "%c", trash);
trash = tree_size  & 256;
fprintf(saida, "%c", trash);