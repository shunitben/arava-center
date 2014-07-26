<?php
/**
 * @file
 * arava_registration_wizard.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function arava_registration_wizard_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_accomodation|node|my_semester|form';
  $field_group->group_name = 'group_accomodation';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'my_semester';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'לינה',
    'weight' => '3',
    'children' => array(
      0 => 'field_my_accomodation',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-accomodation field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_accomodation|node|my_semester|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_accordion|node|course|form';
  $field_group->group_name = 'group_accordion';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_times';
  $field_group->data = array(
    'label' => 'accordion',
    'weight' => '20',
    'children' => array(
      0 => 'group_recurring',
      1 => 'group_manual',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'effect' => 'none',
        'classes' => 'group-accordion field-group-accordion',
      ),
    ),
  );
  $export['group_accordion|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_courses|node|my_semester|form';
  $field_group->group_name = 'group_courses';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'my_semester';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'קורסים',
    'weight' => '2',
    'children' => array(
      0 => 'field_my_courses',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-courses field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_courses|node|my_semester|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_extra_meals|node|my_semester|form';
  $field_group->group_name = 'group_extra_meals';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'my_semester';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_meals';
  $field_group->data = array(
    'label' => 'Extra Meals',
    'weight' => '8',
    'children' => array(
      0 => 'field_extra_days_present',
      1 => 'field_extra_guests_num',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-extra-meals field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_extra_meals|node|my_semester|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_food|user|user|form';
  $field_group->group_name = 'group_food';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'מזון',
    'weight' => '1',
    'children' => array(
      0 => 'field_dairy',
      1 => 'field_gluten',
      2 => 'field_other_allergies',
      3 => 'field_peanuts',
      4 => 'field_vegan',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-food field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_food|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|node|course|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'מידע כללי',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_teacher',
      2 => 'field_image',
      3 => 'field_classroom',
      4 => 'field_semester',
      5 => 'field_price',
      6 => 'field_faculty',
      7 => 'title',
      8 => 'field_external_link',
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
  $export['group_general|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|node|my_semester|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'my_semester';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'כללי',
    'weight' => '0',
    'children' => array(
      0 => 'field_user',
      1 => 'field_semester',
      2 => 'title',
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
  $export['group_general|node|my_semester|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_manual|node|course|form';
  $field_group->group_name = 'group_manual';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_accordion';
  $field_group->data = array(
    'label' => 'זמנים ידניים',
    'weight' => '23',
    'children' => array(
      0 => 'field_lesson_times',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_manual|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_meals|node|my_semester|form';
  $field_group->group_name = 'group_meals';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'my_semester';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'ארוחות',
    'weight' => '4',
    'children' => array(
      0 => 'field_days_present',
      1 => 'group_extra_meals',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-meals field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_meals|node|my_semester|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_more_info|node|my_semester|form';
  $field_group->group_name = 'group_more_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'my_semester';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'מידע נוסף',
    'weight' => '6',
    'children' => array(
      0 => 'field_health_declaration',
      1 => 'field_takanon_amuta',
      2 => 'field_takanon_moa',
      3 => 'field_takanon_school',
      4 => 'field_waver',
      5 => 'field_comments',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-more-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_more_info|node|my_semester|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_payment|node|my_semester|form';
  $field_group->group_name = 'group_payment';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'my_semester';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'תשלומים',
    'weight' => '5',
    'children' => array(
      0 => 'field_payment_total',
      1 => 'field_payment_made',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-payment field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_payment|node|my_semester|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal|user|user|form';
  $field_group->group_name = 'group_personal';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'פרטים אישיים',
    'weight' => '0',
    'children' => array(
      0 => 'field_user_address',
      1 => 'field_user_name',
      2 => 'field_user_phone',
      3 => 'account',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_personal|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_recurring|node|course|form';
  $field_group->group_name = 'group_recurring';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_accordion';
  $field_group->data = array(
    'label' => 'זמנים חוזרים',
    'weight' => '22',
    'children' => array(
      0 => 'field_lesson_days',
      1 => 'field_lesson_hours',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'זמנים חוזרים',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_recurring|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_times|node|course|form';
  $field_group->group_name = 'group_times';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'זמני השיעורים',
    'weight' => '1',
    'children' => array(
      0 => 'field_lesson_times_type',
      1 => 'group_accordion',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-times field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_times|node|course|form'] = $field_group;

  return $export;
}
