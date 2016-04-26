#include "test.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct test {
  int passed;
  int total;
};


TestSuite tst_create (void) {
  TestSuite ret = malloc(sizeof(struct test));
  if (ret == NULL) {
    fprintf(stderr,"tst_create: malloc error");
    exit(1);
  }

  ret->passed = 0;
  ret->total  = 0;

  return ret;
}


void tst_free (TestSuite tst) {
  free(tst);
}


void test(TestSuite tst, const char * msg, bool condition) {
  assert(tst);

  const char * result_txt = "Fail";
  if (condition) {
    result_txt = "OK";
    tst->passed += 1;
  }
  printf("%s: %s\n", msg, result_txt);
  tst->total += 1;
}


int tst_results(TestSuite tst) {
  assert(tst);

  printf("---\nTests passed: %d/%d\n", tst->passed, tst->total);

  return (tst->total - tst->passed);
}
