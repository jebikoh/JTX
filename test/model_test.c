#include "../include/model.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_model_init) {
  Model m;
  model_init(&m, 10, 20);
  ck_assert_int_eq(m.num_v, 10);
  ck_assert_int_eq(m.num_f, 20);
  model_free(&m);
}

START_TEST(test_model_get_v) {
  Model m;
  model_init(&m, 2, 0);
  m.v[4] = 1.0f;
  m.v[5] = 2.0f;
  m.v[6] = 3.0f;
  m.v[7] = 4.0f;
  float *v = model_get_v(&m, 1);
  ck_assert_float_eq(v[0], 1.0f);
  ck_assert_float_eq(v[1], 2.0f);
  ck_assert_float_eq(v[2], 3.0f);
  ck_assert_float_eq(v[3], 4.0f);
  model_free(&m);
}

START_TEST(test_model_load) {
  Model m;
  model_load(&m, "models/cube.obj");
  // Check num vertices and faces
  ck_assert_int_eq(m.num_v, 8);
  ck_assert_int_eq(m.num_f, 12);
  // // Check first vertex
  float *v1 = model_get_v(&m, 0);
  ck_assert_float_eq(v1[0], 1.0f);
  ck_assert_float_eq(v1[1], -1.0f);
  ck_assert_float_eq(v1[2], -1.0f);
  // // Check last vertex
  float *v8 = model_get_v(&m, 7);
  ck_assert_float_eq(v8[0], -1.0f);
  ck_assert_float_eq(v8[1], 1.0f);
  ck_assert_float_eq(v8[2], -1.0f);
  // // Check first face
  ck_assert_int_eq(m.f[0].v1, 1);
  ck_assert_int_eq(m.f[0].v2, 2);
  ck_assert_int_eq(m.f[0].v3, 3);
  // // Check last face
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

  tcase_add_test(tc_core, test_model_init);
  tcase_add_test(tc_core, test_model_get_v);
  tcase_add_test(tc_core, test_model_load);
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