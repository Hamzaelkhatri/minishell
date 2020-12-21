#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct s_list
{
    char *content;
    struct s_list *next;
} t_list;

t_list *creat(char *content)
{
    t_list *lst;
    lst = malloc(sizeof(t_list));
    lst->content = content;
    lst->next = NULL;

    return (lst);
}

void add(t_list **head, t_list *new_obj)
{
    t_list *new;

    if (!head || !new_obj)
        return;
    new = *head;
    if (new)
    {
        while (new->next)
            new = new->next;
        new->next = new_obj;
    }
    else
        *head = new_obj;
}

int main()
{
    t_list *lst;
    t_list *new;

    lst = NULL;
    new = creat("echo  hello | ls; pwd");
    add(&lst, new);
    while (lst != NULL)
    {
        printf("==>%s==>\n", lst->content);
        lst = lst->next;
    }
}