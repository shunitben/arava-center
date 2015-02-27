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
    $query->join('field_data_field_registration_complete', 'complete', 'my_semester.nid = complete.entity_id');
    $query->join('field_data_field_course', 'course', 'my_courses.field_my_courses_value = course.entity_id');
    $query
      ->condition('my_semester.type', 'my_semester')
      ->condition('user.field_user_target_id', $uid)
      ->condition('complete.field_registration_complete_value', "1")
      ->condition('course.field_course_target_id', $course_id)
      ->fields('user', array('field_user_target_id'))
      ->fields('course', array('field_course_target_id'));
    $result = $query->execute()->rowCount();

    return !empty($result);
  }

  public function getAllUsersSignedUpToCourse($course_id, $add_default = false) {
    $query = db_select('node', 'my_semester');
    $query->join('field_data_field_user', 'user', 'my_semester.nid = user.entity_id');
    $query->join('field_data_field_user_name', 'username', 'user.field_user_target_id = username.entity_id');
    $query->join('field_data_field_my_courses', 'my_courses', 'my_semester.nid = my_courses.entity_id');
    $query->join('field_data_field_registration_complete', 'complete', 'my_semester.nid = complete.entity_id');
    $query->join('field_data_field_course', 'course', 'my_courses.field_my_courses_value = course.entity_id');
    $query
      ->condition('my_semester.type', 'my_semester')
      ->condition('complete.field_registration_complete_value', "1")
      ->condition('course.field_course_target_id', $course_id)
      ->fields('username', array('entity_id', 'field_user_name_value'))
      ->orderBy('field_user_name_value');
    $results = $query->execute();

    $users = array(0 => t('Please choose'));
    foreach ($results as $row) {
      $users[$row->entity_id] = $row->field_user_name_value;
    }

    return $users;
  }


  public function hasStudentAttendedClass($student, $course, $lesson) {
    $query = db_select('attendance')
      ->condition('student_uid', $student)
      ->condition('course_nid', $course)
      ->condition('lesson_num', $lesson)
      ->fields('attendance', array('attendance_status'))
      ->execute()
      ->fetchAssoc();
    if (!empty($query['attendance_status']) && (int)$query['attendance_status']) {
      return true;
    }
    return false;

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

  public function hasSemesterStartedYet($semester_id) {
    $semester = node_load($semester_id);
    $dates = $semester->field_semester_dates;
    $start_date = $dates[LANGUAGE_NONE][0]['value'];
    return $start_date < time();
  }

}