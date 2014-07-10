<?php

/**
 * Page callback for accommodation
 */
function arava_registration_accommodation($form, &$form_state) {
  $parts = _arava_registration_get_separated_view('accomodation_selection', 'block_1');

  // get the already selected accomodation, if exists
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $selected = $mySemesterAPI->getAccomodationForUser();

  // build the form

  $form['#tree'] = true;

  $form['above'] = array(
    '#markup' => $parts['above'],
  );

  $options = array();
  foreach ($parts['rows'] as $row) {
    preg_match('/nid:[0-9]+/', $row, $matches);
    $nid = str_replace('nid:', '', $matches[0]);
    $options[$nid] = $row;
  }

  $form['accomodations'] = array(
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => $selected,
  );

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
 * Accommodation selection validation function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_accommodation_validate($form, &$form_state) {
  // @todo: validate that there are free beds of this kind
}

/**
 * Accommodation selection submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_accommodation_submit($form, &$form_state) {

  // get the information from the form
  $accomodation = $form_state['values']['accomodations'];

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // get the courses this user is already signed up for
  $mySemesterAPI->selectAccomodation($accomodation);

	$form_state['redirect'] = array('meals');
}