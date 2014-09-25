<?php

/**
 * Configuration forms
 */
function arava_registration_config() {
  return theme('links', array('links' => array(

    'general' => array(
      'title' => t('General Settings'),
      'href' => 'admin/arava-center/general',
    ),

    'takanon' => array(
      'title' => t('Takanon Links'),
      'href' => 'admin/arava-center/takanon-links',
    ),

    'emails' => array(
      'title' => t('Emails'),
      'href' => 'admin/arava-center/emails',
    ),

    'texts' => array(
      'title' => t('Texts'),
      'href' => 'admin/arava-center/texts',
    ),

  )));
}

function arava_registration_general_settings($form, &$form_state) {
  $form['arava_center_pay_for_accomodation_on_registration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pay for accomodation when registering'),
    '#default_value' => variable_get('arava_center_pay_for_accomodation_on_registration', ''),
  );

  $form['arava_center_num_allowed_payments'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of allowed payments (tranzilla)'),
    '#default_value' => variable_get('arava_center_num_allowed_payments', ''),
    '#size' => 5,
  );

  return system_settings_form($form);
}


function arava_registration_takanon_links($form, &$form_state) {
  $form['arava_center_takanon_moa_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Moa terms link'),
    '#default_value' => variable_get('arava_center_takanon_moa_link', ''),
  );

  $form['arava_center_takanon_school_link'] = array(
    '#type' => 'textfield',
    '#title' => t('School terms link'),
    '#default_value' => variable_get('arava_center_takanon_school_link', ''),
  );

  $form['arava_center_takanon_amuta_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Amuta terms link'),
    '#default_value' => variable_get('arava_center_takanon_amuta_link', ''),
  );

  $form['arava_center_health_declaration_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Health declaration link'),
    '#default_value' => variable_get('arava_center_health_declaration_link', ''),
  );

  $form['arava_center_waver_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Moa terms link'),
    '#default_value' => variable_get('arava_center_waver_link', ''),
  );

  return system_settings_form($form);
}


function arava_registration_emails($form, &$form_state) {
  $form['arava_center_registration_confirmation_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Registration confirmation email subject'),
    '#default_value' => variable_get('arava_center_registration_confirmation_email_subject', ''),
  );

  $val = variable_get('arava_center_registration_confirmation_email', '');
  $form['arava_center_registration_confirmation_email'] = array(
    '#type' => 'text_format',
    '#title' => t('Registration confirmation email'),
    '#default_value' => $val['value'],
    '#format' => isset($val['format']) ? $val['format'] : 'html',
  );

  $form['arava_center_registration_accomodation_confirmation_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Registration - Accomodation confirmation email subject'),
    '#default_value' => variable_get('arava_center_registration_accomodation_confirmation_email_subject', ''),
  );

  $val = variable_get('arava_center_registration_accomodation_confirmation_email', '');
  $form['arava_center_registration_accomodation_confirmation_email'] = array(
    '#type' => 'text_format',
    '#title' => t('Registration- Accomodation confirmation email'),
    '#default_value' => $val['value'],
    '#format' => isset($val['format']) ? $val['format'] : 'html',
  );

  $form['arava_center_registration_payment_received_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Payment received email subject'),
    '#default_value' => variable_get('arava_center_registration_payment_received_email_subject', ''),
  );

  $val = variable_get('arava_center_registration_payment_received_email', '');
  $form['arava_center_registration_payment_received_email'] = array(
    '#type' => 'text_format',
    '#title' => t('Payment received email'),
    '#default_value' => $val['value'],
    '#format' => isset($val['format']) ? $val['format'] : 'html',
  );

  $form['arava_center_registration_approved_pay_accomodation_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Semester approved to pay accomodation - email subject'),
    '#default_value' => variable_get('arava_center_registration_approved_pay_accomodation_email_subject', ''),
  );

  $val = variable_get('arava_center_registration_approved_pay_accomodation_email', '');
  $form['arava_center_registration_approved_pay_accomodation_email'] = array(
    '#type' => 'text_format',
    '#title' => t('Semester approved to pay accomodation - email'),
    '#default_value' => $val['value'],
    '#format' => isset($val['format']) ? $val['format'] : 'html',
  );

  return system_settings_form($form);
}

function arava_registration_texts($form, &$form_state) {

  $val = variable_get('arava_center_registration_before_payment', array('value' => '', 'format' => 'html'));
  $form['arava_center_registration_before_payment'] = array(
    '#type' => 'text_format',
    '#title' => t('Registration before payment message'),
    '#default_value' => $val['value'],
    '#format' => isset($val['format']) ? $val['format'] : 'html',
  );

  $val = variable_get('arava_center_registration_payment_thanks', array('value' => '', 'format' => 'html'));
  $form['arava_center_registration_payment_thanks'] = array(
    '#type' => 'text_format',
    '#title' => t('Registration payment thanks message'),
    '#default_value' => $val['value'],
    '#format' => isset($val['format']) ? $val['format'] : 'html',
  );

  $val = variable_get('arava_center_registration_complete_thanks', array('value' => '', 'format' => 'html'));
  $form['arava_center_registration_complete_thanks'] = array(
    '#type' => 'text_format',
    '#title' => t('Registration complete (no payment) thanks message'),
    '#default_value' => $val['value'],
    '#format' => isset($val['format']) ? $val['format'] : 'html',
  );


  return system_settings_form($form);
}
