<?php

/**
 * Page callback for meals
 */
function arava_registration_meals($form, &$form_state) {

  if (!arava_registration_access()) {
    $form['denied'] = array(
      '#markup' => t('You have already completed your registration. You may only change the courses you signed up to.<br>Please contact the site administrators to make any changes.')
    );
    return $form;
  }

  // get the already selected meals information, if exist
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $selected = $mySemesterAPI->getMealsInfoForUser();

  // build the form

  $form['#tree'] = true;

  $form['food'] = array(
    '#type' => 'fieldset',
    '#collapsible' => false,
  );

  $form['food']['i_eat_dairy'] = array(
    '#type' => 'checkbox',
    '#title' => t('I eat dairy.'),
    '#default_value' => $selected['i_eat_dairy'],
  );

  $form['food']['i_eat_eggs'] = array(
    '#type' => 'checkbox',
    '#title' => t('I eat eggs.'),
    '#default_value' => $selected['i_eat_eggs'],
  );

  $form['food']['allergies'] = array(
    '#type' => 'fieldset',
    '#collapsible' => false,
  );
  $form['food']['allergies']['explanation'] = array(
    '#markup' => '<div><b>' . t('Allergies: ') . '</b>' . t('Are you allergic to any foods? Please mark what\'s relevant.<br> (Please note, this isn\'t about naturopathic
    or ayurvedic preferences, but about allergies.)') . '</div>',
  );
  $form['food']['allergies']['gluten'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am allergic to gluten.'),
    '#default_value' => $selected['gluten'],
  );
  $form['food']['allergies']['soy'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am allergic to soy.'),
    '#default_value' => $selected['soy'],
  );
  $form['food']['allergies']['dairy'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am allergic to dairy.'),
    '#default_value' => $selected['dairy'],
  );
  $form['food']['allergies']['peanuts'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am allergic to peanuts.'),
    '#default_value' => $selected['peanuts'],
  );
  $form['food']['allergies']['other'] = array(
    '#type' => 'textfield',
    '#title' => t('Other allergies:'),
    '#default_value' => $selected['other_allergies'],
  );



  $form['guests'] = array(
    '#type' => 'fieldset',
    '#collapsible' => false,
    '#title' => t('Guests')
  );
  $form['guests']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('The number of guests I am expecting to join me for meals:'),
    '#size' => 5,
    '#default_value' => $selected['extra_guests'],
  );
  $form['guests']['days'] = array(
    '#type' => 'checkboxes',
    '#title' => t('I expect my guests to be present for meals on these days:'),
    '#options' => _arava_registration_days_of_week_options(),
    '#default_value' => $selected['extra_days_present'],
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;

}

/**
 * Meals selection submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_meals_submit($form, &$form_state) {

  // get the information from the form
  $food = $form_state['values']['food'];
  $guests = $form_state['values']['guests'];

  // process the information a bit
  $allergies = $food['allergies'];
  $other_allergies = array_pop($allergies);

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setMealsFoodInfo($allergies, $other_allergies, $food['i_eat_dairy'], $food['i_eat_eggs']);
  $mySemesterAPI->setMealsPresenceInfo($guests['number'], $guests['days']);

	$form_state['redirect'] = array('registration/extra');
}