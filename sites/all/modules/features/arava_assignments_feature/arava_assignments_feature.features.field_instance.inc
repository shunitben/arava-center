<?php
/**
 * @file
 * arava_assignments_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function arava_assignments_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-assignment-field_assignment_type'
  $field_instances['node-assignment-field_assignment_type'] = array(
    'bundle' => 'assignment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_assignment_type',
    'label' => 'סוג מטלה',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-assignment-field_available'
  $field_instances['node-assignment-field_available'] = array(
    'bundle' => 'assignment',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'יש לסמן אם סיימתם לערוך את שעורי הבית ואם ניתן להציג אותם לתלמידים שהיו נוכחים בשיעור.
סימון זה ימנע מכם לערוך את המטלה בעתיד.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_available',
    'label' => 'זמין',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-assignment-field_course'
  $field_instances['node-assignment-field_course'] = array(
    'bundle' => 'assignment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'התחילו להקליד כדי לקבל הצעות',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_course',
    'label' => 'קורס',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-assignment-field_extra_assignments'
  $field_instances['node-assignment-field_extra_assignments'] = array(
    'bundle' => 'assignment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'זה המקום להזין משימות מדיטציה, שינון וכדומה.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_extra_assignments',
    'label' => 'מטלות נוספות',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-assignment-field_lesson_num'
  $field_instances['node-assignment-field_lesson_num'] = array(
    'bundle' => 'assignment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'אם זה לא מבחן',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lesson_num',
    'label' => 'מספר שיעור',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-assignment-field_questions'
  $field_instances['node-assignment-field_questions'] = array(
    'bundle' => 'assignment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_questions',
    'label' => 'שאלות',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 7,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('אם זה לא מבחן');
  t('התחילו להקליד כדי לקבל הצעות');
  t('זה המקום להזין משימות מדיטציה, שינון וכדומה.');
  t('זמין');
  t('יש לסמן אם סיימתם לערוך את שעורי הבית ואם ניתן להציג אותם לתלמידים שהיו נוכחים בשיעור.
סימון זה ימנע מכם לערוך את המטלה בעתיד.');
  t('מטלות נוספות');
  t('מספר שיעור');
  t('סוג מטלה');
  t('קורס');
  t('שאלות');

  return $field_instances;
}
