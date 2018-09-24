#ifndef __VALUE_H__
#define __VALUE_H__

typedef struct VALUE value;

extern value *newValue(void *, int, void (*)(FILE *, void *));
extern void *getValue(value *);
extern int getValueType(value *);
extern void displayValue(FILE *, value *);

#endif
