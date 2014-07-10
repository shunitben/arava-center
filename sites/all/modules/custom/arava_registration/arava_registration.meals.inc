<?php

/**
 * Page callback for meals
 */
function arava_registration_meals($form, &$form_state) {

  // get the already selected meals information, if exist
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $selected = $mySemesterAPI->getMealsInfoForUser();

  // build the form

  $form['#tree'] = true;

  $form['food'] = array(
    '#type' => 'fieldset',
    '#collapsible' => false,
    '#title' => t('Special food requests')
  );

  $form['food']['allergies'] = array(
    '#type' => 'fieldset',
    '#collapsible' => false,
    '#title' => t('Allergies'),
  );
  $form['food']['allergies']['gluten'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am allergic to gluten.'),
    '#default_value' => $selected['gluten'],
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

  $form['food']['vegan'] = array(
    '#type' => 'checkbox',
    '#title' => t('I would like a vegan diet.'),
    '#default_value' => $selected['vegan'],
  );

  $form['presence'] = array(
    '#type' => 'fieldset',
    '#collapsible' => false,
    '#title' => t('Presence in meals')
  );
  $form['presence']['days'] = array(
    '#type' => 'checkboxes',
    '#title' => t('I expect to be present for meals on these days:'),
    '#description' => t('*At the moment, this does not affect the price of your stay. We just want to know how many people to cook for.'),
    '#options' => _arava_registration_days_of_week_options(),
    '#default_value' => $selected['days_present'],
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
  $presence = $form_state['values']['presence'];
  $guests = $form_state['values']['guests'];

  // process the information a bit
  $allergies = $food['allergies'];
  $other_allergies = array_pop($allergies);

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setMealsFoodInfo($allergies, $other_allergies, $food['vegan']);
  $mySemesterAPI->setMealsPresenceInfo($presence['days'], $guests['number'], $guests['days']);

	$form_state['redirect'] = array('extra');
}