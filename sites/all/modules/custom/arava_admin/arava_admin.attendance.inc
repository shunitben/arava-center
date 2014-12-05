<?php

function arava_admin_attendance_choose_lesson_form($form, &$form_state) {
  $form['#prefix'] ='<div id="form-div">';
  $form['#suffix'] ='</div>';
  $form['#tree'] = true;

  $semester_options = _arava_admin_get_semester_options();
  if (!empty($form_state['values']['semester'])) {
    $default_semester = $form_state['values']['semester'];
  }
  elseif (!empty($_GET['semester'])) {
    $default_semester = $_GET['semester'];
  }
  else {
    $default_semester = _arava_admin_get_default_semester();
  }
  $form['semester'] = array(
    '#title' => t('Semester'),
    '#type' => 'select',
    '#options' => $semester_options,
    '#default_value' => $default_semester,
    '#ajax' => array(
      'callback' => 'attendance_choose_semester',
      'wrapper' => 'form-div',
      'method' => 'replace',
      'effect' => 'none',
    ),
  );

  $course_options = _arava_admin_get_course_options($default_semester);
  $default_course = null;
  if (!empty($form_state['triggering_element']) && $form_state['triggering_element']['#name'] != 'semester' && !empty($form_state['values']['course'])) {
    $default_course = $form_state['values']['course'];
  }
  elseif (!empty($_GET['course'])) {
    $default_course = $_GET['course'];
  }
  $form['course'] = array(
    '#title' => t('Course'),
    '#type' => 'select',
    '#options' => $course_options,
    '#default_value' => $default_course,
    '#prefix' => '<div id="course-div">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'attendance_choose_course',
      'wrapper' => 'form-div',
      'method' => 'replace',
      'effect' => 'none',
    ),
  );

  $lesson_options = _arava_admin_get_lesson_options($default_course);
  $form['lesson'] = array(
    '#title' => t('Lesson'),
    '#type' => 'select',
    '#options' => $lesson_options,
    '#default_value' => !empty($_GET['lesson']) ? $_GET['lesson'] : null,
    '#prefix' => '<div id="lesson-div">',
    '#suffix' => '</div>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'go',
  );

  return $form;
}

function arava_admin_attendance_choose_lesson_form_submit($form, &$form_state) {
  drupal_goto('admin/attendance/take', array('query' => array(
    'semester' => $form_state['values']['semester'],
    'course' => $form_state['values']['course'],
    'lesson' => $form_state['values']['lesson'],
  )));
}

function arava_admin_take_attendance_form($form, &$form_state) {

  $path = drupal_get_path('module', 'arava_admin');
  drupal_add_js($path . '/js/arava_admin.js');
  drupal_add_css($path . '/css/arava_admin.css');

  $course = !empty($_GET['course']) ? $_GET['course'] : null;
  $lesson = !empty($_GET['lesson']) ? $_GET['lesson'] : null;

  if ((!$course || !is_numeric($course)) || (!$lesson || !is_numeric($lesson))) {
    $form['attendance'] = array(
      '#markup' => t('Please choose a course and lesson above.'),
    );
  }
  else {

    $form['course'] = array(
      '#type' => 'value',
      '#value' => $course,
    );
    $form['lesson'] = array(
      '#type' => 'value',
      '#value' => $lesson,
    );


    $form['attendance'] = array(
      '#type' => 'fieldset',
      '#prefix' => '<div class="attendance_warning">' .
        t('You have changed the selection of semesters, courses or lessons above.<br> The attendance form has not yet changed.') . '<br><br>' .
        t('To take attendance for the lesson you have selected above, please click the "go" button above.') . "<br>" .
        t('To continue with the attendance you were taking, <a class="discard_attendance_warning">click here</a>') .
        '</div>'
    );

    $students = _arava_admin_get_attendance_list_for_lesson($course, $lesson);

    $course_node = node_load($course);
    $course_name = $course_node->title;
    $attendance_status = '<h3>' . t('@course lesson @lesson.', array('@course' => $course_name, '@lesson' => $lesson)) . '</h1>';
    if ($students['first_time']) {
      $attendance_status .= t('Attendance has not yet been taken for this lesson. All students have been marked as present for your
                              convenience. Please remove any student that was not present.');
    }
    else {
      $attendance_status .= t('Attendance has already been taken for this lesson. This is real data. Edit away!');
    }

    $form['attendance']['header'] = array(
      '#markup' => '<div class="students-header">
                      <div class="attendance_status">' . $attendance_status . '</div>
                      <div class="titles">
                        <span class="present">' . t('Present') . '</span>
                        <span class="made_up">' . t('Made Up') . '</span>
                      </div>
                    </div>',
    );

    foreach ($students['names'] as $uid => $student) {
      $form['attendance']['student_' . $uid] = array(
        '#type' => 'checkboxes',
        '#title' => $student['name'],
        '#options' => array(
          1 => t('Present'),
          2 => t('Made up'),
        ),
        '#default_value' => array($student['status']),
      );
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );
  }

  return $form;
}

function attendance_choose_semester($form, $form_state) {
  $form_state['rebuild'] = true;
  return $form;
}
function attendance_choose_course($form, $form_state) {
  $form_state['rebuild'] = true;
  return $form;
}
function attendance_choose_lesson($form, $form_state) {
  $form_state['rebuild'] = true;
  return $form;
}

function _arava_admin_get_semester_options() {
  $result = db_select('node', 'node')
    ->condition('type', 'semester')
    ->fields('node', array('nid', 'title'))
    ->execute();

  $semesters = array();
  foreach ($result as $row) {
    $semesters[$row->nid] = $row->title;
  }
  return $semesters;
}

function _arava_admin_get_default_semester() {
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $MySemesterApi = new MySemesterAPI();
  return $MySemesterApi->getCurrentSemester(true);
}

function _arava_admin_get_course_options($semester_id) {
  $query = db_select('node', 'node');
  $query->join('field_data_field_semester', 'semester', 'node.nid = semester.entity_id');
  $query->condition('type', 'course')
    ->condition('field_semester_target_id', $semester_id)
    ->fields('node', array('nid', 'title'))
    ->orderBy('title');
  $result = $query->execute();

  $courses = array(null => '--');
  foreach ($result as $row) {
    $courses[$row->nid] = $row->title;
  }
  return $courses;
}

function _arava_admin_get_lesson_options($course_id) {
  if ($course_id) {
    $result = db_select('field_data_field_num_lessons', 'lessons')
      ->condition('entity_id', $course_id)
      ->fields('lessons', array('field_num_lessons_value'))
      ->execute();

    $num_lessons = 0;
    foreach ($result as $row) {
      $num_lessons = $row->field_num_lessons_value;
    }
  }
  $empty_text = (empty($num_lessons) && $course_id != null) ? t('No lessons defined for this course.') : '--';
  $lessons = array('null' => $empty_text);
  if (!empty($num_lessons)) {
    for ($i = 1; $i <= $num_lessons; $i++) {
      $lessons[$i] = t('lesson') . ' ' . $i;
    }
  }
  return $lessons;
}

/**
 * Get students list for lesson, and populate it with any existing attendance data
 * @param $default_course
 * @param $default_lesson
 */
function _arava_admin_get_attendance_list_for_lesson($course, $lesson) {
  // get attendance for this lesson
  $result = db_select('attendance')
    ->condition('course_nid', $course)
    ->condition('lesson_num', $lesson)
    ->fields('attendance', array('student_uid', 'attendance_status'))
    ->execute();
  $attendance = array();
  foreach ($result as $row) {
    $attendance[$row->student_uid] = $row->attendance_status;
  }
  $select_all = count($attendance) == 0;


  // we already have a view that gets students per course, so let's use that:
  $view = views_get_view('courses_reports');
  $view->set_display('page_2');
  // disable the pager to get all the results
  $pager = $view->display_handler->get_option('pager');
  $pager['type'] = 'none';
  $view->display_handler->set_option('pager', $pager);
  // execute the view
  $view->pre_execute(array($course));
  $view->execute();

  // get the uids and names from the results
  $names = array();
  foreach ($view->result as $result) {
    $uid = $result->users_field_data_field_user_uid;
    $names[$uid] = array(
      'name' => $result->field_field_user_name[0]['rendered']['#markup'],
      'status' => $select_all ? 1 : $attendance[$uid],
    );
  }
  return array(
    'first_time' => $select_all,
    'names' => $names,
  );
}

function arava_admin_take_attendance_form_submit($form, &$form_state) {
  global $user;
  foreach($form_state['values'] as $student => $attendance) {
    $uid = str_replace('student_', '', $student);
    $present = !empty($attendance[1]);
    $made_up = !empty($attendance[2]);
    $status = $present ? 1 : ($made_up ? 2 : 0);

    db_insert('attendance')
      ->fields(array(
        'student_uid' => (int)$uid,
        'course_nid' => (int)$form_state['values']['course'],
        'lesson_num' => (int)$form_state['values']['lesson'],
        'attendance_taker_uid' => $user->uid,
        'attendance_status' => $status,
        'updated_date' => time(),
      ))
      ->execute();
  }

  drupal_set_message('The attendance data you submitted has been saved.');
}