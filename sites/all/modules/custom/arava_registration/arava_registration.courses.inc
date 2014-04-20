<?php

/**
 * Page callback for course-selection
 */
function arava_registration_course_selection($form, &$form_state) {

	// get the view and separate its html into "above", "rows" and "below"
	$view = _arava_registration_generate_view('course_selection', 'block_1');
	$view_parts = explode('<!--rows start-->', $view);
	$above = $view_parts[0];
	$view_parts = explode('<!--rows end-->', $view_parts[1]);
	$below = $view_parts[1];
	$rows = explode('<!--new row-->', $view_parts[0]);
	unset($rows[0]);

	// get the courses that are already selected
	module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
	$mySemesterAPI = new MySemesterAPI();
	$selected = $mySemesterAPI->getAllCoursesForUser();

	// build the form

	$form['#tree'] = true;

	$form['above'] = array(
		'#markup' => $above,
	);

	$form['courses'] = array(
		'#type' => 'fieldset',
		'#collapsible' => false,
	);
	foreach ($rows as $row) {
		preg_match('/nid:[0-9]+/', $row, $matches);
		$nid = str_replace('nid:', '', $matches[0]);
		$form['courses'][$nid] = array(
			'#type' => 'fieldset',
			'#collapsible' => false,
			'checkbox' => array(
				'#type' => 'checkbox',
				'#default_value' => in_array($nid, $selected) ? 1 : 0,
			),
			'info' => array(
				'#markup' => $row,
			)
		);
	}

	$form['below'] = array(
		'#markup' => $below,
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);

	return $form;
}

/**
 * Course selection validation function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_course_selection_validate($form, &$form_state) {
	// @todo: validate that hours don't collide

	// @todo: validate that user hasn't unchecked courses they've already paid for
}

/**
 * Course selection submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_course_selection_submit($form, &$form_state) {

	// get the information from the form
	$selected = array();
	foreach ($form_state['values']['courses'] as $course_id => $course) {
		if ($course['checkbox'] == 1) {
			$selected[] = $course_id;
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
	$form_state['redirect'] = array('accommodation-selection');
}