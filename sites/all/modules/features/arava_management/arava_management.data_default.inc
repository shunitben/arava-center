<?php
/**
 * @file
 * arava_management.data_default.inc
 */

/**
 * Implements hook_data_default().
 */
function arava_management_data_default() {
  $export = array();

  $data_table = new stdClass();
  $data_table->disabled = FALSE; /* Edit this to true to make a default data_table disabled initially */
  $data_table->api_version = 1;
  $data_table->title = 'Attendance';
  $data_table->name = 'attendance';
  $data_table->table_schema = array(
    'description' => '',
    'fields' => array(
      'attendance_id' => array(
        'type' => 'serial',
        'size' => 'normal',
        'not null' => TRUE,
        'description' => '',
      ),
      'student_uid' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => FALSE,
        'description' => '',
      ),
      'course_nid' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => FALSE,
        'description' => '',
      ),
      'lesson_num' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => FALSE,
        'description' => '',
      ),
      'attendance_taker_uid' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => FALSE,
        'description' => '',
      ),
      'attendance_status' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => FALSE,
        'description' => '',
      ),
      'updated_date' => array(
        'type' => 'int',
        'size' => 'normal',
        'not null' => FALSE,
        'description' => '',
      ),
    ),
    'name' => 'attendance',
    'indexes' => array(
      'attendance_manager_uid' => array(
        0 => 'attendance_taker_uid',
      ),
      'course_nid' => array(
        0 => 'course_nid',
      ),
      'student_uid' => array(
        0 => 'student_uid',
      ),
    ),
    'primary key' => array(
      0 => 'attendance_id',
    ),
  );
  $data_table->meta = array(
    'fields' => array(
      'attendance_id' => array(),
      'student_uid' => array(),
      'course_nid' => array(),
      'lesson_num' => array(),
      'attendance_taker_uid' => array(),
      'attendance_status' => array(),
      'updated_date' => array(),
    ),
  );
  $export['attendance'] = $data_table;

  return $export;
}
