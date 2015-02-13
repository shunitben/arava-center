<?php

/**
 * Page callback for extra
 */
function arava_registration_extra($form, &$form_state) {

  if (!arava_registration_access()) {
    $form['denied'] = array(
      '#markup' => _arava_registration_step_denied_text()
    );
    return $form;
  }

  // get the already selected extra information, if exist
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $selected = $mySemesterAPI->getExtraInfoForUser();

  // build the form

  $form['#tree'] = true;

  $form['takanon_moa_checkbox'] = _agreement_field_checkbox("Moa's terms", 'arava_center_takanon_moa_link', 'moa', $selected['takanon_moa']);
  $form['takanon_moa'] = _agreement_field_textfield('moa');

  $form['takanon_school_checkbox'] = _agreement_field_checkbox("the school's terms", 'arava_center_takanon_school_link', 'school', $selected['takanon_school']);
  $form['takanon_school'] = _agreement_field_textfield('school');


//  $form['takanon_amuta_checkbox'] = _agreement_field_checkbox("the amuta's terms", 'arava_center_takanon_amuta_link', 'amuta', $selected['takanon_amuta']);
//  $form['takanon_amuta'] = _agreement_field_textfield('amuta');

  $form['health_declaration_checkbox'] = _agreement_field_checkbox("health declaration", 'arava_center_health_declaration_link', 'health', $selected['health_declaration']);
  $form['health_declaration'] = _agreement_field_textfield('health');

  $form['waver_checkbox'] = _agreement_field_checkbox("the waver", 'arava_center_waver_link', 'waver', $selected['waver']);
  $form['waver'] = _agreement_field_textfield('waver');

  $form['comments'] = array(
    '#type' => 'textarea',
    '#title' => t('Comments / Remarks / Extra requests'),
    '#description' => t('You can write any kind of feedback here.'),
    '#default_value' => $selected['comments'],
  );

  $form['no_printed_materials'] = array(
    '#type' => 'checkbox',
    '#title' => t('I do NOT wish to receive printed materials (homework, reading materials, etc.)'),
    '#default_value' => $selected['no_printed_materials'],
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
  );

  return $form;

}

function _agreement_field_checkbox($title, $link_variable, $id, $default) {
  return array(
    '#type' => 'checkbox',
    '#title' => t('I have read and agree to') . ' ' . l(t($title), variable_get($link_variable), array('attributes' => array('class' => array('dialog-link')))),
    '#description' => t('Please click the link to read and sign your name.'),
//    '#element_validate' => array('_arava_registration_agreed_validate'),
    '#default_value' => $default,
    '#disabled' => $default,
    '#prefix' => '<div class="checkbox-field-wrapper" takanon-id="' . $id . '">',
    '#suffix' => '</div>',
  );
}

function _agreement_field_textfield($id) {
  return array(
    '#type' => 'textfield',
    '#title' => '',
    '#description' => t('Please write your first name in hebrew if you agree'),
//    '#element_validate' => array('_arava_registration_agreed_validate'),
    '#prefix' => '<div class="takanon hidden" takanon-id="' . $id . '"><div class="takanon-text"></div><div class="text-field-wrapper">',
    '#suffix' => '</div></div>',
    '#field_suffix' => '<span class="agree">' . t('I agree') . '</span>',
  );
}

//function _arava_registration_agreed_validate($element, &$form_state, $form) {
//  $error = _arava_registration_agreed($element['#value']);
//  if ($error !== false) {
//    form_error($element, $error);
//  }
//}

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

function arava_registration_extra_validate($form, &$form_state) {
  // validate all takanons were signed
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $valid = $mySemesterAPI->validateExtraInfoForUser();
  if (!$valid) {
    form_set_error('submit', t('Please sign all the agreements.'));
  }
}

/**
 * Extra submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_extra_submit($form, &$form_state) {

//  $extra = array(
//    'comments' => $form_state['values']['comments'],
//    'takanon_moa' => _arava_registration_agreed($form_state['values']['takanon_moa']) === false ? '1' : '0',
//    'takanon_school' => _arava_registration_agreed($form_state['values']['takanon_school']) === false ? '1' : '0',
//    'takanon_amuta' => _arava_registration_agreed($form_state['values']['takanon_amuta']) === false ? '1' : '0',
//    'health_declaration' => _arava_registration_agreed($form_state['values']['health_declaration']) === false ? '1' : '0',
//    'waver' => _arava_registration_agreed($form_state['values']['waver']) === false ? '1' : '0',
//  );

  $comments = $form_state['values']['comments'];
  $no_printed_materials = $form_state['values']['no_printed_materials'];

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setComment($comments);
  $mySemesterAPI->setNoPrintedMaterials($no_printed_materials);

	$form_state['redirect'] = array('registration/confirm');
}

function arava_registration_save_agreement() {
  $name = $_POST['name'];
  $to_what = $_POST['takanon'];
  $error_name = _arava_registration_agreed($name);
  if (!$error_name) {
    $to_what = 'field_' . str_replace('-', '_', $to_what);
    module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
    $mySemesterAPI = new MySemesterAPI();
    $mySemesterAPI->setAgreement($to_what);
    print json_encode(array(
      'success' => true,
    ));
  }
  else {
    print json_encode(array(
      'success' => false,
      'error' => $error_name,
    ));
  }
}

function arava_registration_close_dialog() {
  return '<div class="close_dialog">' . t('Closing window...') . '</div>';
}