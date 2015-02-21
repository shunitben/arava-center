<?php
/**
 * @file
 * arava_management.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function arava_management_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'taxonomy_term-emails-field_department_email'
  $field_instances['taxonomy_term-emails-field_department_email'] = array(
    'bundle' => 'emails',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_department_email',
    'label' => 'Department email',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Department email');

  return $field_instances;
}
