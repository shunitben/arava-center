<?php

/**
 * Student's courses report
 */
function arava_courses_students_page() {
  if (!empty($_GET['semester']) && is_numeric($_GET['semester'])) {
    $semesterId = $_GET['semester'];
  }
  else {
    module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
    $mySemesterAPI = new MySemesterAPI();
    $semesterId = $mySemesterAPI->getSemesterId();
  }

  module_load_include('inc', 'arava_center', 'AravaCenterDbApi.class');
  $db_api = new AravaCenterDbApi();
  $courses_students = $db_api->getAllCoursesStudentsForSemester($semesterId);

  // get a list of all students that have at least one course
  $students = array();
  $courses = array('');
  foreach ($courses_students as $course_id => $course) {
    foreach ($course['course_students'] as $uid => $name) {
      $students[$uid] = array('name' => $name);
    }
  }
  uasort($students, '_arava_admin_sort_by_name');
  // now fill out the course data
  foreach ($courses_students as $course_id => $course) {
    $courses[] = $course['course_name'];
    foreach ($course['course_students'] as $uid => $name) {
      $students[$uid][$course_id] = '1';
    }
    foreach ($students as $uid => $data) {
      if (!isset($students[$uid][$course_id])) {
        $students[$uid][$course_id] = '';
      }
    }
  }

  $form_object = drupal_get_form('arava_admin_semesters_dropdown_form');
  $form = drupal_render($form_object);

  return $form . theme('table', array(
    'header' => $courses,
    'rows' => $students,
  ));
}

function _arava_admin_sort_by_name($a, $b) {
  return strcmp($a['name'], $b['name']);
}