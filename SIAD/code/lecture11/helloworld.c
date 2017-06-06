//Logan Holbrook

#include <stdio.h>

int main(int argc, char *argv[]){
	char *data = getenv("QUERY_STRING");
	char *username[100];
	char *password[100];

	printf("Content-Type: text/plain; charset=utf-8\n\n");
	printf("Hello World: %s\n", data);
	sscanf(data, "username=%[^&]&password=%s", username, password);

	return 0;
}
