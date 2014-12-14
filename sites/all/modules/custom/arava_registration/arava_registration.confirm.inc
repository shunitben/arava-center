<?php
/**
 * Page callback for confirmation
 */
function arava_registration_confirmation($form, &$form_state) {

  if (!arava_registration_access()) {
    $form['denied'] = array(
      '#markup' => _arava_registration_step_denied_text()
    );
    return $form;
  }

  $validate = _arava_registration_validate_all_registration();
  if (!empty($validate)) {
    $form['denied'] = array(
      '#markup' => t('Please finish the registration process before confirming:') . '<br>' . implode('<br>', $validate) . '<br>',
    );
    return $form;
  }

  // build the form

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm Registration'),
  );

  return $form;

}

/**
 * confirmation submit function
 *
 * @param $form
 * @param $form_state
 */
function arava_registration_confirmation_submit($form, &$form_state) {

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();

  // save the information
  $mySemesterAPI->setComplete();

  $form_state['redirect'] = array('registration/thanks-confirmed');
}


