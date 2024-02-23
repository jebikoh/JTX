#include "../include/camera.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_camera_init) {
  Camera c;
  Vec3 pos, target, up;
  vec3_init(&pos, 0.0f, 0.0f, 30.0f);
  vec3_init(&target, 0.0f, 0.0f, 0.0f);
  vec3_init(&up, 0.0f, 1.0f, 0.0f);
  camera_init(&c, pos, target, up, 1.0472f, 0.1f, 100.0f);
  ck_assert_float_eq(c.pos.x, 0.0f);
  ck_assert_float_eq(c.pos.y, 0.0f);
  ck_assert_float_eq(c.pos.z, 30.0f);
  ck_assert_float_eq(c.dir.x, 0.0f);
  ck_assert_float_eq(c.dir.y, 0.0f);
  ck_assert_float_eq(c.dir.z, -1.0f);
  ck_assert_float_eq(c.up.x, 0.0f);
  ck_assert_float_eq(c.up.y, 1.0f);
  ck_assert_float_eq(c.up.z, 0.0f);
  ck_assert_float_eq(c.fov, 1.0472f);
  ck_assert_float_eq(c.near, 0.1f);
  ck_assert_float_eq(c.far, 100.0f);
}

START_TEST(test_camera_new) {
  Vec3 pos, target, up;
  vec3_init(&pos, 0.0f, 0.0f, 30.0f);
  vec3_init(&target, 0.0f, 0.0f, 0.0f);
  vec3_init(&up, 0.0f, 1.0f, 0.0f);
  Camera c = camera_new(pos, target, up, 1.0472f, 0.1f, 100.0f);
  ck_assert_float_eq(c.pos.x, 0.0f);
  ck_assert_float_eq(c.pos.y, 0.0f);
  ck_assert_float_eq(c.pos.z, 30.0f);
  ck_assert_float_eq(c.dir.x, 0.0f);
  ck_assert_float_eq(c.dir.y, 0.0f);
  ck_assert_float_eq(c.dir.z, -1.0f);
  ck_assert_float_eq(c.up.x, 0.0f);
  ck_assert_float_eq(c.up.y, 1.0f);
  ck_assert_float_eq(c.up.z, 0.0f);
  ck_assert_float_eq(c.fov, 1.0472f);
  ck_assert_float_eq(c.near, 0.1f);
  ck_assert_float_eq(c.far, 100.0f);
}

START_TEST(test_get_view_mat) {
  Camera c;
  Vec3 pos, target, up;
  vec3_init(&pos, 0.0f, 0.0f, 30.0f);
  vec3_init(&target, 0.0f, 0.0f, 0.0f);
  vec3_init(&up, 0.0f, 1.0f, 0.0f);
  camera_init(&c, pos, target, up, 1.0472f, 0.1f, 100.0f);

  Mat4 m;
  camera_get_view_mat(&c, &m);
  ck_assert_float_eq(m.m[0][0], 1.0f);
  ck_assert_float_eq(m.m[0][1], 0.0f);
  ck_assert_float_eq(m.m[0][2], 0.0f);
  ck_assert_float_eq(m.m[0][3], 0.0f);
  ck_assert_float_eq(m.m[1][0], 0.0f);
  ck_assert_float_eq(m.m[1][1], 1.0f);
  ck_assert_float_eq(m.m[1][2], 0.0f);
  ck_assert_float_eq(m.m[1][3], 0.0f);
  ck_assert_float_eq(m.m[2][0], 0.0f);
  ck_assert_float_eq(m.m[2][1], 0.0f);
  ck_assert_float_eq(m.m[2][2], 1.0f);
  ck_assert_float_eq(m.m[2][3], -30.0f);
  ck_assert_float_eq(m.m[3][0], 0.0f);
  ck_assert_float_eq(m.m[3][1], 0.0f);
  ck_assert_float_eq(m.m[3][2], 0.0f);
  ck_assert_float_eq(m.m[3][3], 1.0f);
}

START_TEST(test_get_proj_mat) {
  Camera c;
  Vec3 pos, target, up;
  vec3_init(&pos, 0.0f, 0.0f, 30.0f);
  vec3_init(&target, 0.0f, 0.0f, 0.0f);
  vec3_init(&up, 0.0f, 1.0f, 0.0f);
  camera_init(&c, pos, target, up, 1.0472f, 0.1f, 100.0f);
  Mat4 m;
  camera_get_proj_mat(&c, &m, 2.0f, PERSPECTIVE);
  ck_assert_float_eq_tol(m.m[0][0], 0.86602295, 0.0001);
  ck_assert_float_eq_tol(m.m[0][1], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[0][2], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[0][3], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[1][0], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[1][1], 1.73204591, 0.0001);
  ck_assert_float_eq_tol(m.m[1][2], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[1][3], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[2][0], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[2][1], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[2][2], 1.002002, 0.0001);
  ck_assert_float_eq_tol(m.m[2][3], 0.2002002, 0.0001);
  ck_assert_float_eq_tol(m.m[3][0], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[3][1], 0.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[3][2], -1.0f, 0.0001);
  ck_assert_float_eq_tol(m.m[3][3], 0.0f, 0.0001);
}

Suite *camera_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("camera");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_camera_init);
  tcase_add_test(tc_core, test_camera_new);
  tcase_add_test(tc_core, test_get_view_mat);
  tcase_add_test(tc_core, test_get_proj_mat);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = camera_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}