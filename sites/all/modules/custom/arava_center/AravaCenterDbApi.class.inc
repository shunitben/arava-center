<?php

/**
 * Class AravaCenterDbApi
 *
 * All kinds of functions that query the database and return the results
 */
class AravaCenterDbApi {

  public function isUserSignedUpToCourse($uid, $course_id) {
    $query = db_select('node', 'my_semester');
    $query->join('field_data_field_user', 'user', 'my_semester.nid = user.entity_id');
    $query->join('field_data_field_my_courses', 'my_courses', 'my_semester.nid = my_courses.entity_id');
    $query->join('field_data_field_course', 'course', 'my_courses.field_my_courses_value = course.entity_id');
    $query
      ->condition('my_semester.type', 'my_semester')
      ->condition('user.field_user_target_id', $uid)
      ->condition('course.field_course_target_id', $course_id)
      ->fields('user', array('field_user_target_id'))
      ->fields('course', array('field_course_target_id'));
    $result = $query->execute()->rowCount();

    return !empty($result);
  }

  public function getAllSemesters() {
    $result = db_select('node')
      ->condition('node.type', 'semester')
      ->fields('node', array('nid', 'title'))
      ->execute();

    $semesters = array();
    foreach ($result as $row) {
      $semesters[$row->nid] = $row->title;
    }
    return $semesters;
  }

}