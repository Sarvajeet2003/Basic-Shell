#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <signal.h>
#include <fcntl.h>
#include "echo.c"

char cur_path[256];
char *history[10001];
int count = 0;

void change_dir(char *);

void INTHandler(int);

void handle_pipe(char * [][101], int , int);

int main() {
	int f=1;
	signal(SIGINT, INTHandler);
	while (f) {
		printf("Sarva's Shell> ");
		char s[10001];
		fgets(s, sizeof(s), stdin);
		
		if ((strcmp(s,"\r") == 0) || (strcmp(s, "\n") == 0)) {
			continue;
		}
		
		if (s[strlen(s) - 1] == '\n') {
			s[strlen(s) - 1] = '\0';
		}
		history[count=count+1] = strdup(s);
		
		char *var[101][101];
		char *token, *end_str;
		char dem[101] = " ";
		token = strtok_r(s, "|", &end_str);
		int row = 0, col = 0, max_col = -1;
		while (token != NULL) {
			char *end_token;
			char *sub_token = strtok_r(token, dem, &end_token);
			while (sub_token != NULL) {
				if (sub_token[strlen(sub_token)-1] == '\\') {
					char *tokenapp = strtok_r(NULL, dem, &end_token);
					if (tokenapp != NULL) {
						sub_token[strlen(sub_token)-1] = '\0';
						strcat(sub_token, " ");
						strcat(sub_token, tokenapp);
					}
				}
				int j=0;
				int flag = 0;
				for (j=0; j<strlen(sub_token); j=j+1) {
					char *end_sub_token;
					char *sub_token2 = NULL;
					if (sub_token[j] == '>') {
						sub_token2 = strtok_r(sub_token, ">", &end_sub_token);
						if (sub_token2 != NULL)
							var[row][col=col+1] = sub_token2;
						var[row][col=col+1] = ">";
						sub_token2 = strtok_r(NULL, ">", &end_sub_token);
						if (sub_token2 != NULL)
							var[row][col=col+1] = sub_token2;
						flag = 1;
					}
					else if (sub_token[j] == '<') {
						sub_token2 = strtok_r(sub_token, "<", &end_sub_token);
						if (sub_token2 != NULL){
							var[row][col=col+1] = sub_token2;
						}
						var[row][col++] = "<";
						sub_token2 = strtok_r(NULL, "<", &end_sub_token);
						if (sub_token2 != NULL){
							var[row][col=col+1] = sub_token2;
						}
						flag = 1;
					}
					if (flag != 0){
						break;
					}
					else{
						continue;
					}
				}
				if (flag != 1){
					var[row][col++] = sub_token;
				}
				sub_token = strtok_r(NULL, dem, &end_token);
			}
			var[row][col] = NULL;
			if (col > max_col){
				max_col = col;
			}

			col = 0;
			row=row+1;
			token = strtok_r(NULL, "|", &end_str);
		}
		*var[row] = NULL;

		if (strcmp(var[0][0], "exit") == 0) {
			exit(0);
		}
		if (strcmp(var[0][0], "cd") == 0) {
			change_dir(var[0][1]);
		}
		else {
			handle_pipe(var, row, col);
		}
	}
	return 0;
}

void change_dir(char *pth) {
	int ret;
	if (pth[0] == '.') {
		getcwd(cur_path, sizeof(cur_path));
		strcat(cur_path,"/");
		strcat(cur_path,pth);
		ret = chdir(cur_path);	
	}
	else if (pth[0] == '~') {
		pth=pth+1;
		char *cur_path = getenv("HOME");
		strcat(cur_path, pth);
		ret = chdir(cur_path);
	}
	else {
		ret = chdir(pth);
	}
	if (ret == -1) {
		printf("Invalid Path\n");
	}
	else {
		char present[10001];
		getcwd(present, sizeof(present));
		printf("%s\n", present);
	}
}



void INTHandler(int sig) {
	signal(sig, SIG_IGN);
	signal(SIGINT, INTHandler);
}



void handle_pipe(char *var[][101], int row, int col) {
	int fd[2], i = 0, pid, temp = 0;

	while (var[i][0] != NULL) {
		pipe(fd);
		pid = fork();

		if (pid == 0) {	
			dup2(temp, 0);
			if (var[i+1][0] != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);	

			int j=0;
			while (var[i][j] != NULL) {
				if (strcmp(var[i][j],">") == 0) {
					int fd = creat(var[i][j+1], 0644);
					dup2(fd, 1);
					close (fd);
					var[i][j] = NULL;
					var[i][j+1] = NULL;
					break;
				}
				else if (strcmp(var[i][j],"<") == 0) {
					int fd = open(var[i][j+1], O_RDONLY, 0);
					dup2(fd, 0);
					close(fd);
					var[i][j] = NULL;
					var[i][j+1] = NULL;
					break;
				}
				j=j+1;
			}

			if (execvp(var[i][0], var[i]) == -1){
				printf("Please do enter Valid Commands\n");
			}
			exit(0);
		}
		else {	
			wait(NULL);
			close(fd[1]);	
			i=i+1;
			temp = fd[0];
		}
	}
}