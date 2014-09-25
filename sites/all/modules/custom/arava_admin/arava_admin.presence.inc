<?php

/**
 * Show how many students should be present every day
 * @return string
 */
function arava_admin_presence_page() {
  // get the students presence
  $result = db_query("
   SELECT
  present.field_days_present_value AS day,
  COUNT(users.field_user_target_id) as num
  FROM
  node
  INNER JOIN field_data_field_days_present present ON node.nid = present.entity_id
  INNER JOIN field_data_field_user users ON node.nid = users.entity_id
  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  WHERE
  node.type = 'my_semester'
  GROUP BY present.field_days_present_value
  ");

  $rows = array();
  foreach ($result as $row) {
    $rows[$row->day] = array(
      $row->day,
      $row->num,
      l(t('list'), 'admin/arava-reports/presence/'.$row->day.'/list'),
    );
  }

  // order the days
  $rows_ordered = array(
    $rows['sunday'],
    $rows['monday'],
    $rows['tuesday'],
    $rows['wednesday'],
    $rows['thursday'],
    $rows['friday'],
    $rows['saturday'],
  );

  return theme('table', array(
    'header' => array(
      t('Day'),
      t('Students'),
      t('List'),
    ),
    'rows' => $rows_ordered,
  ));
}