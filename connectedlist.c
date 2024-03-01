#include "main.h"

name_t *addnameend(name_t **head, char *name, char *value);
void freenamelist(name_t *head);
list_t *addnodeend(list_t **head, char *dirctor);
void freelist(list_t *head);

/**
 * addnameend - Adds a node to the end of a name_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new name to be added.
 * @value: The value of the new name to be added.
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
name_t *addnameend(name_t **head, char *name, char *value)
{
	name_t *newnode = malloc(sizeof(name_t));
	name_t *last;

	if (!newnode)
		return (NULL);

	newnode->next = NULL;
	newnode->name = malloc(sizeof(char) * (stringlength(name) + 1));
	if (!newnode->name)
	{
		free(newnode);
		return (NULL);
	}
	newnode->value = value;
	stringcopy(newnode->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = newnode;
	}
	else
		*head = newnode;

	return (newnode);
}

/**
 * addnodeend - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dirctor: The dirctorectory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *addnodeend(list_t **head, char *dirctor)
{
	list_t *newnode = malloc(sizeof(list_t));
	list_t *last;

	if (!newnode)
		return (NULL);

	newnode->dirctor = dirctor;
	newnode->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = newnode;
	}
	else
		*head = newnode;

	return (newnode);
}

/**
 * freenamelist - Frees a name_t linked list.
 * @head: THe head of the name_t list.
 */
void freenamelist(name_t *head)
{
	name_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * freelist - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void freelist(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dirctor);
		free(head);
		head = next;
	}
}

