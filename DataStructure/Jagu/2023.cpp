#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int check_matching(const char* in) {


	for (int i = 0; i < strlen(in); i++) {
		if (in[i] == '{' || in[i] == '(' || in[i] == '[') {
			push(in[i]);
		}
		else if (in[i] == '}') {
			char a = pop();
			if (a != '{') return 0;
		}
		else if (in[i] == ']') {
			char a = pop();
			if (a != ']') return 0;
		}
		else if (in[i] == ')') {
			char a = pop();
			if (a != ')') return 0;
		}
	}
	if (is_empty) return 1;
	else return 0;	
}

int main() {

	char eq[30];
	scanf("%s", &eq);
	if (check_matching(eq) == 1)
		printf("success\n");
	else printf("fail");
	return 0;
}