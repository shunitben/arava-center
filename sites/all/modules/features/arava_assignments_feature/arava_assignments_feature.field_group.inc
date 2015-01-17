<?php
/**
 * @file
 * arava_assignments_feature.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function arava_assignments_feature_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_extra_assignments|node|assignment|form';
  $field_group->group_name = 'group_extra_assignments';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'מטלות נוספות',
    'weight' => '8',
    'children' => array(
      0 => 'field_extra_assignments',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-extra-assignments field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_extra_assignments|node|assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|node|assignment|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'כללי',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_course',
      2 => 'field_assignment_type',
      3 => 'field_lesson_num',
      4 => 'field_available',
      5 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-general field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_general|node|assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_questions|node|assignment|form';
  $field_group->group_name = 'group_questions';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'שאלות',
    'weight' => '7',
    'children' => array(
      0 => 'field_questions',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-questions field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_questions|node|assignment|form'] = $field_group;

  return $export;
}
