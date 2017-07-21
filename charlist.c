typedef struct {
	size_t size; 
	size_t capacity;
	char *data; 
}Charlist; 

int Charlist_init(Charlist *charlist)
{
	charlist->data = malloc(sizeof(char) 1024); 
	charlist->size = 0; 
	charlist->capacity = 1024; 
}
int Charlist_add(Charlist *charlist, char *item, size_t len)
{
	while (charlist->size + len >= charlist->capacity){
		charlist->capacity = charlist->capacity * 2; 
		charlist->data = realloc(charlist->data, sizeof(char) * charlist->capacity); 
	}
	
	memcpy((void *) (charlist->data) + charlist->size, (void *) item, len);  
	charlist->size = charlist->size + len; 
}
const char *Charlist_tochars(Charlist *charlist)
{
	return (const char *) charlist->data;
}

void Charlist_delete(Charlist *charlist)
{
	free(charlist->data); 
}

