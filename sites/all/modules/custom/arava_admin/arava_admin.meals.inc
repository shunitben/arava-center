<?php

/**
 * Meals report
 *
 * Show for each day of the week how many people:
 * - are present (plus guests)
 * - have allergies to each thing
 * - want eggs/dairy
 */
function arava_admin_meals_page() {
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $semesterId = $mySemesterAPI->getSemesterId();

  // get the students presence
  $result = db_query("
   SELECT
  present.field_days_present_value AS day,
  COUNT(users.field_user_target_id) as num,
  SUM(gluten.field_gluten_value) AS gluten, SUM(soy.field_soy_value) AS soy, SUM(dairy.field_dairy_value) AS dairy, SUM(peanuts.field_peanuts_value) AS peanuts,
  SUM(eat_eggs.field_i_eat_eggs_value) AS eat_eggs, SUM(eat_dairy.field_i_eat_dairy_value) AS eat_dairy
  FROM
  node
  INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id AND semester.field_semester_target_id = $semesterId
  INNER JOIN field_data_field_days_present present ON node.nid = present.entity_id
  INNER JOIN field_data_field_user users ON node.nid = users.entity_id " .
//  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  "LEFT JOIN field_data_field_gluten gluten ON users.field_user_target_id = gluten.entity_id
  LEFT JOIN field_data_field_soy soy ON users.field_user_target_id = soy.entity_id
  LEFT JOIN field_data_field_dairy dairy ON users.field_user_target_id = dairy.entity_id
  LEFT JOIN field_data_field_peanuts peanuts ON users.field_user_target_id = peanuts.entity_id
  LEFT JOIN field_data_field_i_eat_eggs eat_eggs ON users.field_user_target_id = eat_eggs.entity_id
  LEFT JOIN field_data_field_i_eat_dairy eat_dairy ON users.field_user_target_id = eat_dairy.entity_id
  WHERE
  node.type = 'my_semester'
  GROUP BY present.field_days_present_value
  ");

  $rows = array();
  foreach ($result as $row) {
    $rows[$row->day] = array(
      $row->day,
      $row->num,
      '',
      $row->gluten,
      $row->soy,
      $row->dairy,
      $row->peanuts,
      $row->eat_eggs,
      $row->eat_dairy
    );
  }

  // get the guests presence
  $result = db_query("
   SELECT
  present.field_extra_days_present_value AS day,
  SUM(num.field_extra_guests_num_value) AS num
  FROM
  node
  INNER JOIN field_data_field_extra_days_present present ON node.nid = present.entity_id
  INNER JOIN field_data_field_extra_guests_num num ON node.nid = num.entity_id
  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  WHERE
  node.type = 'my_semester'
  GROUP BY present.field_extra_days_present_value
  ");

  foreach ($result as $row) {
    $rows[$row->day][2] = $row->num;
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
      t('Guests'),
      t('Gluten Allergy'),
      t('Soy Allergy'),
      t('Dairy Allergy'),
      t('Peanuts Allergy'),
      t('People who eat eggs'),
      t('People who eat dairy'),
    ),
    'rows' => $rows_ordered,
  ));
}