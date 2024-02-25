#include "../include/renderer.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_renderer_init) {
  Renderer r;
  int w = 100;
  int h = 50;
  Camera c = camera_new(vec3_new(0.0f, 0.0f, 30.0f), vec3_new(0.0f, 0.0f, 0.0f),
                        vec3_new(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);
  renderer_init(&r, w, h, NULL, c);
  ck_assert_int_eq(r.w, w);
  ck_assert_int_eq(r.h, h);
  ck_assert_float_eq(r.ar, 2.0f);
  ck_assert_int_eq(r.mlen, 111);
  ck_assert_float_eq(r.c.fov, 1.0472f);
  ck_assert_ptr_nonnull(r.zbuf);
  ck_assert_ptr_nonnull(r.fb);
  ck_assert_float_eq(r.zbuf[0], -INFINITY);

  renderer_free(&r, 1);
}

START_TEST(test_renderer_init_extfb) {
  Renderer r;
  int w = 100;
  int h = 50;
  Camera c = camera_new(vec3_new(0.0f, 0.0f, 30.0f), vec3_new(0.0f, 0.0f, 0.0f),
                        vec3_new(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);
  float *fb = calloc(w * h, sizeof(float));
  renderer_init(&r, w, h, &fb, c);
  ck_assert_int_eq(r.w, w);
  ck_assert_int_eq(r.h, h);
  ck_assert_float_eq(r.ar, 2.0f);
  ck_assert_int_eq(r.mlen, 111);
  ck_assert_float_eq(r.c.fov, 1.0472f);
  ck_assert_ptr_nonnull(r.zbuf);
  ck_assert_ptr_nonnull(r.fb);
  ck_assert_float_eq(r.zbuf[0], -INFINITY);
  renderer_free(&r, 1);
}

START_TEST(test_renderer_clear) {
  Renderer r;
  int w = 100;
  int h = 50;
  Camera c = camera_new(vec3_new(0.0f, 0.0f, 30.0f), vec3_new(0.0f, 0.0f, 0.0f),
                        vec3_new(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);
  renderer_init(&r, w, h, NULL, c);
  r.fb[0] = 1.0f;
  r.zbuf[0] = 1.0f;
  renderer_clear(&r);
  ck_assert_float_eq(r.fb[0], 0.0f);
  ck_assert_float_eq(r.zbuf[0], -INFINITY);
  renderer_free(&r, 1);
}

START_TEST(test_leak) { float *fb = calloc(100 * 50, sizeof(float)); }

Suite *renderer_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("renderer");

  tc_core = tcase_create("Core");
  // Disable timeout for valgrind/leaks
  tcase_set_timeout(tc_core, 0);

  tcase_add_test(tc_core, test_renderer_init);
  tcase_add_test(tc_core, test_renderer_init_extfb);
  tcase_add_test(tc_core, test_renderer_clear);
  tcase_add_test(tc_core, test_leak);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = renderer_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}