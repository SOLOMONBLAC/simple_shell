#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
char **env = info->env;
while (*env != NULL)
{
_puts(*env);
_putchar('\n');
env++;
}
return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
char **env = info->env;
size_t name_len = _strlen(name);

while (*env != NULL)
{
if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
return (*env + name_len + 1);

env++;
}

return (NULL);
}
