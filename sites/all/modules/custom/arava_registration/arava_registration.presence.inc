<?php

/**
 * Page callback for presence
 */
function arava_registration_presence($form, &$form_state) {

  if (!arava_registration_access()) {
    $form['denied'] = array(
      '#markup' => _arava_registration_step_denied_text()
    );
    return $form;
  }

  // get the already selected presence information, if exist
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $selected = $mySemesterAPI->getPresenceInfoForUser();

  $path = drupal_get_path('theme', 'arava_center');
  drupal_add_js($path . '/js/jquery.timepicker.min.js');
  drupal_add_css($path . '/css/jquery.timepicker.css');

  // build the form

  $form['#tree'] = true;

  $form['presence'] = array(
    '#type' => 'checkboxes',
    '#title' => t('I expect to be present on these days:'),
    '#description' => t('*At the moment, this does not affect the price of your stay. We just want to know how many people to expect each day.'),
    '#options' => _arava_registration_days_of_week_options(),
    '#default_value' => $selected['days'],
    '#required' => true,
  );

  $form['arrival_time'] = array(
    '#type' => 'textfield',
    '#title' => t('I expect to arrive at about: '),
    '#default_value' => $selected['arrival_time'],
    '#required' => true,
  );

  $form['departure_time'] = array(
    '#type' => 'textfield',
    '#title' => t('I expect to leave at about: '),
    '#default_value' => $selected['departure_time'],
    '#required' => true,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
  );

  return $form;

}

/**
 * Presence selection submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_presence_submit($form, &$form_state) {

  // get the information from the form
  $presence = $form_state['values']['presence'];
  $arrival = $form_state['values']['arrival_time'];
  $departure = $form_state['values']['departure_time'];

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setPresenceInfo($presence, $arrival, $departure);

	$form_state['redirect'] = array('registration/meals');
}