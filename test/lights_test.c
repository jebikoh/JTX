#include "../include/lights.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_dirlight_init) {
  DirLight l;
  dirlight_init(&l, 1.0f, 1.0f, 1.0f);
  ck_assert_float_eq(l.dir.x, 0.57735026f);
  ck_assert_float_eq(l.dir.y, 0.57735026f);
  ck_assert_float_eq(l.dir.z, 0.57735026f);
}

START_TEST(test_dirlight_init_vec3) {
  DirLight l;
  Vec3 dir = vec3_new(1.0f, 1.0f, 1.0f);
  dirlight_init_vec3(&l, dir);
  ck_assert_float_eq(l.dir.x, 0.57735026f);
  ck_assert_float_eq(l.dir.y, 0.57735026f);
  ck_assert_float_eq(l.dir.z, 0.57735026f);
}

START_TEST(test_dirlight_new) {
  DirLight l = dirlight_new(1.0f, 1.0f, 1.0f);
  ck_assert_float_eq(l.dir.x, 0.57735026f);
  ck_assert_float_eq(l.dir.y, 0.57735026f);
  ck_assert_float_eq(l.dir.z, 0.57735026f);
}

START_TEST(test_dirlight_new_vec3) {
  Vec3 dir = vec3_new(1.0f, 1.0f, 1.0f);
  DirLight l = dirlight_new_vec3(dir);
  ck_assert_float_eq(l.dir.x, 0.57735026f);
  ck_assert_float_eq(l.dir.y, 0.57735026f);
  ck_assert_float_eq(l.dir.z, 0.57735026f);
}

START_TEST(test_dirlight_intensity) {
  DirLight l = dirlight_new(1.0f, 1.0f, 1.0f);
  ck_assert_float_eq(dirlight_intensity(&l, -1.0f, -1.0f, -1.0f),
                     1.7320508075688776f);
}

START_TEST(test_dirlight_intensity_vec3) {
  Vec3 n = vec3_new(-1.0f, -1.0f, -1.0f);
  DirLight l = dirlight_new(1.0f, 1.0f, 1.0f);
  ck_assert_float_eq(dirlight_intensity_vec3(&l, n), 1.7320508075688776f);
}

Suite *lights_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("lights");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_dirlight_init);
  tcase_add_test(tc_core, test_dirlight_init_vec3);
  tcase_add_test(tc_core, test_dirlight_new);
  tcase_add_test(tc_core, test_dirlight_new_vec3);
  tcase_add_test(tc_core, test_dirlight_intensity);
  tcase_add_test(tc_core, test_dirlight_intensity_vec3);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = lights_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}