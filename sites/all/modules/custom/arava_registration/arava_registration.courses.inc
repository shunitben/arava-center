<?php

/**
 * Page callback for course
 */
function arava_registration_course($form, &$form_state) {

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
    '#markup' => '<div class="my-timetable-block">' . _arava_registration_generate_all_timetables() . '</div>',
  );

	$form['courses_groups'] = array(
		'#type' => 'horizontal_tabs',
    '#attached' => array('library' => array(array('field_group', 'horizontal-tabs'))), // Converts fieldsets into tabs
	);

  $i = 0;
	foreach ($parts['rows'] as $section) {
    $i++;
    $section_name = $section['above'];
    $form['courses'][$i] = array(
      '#type' => 'fieldset',
      '#collapsible' => false,
      '#group' => 'courses_groups',
      '#title' => $section_name,
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

	$form['below'] = array(
		'#markup' => $parts['below'],
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
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
	$form_state['redirect'] = array('registration/accommodation');
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
    'timetable' => _arava_registration_generate_all_timetables(),
  ));

}