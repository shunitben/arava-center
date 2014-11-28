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
    'weight' => '2',
    'children' => array(
      0 => 'field_my_accomodation',
      1 => 'field_roommates',
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
      0 => 'group_manual',
      1 => 'group_recurring',
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
    'weight' => '1',
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
  $field_group->identifier = 'group_files|node|course|form';
  $field_group->group_name = 'group_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'קבצים',
    'weight' => '2',
    'children' => array(
      0 => 'field_audio_files',
      1 => 'field_pdf_files',
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
  $export['group_files|node|course|form'] = $field_group;

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
    'weight' => '2',
    'children' => array(
      0 => 'field_dairy',
      1 => 'field_gluten',
      2 => 'field_other_allergies',
      3 => 'field_peanuts',
      4 => 'field_soy',
      5 => 'field_i_eat_dairy',
      6 => 'field_i_eat_eggs',
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
      7 => 'field_external_link',
      8 => 'title',
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
      3 => 'field_registration_complete',
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
  $field_group->identifier = 'group_homework|node|course|form';
  $field_group->group_name = 'group_homework';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'שעורי בית',
    'weight' => '4',
    'children' => array(
      0 => 'field_number_of_homework',
      1 => 'field_final_test',
      2 => 'field_number_of_quizzes',
      3 => 'field_examiners',
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
  $export['group_homework|node|course|form'] = $field_group;

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
    'weight' => '3',
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
  $field_group->identifier = 'group_mt_contact_info|node|teacher|default';
  $field_group->group_name = 'group_mt_contact_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'teacher';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_mt_faculty_details';
  $field_group->data = array(
    'label' => 'Contact information',
    'weight' => '5',
    'children' => array(
      0 => 'field_mt_contact_info',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => 'group-mt-contact-info field-group-accordion-item',
      ),
    ),
  );
  $export['group_mt_contact_info|node|teacher|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_mt_faculty_details|node|teacher|default';
  $field_group->group_name = 'group_mt_faculty_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'teacher';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '2',
    'children' => array(
      0 => 'group_mt_contact_info',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-mt-faculty-details field-group-accordion',
        'effect' => 'bounceslide',
      ),
    ),
  );
  $export['group_mt_faculty_details|node|teacher|default'] = $field_group;

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
    'weight' => '4',
    'children' => array(
      0 => 'field_payment_total',
      1 => 'field_payment_made',
      2 => 'field_payment_comments',
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
