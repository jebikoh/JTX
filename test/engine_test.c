#include "../include/engine.h"

#include <check.h>
#include <stdlib.h>

// Use valgrind for checking memory leaks
START_TEST(test_engine_init) {
  Engine e;
  engine_init(&e, 100, 50, 10, 10, 10);
  ck_assert_int_eq(e.w, 100);
  ck_assert_int_eq(e.h, 50);
  ck_assert_int_eq(e.mlen, 111);
  ck_assert_int_eq(e.m_cap, 10);
  ck_assert_int_eq(e.num_m, 0);
  ck_assert_int_eq(e.dl_cap, 10);
  ck_assert_int_eq(e.num_dl, 0);
  ck_assert_int_eq(e.c_cap, 10);
  ck_assert_int_eq(e.num_c, 0);
  ck_assert_ptr_ne(e.models, NULL);
  ck_assert_ptr_ne(e.dlights, NULL);
  ck_assert_ptr_ne(e.cameras, NULL);
  ck_assert_ptr_ne(e.buf, NULL);
  ck_assert_ptr_ne(e.zbuf, NULL);
  engine_free(&e, 0);
}

// START_TEST(test_engine_free_m) {
//   Model m1, m2;
//   model_load(&m1, "models/cube.obj");
//   model_load(&m1, "models/cube.obj");
//   Engine e;
//   engine_init(&e, 100, 50, 10, 10, 10);
// }

Suite *engine_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("engine");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_engine_init);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = engine_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}