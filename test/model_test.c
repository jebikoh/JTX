#include "../include/model.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_init_model) {
  Model m;
  model_init(&m, 10, 20);
  ck_assert_int_eq(m.num_v, 10);
  ck_assert_int_eq(m.num_f, 20);
  model_free(&m);
}

START_TEST(test_load_model) {
  Model m;
  model_load(&m, "models/cube.obj");
  // Check num vertices and faces
  ck_assert_int_eq(m.num_v, 8);
  ck_assert_int_eq(m.num_f, 12);
  // Check first vertex
  ck_assert_float_eq(m.v[0].x, 1.0f);
  ck_assert_float_eq(m.v[0].y, -1.0f);
  ck_assert_float_eq(m.v[0].z, -1.0f);
  // Check last vertex
  ck_assert_float_eq(m.v[7].x, -1.0f);
  ck_assert_float_eq(m.v[7].y, 1.0f);
  ck_assert_float_eq(m.v[7].z, -1.0f);
  // Check first face
  ck_assert_int_eq(m.f[0].v1, 1);
  ck_assert_int_eq(m.f[0].v2, 2);
  ck_assert_int_eq(m.f[0].v3, 3);
  // Check last face
  ck_assert_int_eq(m.f[11].v1, 4);
  ck_assert_int_eq(m.f[11].v2, 0);
  ck_assert_int_eq(m.f[11].v3, 7);
  model_free(&m);
}

Suite *model_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("model");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_init_model);
  tcase_add_test(tc_core, test_load_model);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = model_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}