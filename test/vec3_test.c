#include <check.h>

#include "../include/util.h"

START_TEST(test_init_vec3) {
  Vec3 v;
  init_vec3(&v, 1, 2, 3);
  ck_assert(v.x == 1);
  ck_assert(v.y == 2);
  ck_assert(v.z == 3);
}

Suite *vec3_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Vec3");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_init_vec3);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = vec3_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}