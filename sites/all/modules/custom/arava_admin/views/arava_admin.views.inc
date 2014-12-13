<?php

function arava_admin_views_data_alter(&$data) {
  if ( isset($data['field_data_field_semester']) && !isset($data['field_data_field_semester']['semester']) ) {
    $data['field_data_field_semester']['semester'] = array(
      'group' => t('Custom'),
      'real field' => 'semester', // name of entity field to which filter applies
      'title' => t('Semester'),
      'help' => t('Semesters dropdown'),
      'filter' => array(
        'handler' => 'arava_admin_handler_filter_semester',
      ),
    );
  }
}