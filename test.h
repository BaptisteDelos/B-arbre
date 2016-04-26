#ifndef _TEST_H
#define _TEST_H

#include <stdbool.h>

typedef struct test * TestSuite;

TestSuite tst_create (void);
void      tst_free (TestSuite tst);

void test(TestSuite tst, const char * msg, bool condition);

/** Affiche le nombre de tests réussis et le nombre total de tests.
 *  @return le nombre de tests ratés. */
int tst_results(TestSuite tst);

#endif //_TEST_H
