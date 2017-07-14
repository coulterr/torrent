int main (int argc, char **argv)
{
	const int BLOCK_SIZE = 16000; 

	const char *source_path = argv[1]; 
	const char *dest_path = argv[2]; 

	int source = open(source_path, O_RDONOLY); 
	int dest = open(dest_path, O_WRONLY); 
	
	char buff[BLOCK_SIZE]; 
	while(read(source, buff, BLOCK_SIZE, 0)) 
	{

	}

	 
	
}
