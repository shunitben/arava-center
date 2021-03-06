<?php

/**
 * Page callback for accommodation
 */
function arava_registration_accommodation($form, &$form_state) {

  if (!arava_registration_access()) {
    $form['denied'] = array(
      '#markup' => _arava_registration_step_denied_text()
    );
    return $form;
  }

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
    '#title' => t('Accommodation type'),
    '#title_display' => 'invisible',
    '#options' => $options,
    '#default_value' => $selected['accomodation'],
    '#required' => true,
  );

  $form['roommates'] = array(
    '#type' => 'textfield',
    '#title' => t('Is there anyone you would like to share the room with?'),
    '#default_value' => $selected['roommates'],
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
  $roommates = $form_state['values']['roommates'];

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the users requested accomodation
  $mySemesterAPI->selectAccomodation(array('accomodation' => $accomodation, 'roommates' => $roommates));

	$form_state['redirect'] = array('registration/presence');
}