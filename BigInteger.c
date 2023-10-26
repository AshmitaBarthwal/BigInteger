#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
  int data;
  struct node *next;
};

struct BigInteger
{
  int length;
  struct node *nextnode;
};

struct node *createNode (int data)
{
  struct node *newnode = (struct node *) malloc (sizeof (struct node));
  if (newnode)
    {
      newnode->data = data;
      newnode->next = NULL;
    }
  return newnode;
}

struct BigInteger initialize (char *str)
{
  struct BigInteger value;
  value.length = 0;
  value.nextnode = NULL;
  int len = strlen (str);
  int i = 0;
  for (i=0; i < len; i++)
    {
      if (str[i] < '0' || str[i] > '9')
	{
	  printf ("Invalid .\n");
	  exit (1);
	}
      int digit = str[i] - '0';
      struct node *newnode = createNode (digit);
      if (!newnode)
	{
	  printf ("Memory allocation failed.\n");
	  exit (1);
	}
      newnode->next = value.nextnode;
      value.nextnode = newnode;
      value.length++;
    }
  if (value.length == 0)
    {
      value.length = 1;
      value.nextnode = createNode (0);
    }

  return value;
}

//add two BigIntegers
struct BigInteger add (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger result;
  result.length = 0;
  result.nextnode = NULL;

  int carry = 0, sum = 0;
  struct node *itr1 = a.nextnode;
  struct node *itr2 = b.nextnode;
  while (itr1 || itr2 || carry)
    {
      sum = carry;
      if (itr1)
	{
	  sum += itr1->data;
	  itr1 = itr1->next;
	}
      if (itr2)
	{
	  sum += itr2->data;
	  itr2 = itr2->next;
	}
      carry = sum / 10;
      struct node *newnode = createNode (sum % 10);
      if (result.nextnode == NULL)
	{
	  result.nextnode = newnode;
	}
      else
	{
	  struct node *temp = result.nextnode;
	  while (temp->next)
	    {
	      temp = temp->next;
	    }
	  temp->next = newnode;
	}

      result.length++;
    }
  return result;
}

struct BigInteger sub (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger result;
  result.length = 0;
  result.nextnode = NULL;

  int borrow = 0, difference = 0;
  struct node *itr1 = a.nextnode;
  struct node *itr2 = b.nextnode;
  while (itr1 || itr2)
    {
      difference = borrow;

      if (itr1)
	{
	  difference += itr1->data;
	  itr1 = itr1->next;
	}
      if (itr2)
	{
	  difference -= itr2->data;
	  itr2 = itr2->next;
	}
      if (difference < 0)
	{
	  difference += 10;
	  borrow = -1;
	}
      else
	borrow = 0;

      struct node *newnode = createNode (difference);
      if (result.nextnode == NULL)
	{
	  result.nextnode = newnode;
	}
      else
	{
	  struct node *temp = result.nextnode;
	  while (temp->next)
	    {
	      temp = temp->next;
	    }
	  temp->next = newnode;
	}

      result.length++;
    }
  struct node *temp = result.nextnode;
  struct node *last = NULL;
  while (temp)
    {
      if (temp->data != 0)
	{
	  last = temp;
	}
      temp = temp->next;
    }

  if (last)
    {
      last->next = NULL;
    }
  else
    {
      result.nextnode = createNode (0);
    }
  return result;
}

struct BigInteger mul (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger result;
  result.length = 1;
  result.nextnode = createNode (0);

  struct node *itr2 = b.nextnode;
  int position = 0;	

  while (itr2)
    {
      int value = itr2->data;
      struct BigInteger prod;
      prod.length = 0;
      prod.nextnode = NULL;
      struct node *itr1 = a.nextnode;
      int carry = 0;

      while (itr1)
	{
	  int total = (itr1->data * value) + carry;
	  carry = total / 10;
	  struct node *newnode = createNode (total % 10);

	  if (prod.nextnode == NULL)
	    {
	      prod.nextnode = newnode;
	    }
	  else
	    {
	      struct node *temp = prod.nextnode;
	      while (temp->next)
		{
		  temp = temp->next;
		}
	      temp->next = newnode;
	    }

	  itr1 = itr1->next;
	}

      if (carry > 0)
	{
	  struct node *newnode = createNode (carry);
	  if (prod.nextnode == NULL)
	    {
	      prod.nextnode = newnode;
	    }
	  else
	    {
	      struct node *temp = prod.nextnode;
	      while (temp->next)
		{
		  temp = temp->next;
		}
	      temp->next = newnode;
	    }
	}
      for (int i = 0; i < position; i++)
	{
	  struct node *zero = createNode (0);
	  zero->next = prod.nextnode;
	  prod.nextnode = zero;
	}

      // Add the prod to the result
      result = add (result, prod);

      itr2 = itr2->next;
      position++;
    }

  return result;
}

struct node* reverseList(struct node* head) {
    struct node* prev = NULL;
    struct node* temp = head;
    struct node* next = NULL;
    while (temp != NULL) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    return prev; 
}

struct node* copyList(struct node* head) {
    struct node* newHead = NULL;
    struct node* temp = head;
    struct node* tail = NULL;

    while (temp != NULL) {
        struct node* newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data = temp->data;
        newnode->next = NULL;

        if (tail == NULL) {
            newHead = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }

        temp = temp->next;
    }

    return newHead;
}

int compare(struct BigInteger num1, struct BigInteger num2) 
{
    struct node* itr1 = num1.nextnode;
    struct node* itr2 = num2.nextnode;
    int len1 = 0;
    int len2 = 0;

    while (itr1 != NULL)
    {
        len1++;
        itr1 = itr1->next;
    }

    while (itr2 != NULL) 
    {
        len2++;
        itr2 = itr2->next;
    }

    if (len1 < len2) 
        return -1;
    else if (len1 > len2) 
        return 1;
    else 
    {
        struct node* rev1 = copyList(num1.nextnode);
        itr1 = reverseList(rev1);;
        
        struct node* rev2 = copyList(num2.nextnode);
        itr2 = reverseList(rev2); 
        while (itr1 != NULL) {
            if (itr1->data < itr2->data) 
            {
                free(rev1);  
                free(rev2); 
                return -1;
            } 
            else if (itr1->data > itr2->data) 
            {
                free(rev1);  
                free(rev2); 
                return 1;
            }
            itr1 = itr1->next;
            itr2 = itr2->next;
        }
        free(rev1);
        free(rev2);
        return 0; 
    }
}

// Function to divide two BigIntegers(returning quotient)
struct BigInteger div1(struct BigInteger dividend, struct BigInteger divisor) 
{
  struct BigInteger quotient;
  quotient.length = 1;
  quotient.nextnode = createNode(0);

  struct BigInteger first;
  first.length = 1;
  first.nextnode = createNode(1);

  struct BigInteger zero;
  zero.length = 1;
  zero.nextnode = createNode(0);

  if (compare(divisor, zero) == 0) {
    printf("Error.\n");
    exit(1);
  }

  if (compare(dividend, zero) == 0) {
    return zero;
  }

  struct BigInteger rem = dividend;

  while (compare(rem, divisor) >= 0) 
  {
    rem = sub(rem, divisor);
    quotient = add(quotient, first);
  }

  return quotient;
}

// divide two BigIntegers (returning rem)
struct BigInteger mod (struct BigInteger D, struct BigInteger divisor)
{
  struct BigInteger zero;
  zero.length = 1;
  zero.nextnode = createNode (0);

  if (compare (divisor, zero) == 0)
    {
      printf ("Error: Division by zero.\n");
      exit (1);
    }

  struct BigInteger rem = D;

  while (compare (rem, divisor)>=0)
      rem = sub (rem, divisor);

  return rem;
}

void Reverse (struct node *temp)
{
  if (temp == NULL)
    {
      return;
    }
  Reverse (temp->next);
  printf ("%d", temp->data);
}

// Function to display a BigInteger in reverse order
void display (struct BigInteger num)
{
  if (num.length == 0)
    {
      printf ("0\n");
      return;
    }

  Reverse (num.nextnode);	
  printf ("\n");
}



