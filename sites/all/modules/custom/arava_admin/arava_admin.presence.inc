<?php

/**
 * Show how many students should be present every day
 * @return string
 */
function arava_admin_presence_page() {

  if (!empty($_GET['semester']) && is_numeric($_GET['semester'])) {
    $semesterId = $_GET['semester'];
  }
  else {
    module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
    $mySemesterAPI = new MySemesterAPI();
    $semesterId = $mySemesterAPI->getSemesterId();
  }

  // get the students presence
  $result = db_query("
   SELECT
  present.field_days_present_value AS day,
  COUNT(users.field_user_target_id) as num
  FROM
  node
  INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id AND semester.field_semester_target_id = $semesterId
  INNER JOIN field_data_field_days_present present ON node.nid = present.entity_id
  INNER JOIN field_data_field_user users ON node.nid = users.entity_id
  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  WHERE
  node.type = 'my_semester'
  GROUP BY present.field_days_present_value
  ");

  $rows = array(
    'sunday' => array(),
    'monday' => array(),
    'tuesday' => array(),
    'wednesday' => array(),
    'thursday' => array(),
    'friday' => array(),
    'saturday' => array(),
  );
  foreach ($result as $row) {
    $rows[$row->day] = array(
      $row->day,
      $row->num,
      l(t('list'), 'admin/arava-reports/presence/'.$row->day.'/list'),
    );
  }

  foreach ($rows as $key => &$row) {
    if (empty($row)) {
      $row = array($key, 0, '');
    }
  }

  $form_object = drupal_get_form('arava_admin_semesters_dropdown_form');
  $form = drupal_render($form_object);

  return $form . theme('table', array(
    'header' => array(
      t('Day'),
      t('Students'),
      t('List'),
    ),
    'rows' => $rows,
  ));
}