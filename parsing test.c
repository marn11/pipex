#include <stdio.h>
int main(int argc, char *argv[], char **envp)
{
	char *cmd_path;
	char *opt[3] = {"ls", "-la", NULL};
	char *cmd = "ls";
	(void)argc;
	(void)argv;
	cmd_path = get_cmd_path(cmd,envp);
	
	if (!cmd_path)
{
    perror("Error finding command path");
    return -1;
}
	execve(cmd_path,opt, envp);// process finishes here so printf won't execute
	printf("Victory");
	free(cmd_path);
}
