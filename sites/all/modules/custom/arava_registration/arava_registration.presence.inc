<?php

/**
 * Page callback for presence
 */
function arava_registration_presence($form, &$form_state) {

  if (!arava_registration_access()) {
    $form['denied'] = array(
      '#markup' => t('You have already completed your registration. You may only change the courses you signed up to.<br>Please contact the site administrators to make any changes.')
    );
    return $form;
  }

  // get the already selected presence information, if exist
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $selected = $mySemesterAPI->getPresenceInfoForUser();

  // build the form

  $form['#tree'] = true;

  $form['presence'] = array(
    '#type' => 'checkboxes',
    '#title' => t('I expect to be present on these days:'),
    '#description' => t('*At the moment, this does not affect the price of your stay. We just want to know how many people to expect each day.'),
    '#options' => _arava_registration_days_of_week_options(),
    '#default_value' => $selected,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
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

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setPresenceInfo($presence);

	$form_state['redirect'] = array('registration/meals');
}