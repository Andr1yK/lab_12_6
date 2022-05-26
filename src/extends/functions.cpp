#pragma once

#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

struct queue
{
  string str;
  long priority;
  struct queue *parent;
  struct queue *child;
};

struct queue *root;
struct queue **pri;

static void add_string(string str, int priority)
{
  struct queue *n = root;
  struct queue *prev = NULL;
  struct queue *temp = NULL;
  struct queue *temp1 = NULL;

  int prr = priority + 20;

  while ((n = pri[prr]) == NULL)
  {
    prr++;
    if (prr >= 20)
      break;
  }

  if (n == NULL)
    n = root;

  while (1)
  {
    if (n == NULL)
    {
      n = (struct queue *)calloc(1, sizeof(struct queue *));
      n->str = str;
      n->priority = priority;
      if (prev)
      {
        prev->child = n;
        n->parent = prev;
      }
      pri[priority + 20] = n;
      if (root == NULL)
        root = n;
      return;
    }
    while (n->priority < priority)
    {
      temp = n;
      prev = n;
      n = n->parent;
      if (n == NULL)
      {
        n = (struct queue *)calloc(1, sizeof(struct queue));
        n->str = str;
        n->priority = priority;
        n->child = temp;
        temp->parent = n;
        root = n;
        pri[priority + 20] = n;
        return;
      }
    }
    while (n->priority > priority)
    {
      temp = n;
      prev = n;
      n = n->child;
      if (n == NULL)
      {
        n = (struct queue *)calloc(1, sizeof(struct queue));
        n->str = str;
        n->priority = priority;
        n->parent = temp;
        temp->child = n;
        pri[priority + 20] = n;
        return;
      }
      else if (n->priority <= priority)
      {
        temp = n->parent;
        temp1 = n;
        n = (struct queue *)calloc(1, sizeof(struct queue));
        n->str = str;
        n->priority = priority;
        n->parent = temp;
        n->child = temp1;
        temp->child = n;
        temp1->parent = n;
        pri[priority + 20] = n;
        return;
      }
    }
    while (n->priority == priority)
    {
      temp = n;
      prev = n;
      n = n->child;
      if (n == NULL)
      {
        n = (struct queue *)calloc(1, sizeof(struct queue));
        n->str = str;
        n->priority = priority;
        n->child = NULL;
        n->parent = n;
        temp->child = n;
        pri[priority + 20] = n;
        return;
      }
      else if (n->priority != priority)
      {
        temp = n->parent;
        temp1 = n;
        n = (struct queue *)calloc(1, sizeof(struct queue));
        n->str = str;
        n->priority = priority;
        n->parent = temp;
        n->child = temp1;
        pri[priority + 20] = n;
        return;
      }
    }
  }
}

void getDataFromFile(const char *fname)
{
  ifstream f(fname);
  string str;

  int spacePos;

  while (getline(f, str))
  {
    spacePos = str.find(" ", 0);

    add_string(
      str.substr(0, spacePos),
      stoi(str.substr(spacePos + 1, str.size() - spacePos - 1))
    );
  }

  f.close();
}

static string get_string_from_queue()
{
  if (!root)
    return "";
  struct queue *n = root;
  root = root->child;
  string str = n->str;
  free(n);
  return str;
}

void Print()
{
  string str;

  while ((str = get_string_from_queue()) != "")
  {
    cout << str << "\t";
  }
  cout << endl;
}

#endif // !_FUNCTIONS_
