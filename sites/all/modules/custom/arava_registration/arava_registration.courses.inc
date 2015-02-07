<?php

/**
 * Page callback for course
 */
function arava_registration_course($form, &$form_state) {

  if (!arava_registration_access(true)) {
    $form['denied'] = array(
      '#markup' => _arava_registration_step_denied_text()
    );
    return $form;
  }

  drupal_add_library('system', 'ui.accordion');

  $parts = _arava_registration_get_separated_sectioned_view('course_selection', 'block_1');

  // get the courses that are already selected
	module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
	$mySemesterAPI = new MySemesterAPI();
	$selected = $mySemesterAPI->getAllCoursesForUser();

	// build the form

	$form['#tree'] = true;

	$form['above'] = array(
		'#markup' => $parts['above'],
	);

  $form['timetable'] = array(
    '#markup' => '<div class="my-timetable-block">' . _arava_registration_generate_all_timetables('page_1') . '</div>',
  );

  $form['courses_start'] = array(
    '#markup' => '<div class="all-courses">',
  );

  $i = 0;
	foreach ($parts['rows'] as $section) {
    $i++;
    $section_name = $section['above'];
    $form['courses']['title' . $i] = array(
      '#markup' => '<h3>' . $section_name . '</h3>',
    );
    $form['courses'][$i] = array(
      '#type' => 'fieldset',
      '#collapsible' => false,
    );

    foreach ($section['rows'] as $row) {
      preg_match('/nid:[0-9]+/', $row, $matches);
      $nid = str_replace('nid:', '', $matches[0]);
      $form['courses'][$i][$nid] = array(
        '#type' => 'fieldset',
        '#collapsible' => false,
        '#group' => $i,
        'checkbox' => array(
          '#type' => 'checkbox',
          '#default_value' => in_array($nid, $selected) ? 1 : 0,
        ),
        'info' => array(
          '#markup' => $row,
        )
      );
    }
	}

  $form['courses_end'] = array(
    '#markup' => '</div>',
  );

	$form['below'] = array(
		'#markup' => $parts['below'],
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Continue'),
	);

	return $form;
}

/**
 * Course selection validation function:
 * validate that hours don't collide
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_course_validate($form, &$form_state) {
  // get the information from the form
  $selected = array();
  foreach ($form_state['values']['courses'] as $section) {
    foreach ($section as $course_id => $course) {
      if ($course['checkbox'] == 1) {
        $selected[] = $course_id;
      }
    }
  }


  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $collisions = $mySemesterAPI->coursesCollision($selected);
  if ($collisions) {
    $error = t('You have collisions between the following courses:') . '<br>';
    $error .= implode(', ', $collisions);
    form_set_error('submit', $error);
  }
}

/**
 * Course selection submit function
 *
 * This actually shouldn't do much, since courses are saved in ajax
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_course_submit($form, &$form_state) {

	// get the information from the form
	$selected = array();
  foreach ($form_state['values']['courses'] as $section) {
    foreach ($section as $course_id => $course) {
      if ($course['checkbox'] == 1) {
        $selected[] = $course_id;
      }
    }
  }


	module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
	$mySemesterAPI = new MySemesterAPI();

	// get the courses this user is already signed up for
	$curr_courses = $mySemesterAPI->getAllCoursesForUser();

	// add new ones
	foreach ($selected as $course) {
		if (!in_array($course, $curr_courses)) {
			$mySemesterAPI->addCourse($course);
		}
	}

	// remove any removed ones
	foreach ($curr_courses as $course) {
		if (!in_array($course, $selected)) {
			$mySemesterAPI->removeCourse($course);
		}
	}

	// redirect to next page
	$form_state['redirect'] = arava_registration_access() ? array('registration/accommodation') : array('user');
}

/**
 * @param $course_id
 * @param $action - add | remove
 */
function arava_registration_course_ajax($course_id, $action) {

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // get the courses this user is already signed up for
  $curr_courses = $mySemesterAPI->getAllCoursesForUser();

  if ($action == 'add') {
    if (!in_array($course_id, $curr_courses)) {
      $mySemesterAPI->addCourse($course_id);
    }
  }
  elseif ($action == 'remove') {
    if (in_array($course_id, $curr_courses)) {
      $mySemesterAPI->removeCourse($course_id);
    }
  }

  print json_encode(array(
    'timetable' => _arava_registration_generate_all_timetables('page_1'),
  ));

}