#include "../include/scene.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_scene_init_free) {
  Scene s;
  scene_init(&s, 10, 20);
  ck_assert_int_eq(s.cap_p, 10);
  ck_assert_int_eq(s.cap_l, 20);
  ck_assert_int_eq(s.num_p, 0);
  ck_assert_int_eq(s.num_l, 0);
  ck_assert_int_eq(s.num_free_ids_p, 10);
  ck_assert_int_eq(s.num_free_ids_l, 20);
  scene_free(&s, 0);
}

START_TEST(test_scene_add_prim) {
  Primitive p;
  prim_load(&p, "models/cube.obj");
  Scene s;
  scene_init(&s, 10, 20);
  int id = scene_add_prim(&s, &p);
  ck_assert_int_eq(s.num_p, 1);
  ck_assert_int_eq(s.num_free_ids_p, 9);
  ck_assert_int_eq(id, 9);
  scene_free(&s, 0);
  prim_free(&p);
}

START_TEST(test_scene_free_prim) {
  Primitive p;
  prim_load(&p, "models/cube.obj");
  Scene s;
  scene_init(&s, 10, 20);
  scene_add_prim(&s, &p);
  scene_free(&s, 1);
}

START_TEST(test_scene_remove_prim) {
  Primitive p;
  prim_load(&p, "models/cube.obj");
  Scene s;
  scene_init(&s, 10, 20);
  int id = scene_add_prim(&s, &p);
  scene_remove_prim(&s, id, 0);
  ck_assert_int_eq(s.num_p, 0);
  ck_assert_int_eq(s.num_free_ids_p, 10);
  scene_free(&s, 0);
  prim_free(&p);
}

START_TEST(test_scene_remove_free_prim) {
  Primitive p;
  prim_load(&p, "models/cube.obj");
  Scene s;
  scene_init(&s, 10, 20);
  int id = scene_add_prim(&s, &p);
  scene_remove_prim(&s, id, 1);
  ck_assert_int_eq(s.num_p, 0);
  ck_assert_int_eq(s.num_free_ids_p, 10);
  scene_free(&s, 0);
}

START_TEST(test_scene_add_dirlight) {
  DirLight l = dirlight_new(1.0f, 1.0f, 1.0f);
  Scene s;
  scene_init(&s, 10, 10);
  int id = scene_add_light(&s, l);
  ck_assert_int_eq(s.num_l, 1);
  ck_assert_int_eq(s.num_free_ids_l, 9);
  ck_assert_int_eq(id, 9);
  scene_free(&s, 0);
}

START_TEST(test_scene_remove_dirlight) {
  DirLight l = dirlight_new(1.0f, 1.0f, 1.0f);
  Scene s;
  scene_init(&s, 10, 10);
  scene_add_light(&s, l);
  scene_remove_light(&s, 9);
  ck_assert_int_eq(s.num_l, 0);
  ck_assert_int_eq(s.num_free_ids_l, 10);
  scene_free(&s, 0);
}

Suite *scene_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("scene");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_scene_init_free);
  tcase_add_test(tc_core, test_scene_add_prim);
  tcase_add_test(tc_core, test_scene_free_prim);
  tcase_add_test(tc_core, test_scene_remove_prim);
  tcase_add_test(tc_core, test_scene_remove_free_prim);
  tcase_add_test(tc_core, test_scene_add_dirlight);
  tcase_add_test(tc_core, test_scene_remove_dirlight);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = scene_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}