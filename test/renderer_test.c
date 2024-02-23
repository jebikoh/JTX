#include "../include/renderer.h"

#include <check.h>
#include <stdlib.h>

// START_TEST(test_renderer_init) {
//   Renderer r;
//   int w = 100;
//   int h = 50;
//   Camera c =
// }

// START_TEST(test_renderer_init_extfb) {

// }

Suite *renderer_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("renderer");

  tc_core = tcase_create("Core");

  // tcase_add_test(tc_core, test_dirlight_init);
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