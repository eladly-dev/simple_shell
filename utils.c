#include "shell.h"

/**
 * _getenv - gets the environment variable's value
 * @var: the required variable
 *
 * Return: a pointer to the @var's value, NULL on failure.
 **/
char *_getenv(char *var)
{
	char *piece, *current;
	int i;

	if (!*var)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		current = environ[i];
		piece = strtok(environ[i], "=");
		printf("piece: %s, environ[%d]: %s\n", piece, i, current);
		if (piece == var)
			break;
	}

	return (environ[i]);
}

/**
 * link_path - builds a linked list of the PATH directories.
 *
 * Return: a pointer to the head of the linked list, NULL on failure.
 **/
node_t *link_path(void)
{
	char *path, *piece, *pathdup;
	node_t *head = NULL;

	path = getenv("PATH");
	if (!path)
		return (NULL);

	pathdup = _strdup(path);
	if (!pathdup)
		return (NULL);

	piece = strtok(pathdup, ":");
	while (piece != NULL)
	{
		if (new_node(&head, piece) == NULL)
			return (NULL);
		piece = strtok(NULL, ":");
	}

	return (head);
}

/**
 * new_node - adds a new node to the end of a linked list
 * @head: the head of the linked list.
 * @value: the value
 *
 * Return: pointer to the new_node, NULL on failure
 **/
node_t *new_node(node_t **head, char *value)
{
	node_t *new_node, *start = *head;

	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);
	new_node->value = value;

	if (start == NULL)
	{
		new_node->next = start;
		*head = new_node;
		return (*head);
	}
	else
	{
		node_t *tmp = start;

		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}

	return (new_node);
}