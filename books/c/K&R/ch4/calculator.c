#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <string.h>

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define NAME 'n'   /* signal that a mathfunc was found */

int getop(char[]);
void push(double);
double pop(void);
void clrsp(void);
void mathfunc(char[]);

#define MAXRNT 10
double recent[MAXRNT];
int rp = 0;

int main() {
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;

        case NAME:
            mathfunc(s);
            break;

        case '+':
            push(pop() + pop());
            break;

        case '*':
            push(pop() * pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;

        case '?':
            op2 = pop();
            printf("\t%.8g\n", op2);
            push(op2);
            break;

        case 'c':
            clrsp();
            break;

        case 'd':
            op2 = pop();
            push(op2);
            push(op2);
            break;

        case 's':
            op1 = pop();
            op2 = pop();
            push(op2);
            push(op1);
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;

        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("erro:zero divisor\n");
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
    int i = 0, j = 0;
    for (i = 0, j = rp; i < MAXRNT; ++i) {
        printf("%.8g\n", recent[j++ % MAXRNT]);
    }

    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    int tmp = val[--sp];
    if (sp > 0) {
        recent[rp++ % MAXRNT] = tmp;
        return tmp;
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void clrsp(void) { sp = 0; }

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters");
    else
        buf[bufp++] = c;
}

void mathfunc(char s[]) {
    double op2 = 0;
    if (strcasecmp("sin", s) == 0) {
        push(sin(pop()));
    } else if (strcasecmp("cos", s) == 0) {
        push(cos(pop()));
    } else if (strcasecmp("exp", s) == 0) {
        push(exp(pop()));
    } else if (strcasecmp("pow", s) == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    } else {
        printf("error: %s is invalid math method\n", s);
    }
}
