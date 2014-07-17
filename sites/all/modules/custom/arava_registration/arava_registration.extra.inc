<?php

/**
 * Page callback for extra
 */
function arava_registration_extra($form, &$form_state) {

  // get the already selected extra information, if exist
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $selected = $mySemesterAPI->getExtraInfoForUser();

  // build the form

  $form['#tree'] = true;

  $form['comments'] = array(
    '#type' => 'textarea',
    '#title' => t('Comments'),
    '#default_value' => $selected['comments'],
  );

  $form['takanon_moa'] = array(
    '#type' => 'textfield',
    '#title' => t('I have read and agree to') . ' ' . l(t('Moa\'s terms'), variable_get('arava_center_takanon_moa_link'), array('attributes' => array('target' => '_blank'))),
    '#description' => t('Please write your first name in hebrew if you agree'),
    '#element_validate' => array('_arava_registration_agreed_validate'),
  );

  $form['takanon_school'] = array(
    '#type' => 'textfield',
    '#title' => t('I have read and agree to') . ' ' . l(t('the school\'s terms'), variable_get('arava_center_takanon_school_link'), array('attributes' => array('target' => '_blank'))),
    '#description' => t('Please write your first name in hebrew if you agree'),
    '#element_validate' => array('_arava_registration_agreed_validate'),
  );

  $form['takanon_amuta'] = array(
    '#type' => 'textfield',
    '#title' => t('I have read and agree to') . ' ' . l(t('the amuta\'s terms'), variable_get('arava_center_takanon_amuta_link'), array('attributes' => array('target' => '_blank'))),
    '#description' => t('Please write your first name in hebrew if you agree'),
    '#element_validate' => array('_arava_registration_agreed_validate'),
  );

  $form['health_declaration'] = array(
    '#type' => 'textfield',
    '#title' => t('I have read and agree to') . ' ' . l(t('health declaration'), variable_get('arava_center_health_declaration_link'), array('attributes' => array('target' => '_blank'))),
    '#description' => t('Please write your first name in hebrew if you agree'),
    '#element_validate' => array('_arava_registration_agreed_validate'),
  );

  $form['waver'] = array(
    '#type' => 'textfield',
    '#title' => t('I have read and agree to') . ' ' . l(t('the waver'), variable_get('arava_center_waver_link'), array('attributes' => array('target' => '_blank'))),
    '#description' => t('Please write your first name in hebrew if you agree'),
    '#element_validate' => array('_arava_registration_agreed_validate'),
  );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;

}

function _arava_registration_agreed_validate($element, &$form_state, $form) {
  $error = _arava_registration_agreed($element['#value']);
  if ($error !== false) {
    form_error($element, $error);
  }
}

function _arava_registration_agreed($value) {
  global $user;
  $user = user_load($user->uid);
  $name = $user->field_user_name[LANGUAGE_NONE][0]['value'];

  if (empty($value)) {
    return t('You must agree to the terms.');
  }
  else if (strpos($name, $value) === false || strlen($value) < 2) {
   return t('Please write the first name you signed up. Reminder: you signed up with the name @name', array('@name' => $name));
  }
  // all is good
  return false;
}

/**
 * Extra submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_extra_submit($form, &$form_state) {

  $extra = array(
    'comments' => $form_state['values']['comments'],
    'takanon_moa' => _arava_registration_agreed($form_state['values']['takanon_moa']) === false ? '1' : '0',
    'takanon_school' => _arava_registration_agreed($form_state['values']['takanon_school']) === false ? '1' : '0',
    'takanon_amuta' => _arava_registration_agreed($form_state['values']['takanon_amuta']) === false ? '1' : '0',
    'health_declaration' => _arava_registration_agreed($form_state['values']['health_declaration']) === false ? '1' : '0',
    'waver' => _arava_registration_agreed($form_state['values']['waver']) === false ? '1' : '0',
  );

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setExtraInfo($extra);

	$form_state['redirect'] = array('registration/payment');
}
