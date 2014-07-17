<?php

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
