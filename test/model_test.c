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

START_TEST(test_model_apply_smat) {
  Model m;
  model_load(&m, "models/cube.obj");
  Mat4 scale;
  build_smat(&scale, 2.0f, 2.0f, 2.0f);
  model_apply_transf(&m, &scale);
  // Check first vertex
  float *v1 = model_get_v(&m, 0);
  ck_assert_float_eq(v1[0], 2.0f);
  ck_assert_float_eq(v1[1], -2.0f);
  ck_assert_float_eq(v1[2], -2.0f);
  // Check last vertex
  float *v8 = model_get_v(&m, 7);
  ck_assert_float_eq(v8[0], -2.0f);
  ck_assert_float_eq(v8[1], 2.0f);
  ck_assert_float_eq(v8[2], -2.0f);
  model_free(&m);
}

START_TEST(test_model_apply_tmat) {
  Model m;
  model_load(&m, "models/cube.obj");
  Mat4 translate;
  build_tmat(&translate, 1.0f, 2.0f, 3.0f);
  model_apply_transf(&m, &translate);
  // Check first vertex
  float *v1 = model_get_v(&m, 0);
  ck_assert_float_eq(v1[0], 2.0f);
  ck_assert_float_eq(v1[1], 1.0f);
  ck_assert_float_eq(v1[2], 2.0f);
  // Check last vertex
  float *v8 = model_get_v(&m, 7);
  ck_assert_float_eq(v8[0], 0.0f);
  ck_assert_float_eq(v8[1], 3.0f);
  ck_assert_float_eq(v8[2], 2.0f);
  model_free(&m);
}

START_TEST(test_model_apply_rmat) {
  Model m;
  model_load(&m, "models/cube.obj");
  Mat4 rotate;
  build_rmat(&rotate, deg_to_rad(90.0f), X);
  model_apply_transf(&m, &rotate);
  // Check first vertex
  float *v1 = model_get_v(&m, 0);
  ck_assert_float_eq_tol(v1[0], 1.0f, 0.0001);
  ck_assert_float_eq_tol(v1[1], 1.0f, 0.0001);
  ck_assert_float_eq_tol(v1[2], -1.0f, 0.0001);
  // Check last vertex
  float *v8 = model_get_v(&m, 7);
  ck_assert_float_eq_tol(v8[0], -1.0f, 0.0001);
  ck_assert_float_eq_tol(v8[1], 1.0f, 0.0001);
  ck_assert_float_eq_tol(v8[2], 1.0f, 0.0001);
  model_free(&m);
}

START_TEST(test_model_apply_cond) {
  Model m;
  model_load(&m, "models/cube.obj");
  Mat4 mats[3];
  build_smat(&mats[0], 2.0f, 2.0f, 2.0f);
  build_tmat(&mats[1], 1.0f, 2.0f, 3.0f);
  build_rmat(&mats[2], deg_to_rad(90.0f), X);
  Mat4 tf;
  cond_mat4(mats, 3, &tf);
  model_apply_transf(&m, &tf);
  // Check first vertex
  float *v1 = model_get_v(&m, 0);
  ck_assert_float_eq_tol(v1[0], 4.0f, 0.0001);
  ck_assert_float_eq_tol(v1[1], 6.0f, 0.0001);
  ck_assert_float_eq_tol(v1[2], 4.0f, 0.0001);
  // Check last vertex
  float *v8 = model_get_v(&m, 7);
  ck_assert_float_eq_tol(v8[0], 0.0f, 0.0001);
  ck_assert_float_eq_tol(v8[1], 6.0f, 0.0001);
  ck_assert_float_eq_tol(v8[2], 8.0f, 0.0001);
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
  tcase_add_test(tc_core, test_model_apply_smat);
  tcase_add_test(tc_core, test_model_apply_tmat);
  tcase_add_test(tc_core, test_model_apply_rmat);
  tcase_add_test(tc_core, test_model_apply_cond);
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