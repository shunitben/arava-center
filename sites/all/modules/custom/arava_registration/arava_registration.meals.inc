<?php

/**
 * Page callback for meals
 */
function arava_registration_meals($form, &$form_state) {

  if (!arava_registration_access()) {
    $form['denied'] = array(
      '#markup' => _arava_registration_step_denied_text()
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
    '#markup' => '<div><b>' . t('Nutritional Preferences: ') . '</b>' . t('Institutional kitchen cooking holds many challenges . Please indicate your preferences so we can understand <b>the current trend</b> and try to respond to most needs and preferences:') . '</div>',
  );
  $form['food']['allergies']['gluten'] = array(
    '#type' => 'checkbox',
    '#title' => t('I prefer gluten-free food.'),
    '#default_value' => $selected['gluten'],
  );
  $form['food']['allergies']['soy'] = array(
    '#type' => 'checkbox',
    '#title' => t('I prefer soy-free food.'),
    '#default_value' => $selected['soy'],
  );
  $form['food']['allergies']['send_email'] = array(
    '#markup' => '<div>' . t('If you have any allergies, please send an email to foo@bar.com.') . '</div>',
  );

  $form['food']['meals_presence'] = array(
    '#type' => 'checkboxes',
    '#title' => t('I expect to be present and dine at these meals:'),
    '#options' => _arava_registration_meals_options(),
    '#default_value' => $selected['meals_present'],
  );



  $form['guests'] = array(
    '#type' => 'fieldset',
    '#collapsible' => false,
    '#title' => t('Guests'),
    '#description' => t('Please write the number of guests you expect to have for each of these meals:')
  );
  $table_top = '<table><tr><td></td>';
  for ($i=1; $i<=5; $i++) {
    $table_top .= '<td>' . t('Week @num', array('@num' => $i)) . '</td>';
  }
  $table_top .= '</tr>';
  $form['guests']['table_start'] = array(
    '#markup' => $table_top
  );

  foreach (_arava_registration_guest_meals_options() as $meal => $meal_name) {
    $form['guests']['row_'.$meal.'_start'] = array(
      '#markup' => '<tr><td>' . $meal_name . '</td>'
    );
    for ($i=1; $i<=5; $i++) {
      $form['guests'][$meal . '-' . $i] = array(
        '#type' => 'select',
        '#default_value' => $selected['guests_for_meals'][$meal . '-' . $i],
        '#options' => array(
          0 => 0,
          1 => 1,
          2 => 2,
          3 => 3,
          4 => 4,
          5 => 5,
          6 => 6,
          7 => 7,
          8 => 8,
          9 => 9,
          10 => 10,
        ),
        '#prefix' => '<td>',
        '#suffix' => '</td>'
      );
    }
    $form['guests']['row_'.$meal.'_end'] = array(
      '#markup' => '</tr>'
    );
  }

  $form['guests']['table_end'] = array(
    '#markup' => '</table>'
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
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

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setMealsFoodInfo($allergies, $food['i_eat_dairy'], $food['i_eat_eggs']);
  $mySemesterAPI->setMealsPresenceInfo($food['meals_presence'], $guests);

	$form_state['redirect'] = array('registration/extra');
}