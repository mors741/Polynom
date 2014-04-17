/* 
 * File:   poly.cpp
 * Author: evgeny
 *
 * Created on April 17, 2014, 7:44 PM
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct item
{
    int num;
    int power;
    item *next;
};
struct item *get_elem(int num, int power)
{
    struct item *temp;
    temp = (item*)malloc(sizeof(item));
    if (temp != 0)
    {
        temp->num = num;
        temp->power = power;
        temp->next = NULL;
        return temp;
    }
    else
        return NULL;
}
void add_elem(struct item **head, int n, int num, int power)
{
    if (*head == NULL)
        *head = get_elem(num, power);
    else
    {
        if (n != 0)
        {
            if (n == 1)
            {
                struct item *p = *head;
                *head = get_elem(num, power);
                (*head)->next = p;
            }
            else
            {
                struct item *prev = *head;
                int count = 1;
                while (count < n - 1 && prev->next != NULL) 
                {
                    prev = prev->next;
                    count++;
                }
                struct item *p = prev->next;
                prev->next = get_elem(num, power);
                prev->next->next = p;
            }
        }
        else
        {
            struct item *elem = *head;
            while (elem->next != NULL)
                elem = elem->next;
            elem->next = get_elem(num, power);
        }
    }
}
void get_size(struct item *head)
{
    int counter = 0;
    struct item *elem = head;
    while (elem != NULL)
    {
        counter++;
        elem = elem->next;
    }
    printf("Number of elements: %i\n", counter);
}
struct item *find_power(struct item *head, int power1)
{
    struct item *elem = head;
    if (elem == NULL)
        return NULL;
    else
    {
        while (elem != NULL)
        {
            if (power1 == elem->power)
                return elem;
            elem = elem->next;
        }
        return NULL;
    }
}
struct item *find_prev(struct item *head, struct item *elem)
{
    if (head == elem)
        return NULL;
    else
    {
        item *elem1 = head;
        while (elem1->next != elem)
            elem1 = elem1->next;
        return elem1;
    }
}
void delete_head(struct item **head)
{
    struct item *pointer = (*head)->next;
    free(*head);
    *head = pointer;
}
void delete_elem(struct item **head, item *elem)
{
    if (elem == *head)
        delete_head(head);
    else
    {
        struct item *p = find_prev(*head, elem);
        p->next = elem->next;
        free(elem);
    }

}
void print_list(struct item *head)
{
    struct item *point = head;
    while (point != NULL)
    {
        printf("  %i\n%ix\n    + \n", point->power, point->num);
        point = point->next;
    }
    printf("\n---------------------------------------\n");
}
void read_elems(struct item **head)
{
    int n;
    int p;
    printf("Num: ");
    scanf("%i", &n);
    printf("Power: ");
    scanf("%i", &p);
    while (n != 0)
    {
        add_elem(head, 0, n, p);
        printf("\nNum: ");
        scanf("%i", &n);
        printf("Power: ");
        scanf("%i", &p);
    }
}
void format(struct item *head)
{
    struct item *elem1 = head;
    struct item *elem2 = head->next;
    while (elem1 != NULL && elem1->next != NULL)
    {
        elem2 = elem1->next;
        while (elem2 != NULL)
        {
            if (elem1->power == elem2->power)
            {
                elem1->num = elem1->num + elem2->num;
                struct item *prev = find_prev(head, elem2);
                delete_elem(&head, elem2);
                elem2 = prev->next;
            }
            else
                elem2 = elem2->next;
        }
        elem1 = elem1->next;
    }
}
void znach(struct item *head)
{
    int x;
    printf("x: ");
    scanf("%i", &x);
    struct item *elem = head;
    int q;
    int sum = 0;
    while (elem != NULL)
    {
        q = 1;
        for (int i = 0; i < (elem->power); i++)
            q = q*x;
        sum = sum + (elem->num)*q;
        elem = elem->next;
    }
    printf("%i\n", sum);
}
int main()
{
    struct item *head = NULL;
    read_elems(&head);
    print_list(head);
    format(head);
    print_list(head);
    znach(head);
    return 0;
}

