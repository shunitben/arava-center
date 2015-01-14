<?php

/**
 * Meals report
 *
 * Show for each day of the week how many people:
 * - are present
 * - prefer not to eat soy/gluten
 * - want eggs/dairy
 */
function arava_admin_meals_page() {
  if (!empty($_GET['semester']) && is_numeric($_GET['semester'])) {
    $semesterId = $_GET['semester'];
  }
  else {
    module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
    $mySemesterAPI = new MySemesterAPI();
    $semesterId = $mySemesterAPI->getSemesterId();
  }

  // get the students presence:

  // my semester nodes for this semester, with presence days, with user, with registration complete
  $result = db_query("
   SELECT
  present.field_days_present_value AS day,
  COUNT(users.field_user_target_id) as num,
  SUM(gluten.field_gluten_value) AS gluten, SUM(soy.field_soy_value) AS soy,
  SUM(eat_eggs.field_i_eat_eggs_value) AS eat_eggs, SUM(eat_dairy.field_i_eat_dairy_value) AS eat_dairy
  FROM
  node
  INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id AND semester.field_semester_target_id = $semesterId
  INNER JOIN field_data_field_days_present present ON node.nid = present.entity_id
  INNER JOIN field_data_field_user users ON node.nid = users.entity_id
  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  LEFT JOIN field_data_field_gluten gluten ON users.field_user_target_id = gluten.entity_id
  LEFT JOIN field_data_field_soy soy ON users.field_user_target_id = soy.entity_id
  LEFT JOIN field_data_field_i_eat_eggs eat_eggs ON users.field_user_target_id = eat_eggs.entity_id
  LEFT JOIN field_data_field_i_eat_dairy eat_dairy ON users.field_user_target_id = eat_dairy.entity_id
  WHERE
  node.type = 'my_semester'
  GROUP BY present.field_days_present_value
  ");

  $rows = array(
    'sunday' => array(),
    'sunday_lunch' => array(),
    'sunday_supper' => array(),
    'monday' => array(),
    'tuesday' => array(),
    'wednesday' => array(),
    'thursday' => array(),
    'thursday_lunch' => array(),
    'thursday_supper' => array(),
    'friday' => array(),
    'friday_lunch' => array(),
    'friday_supper' => array(),
    'saturday' => array(),
    'saturday_lunch' => array(),
    'saturday_supper' => array(),
  );
  foreach ($result as $row) {
    $rows[$row->day] = array(
      $row->day,
      $row->num,
      $row->gluten,
      $row->soy,
      $row->eat_eggs,
      $row->eat_dairy
    );
  }

  // get the meals presence
  $result = db_query("
  SELECT
  present.field_meals_present_value AS meal,
  COUNT(users.field_user_target_id) as num,
  SUM(gluten.field_gluten_value) AS gluten, SUM(soy.field_soy_value) AS soy,
  SUM(eat_eggs.field_i_eat_eggs_value) AS eat_eggs, SUM(eat_dairy.field_i_eat_dairy_value) AS eat_dairy
  FROM
  node
  INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id AND semester.field_semester_target_id = $semesterId
  INNER JOIN field_data_field_meals_present present ON node.nid = present.entity_id
  INNER JOIN field_data_field_user users ON node.nid = users.entity_id
  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  LEFT JOIN field_data_field_gluten gluten ON users.field_user_target_id = gluten.entity_id
  LEFT JOIN field_data_field_soy soy ON users.field_user_target_id = soy.entity_id
  LEFT JOIN field_data_field_i_eat_eggs eat_eggs ON users.field_user_target_id = eat_eggs.entity_id
  LEFT JOIN field_data_field_i_eat_dairy eat_dairy ON users.field_user_target_id = eat_dairy.entity_id
  WHERE
  node.type = 'my_semester'
  GROUP BY present.field_meals_present_value
  ");

  foreach ($result as $row) {
    $rows[$row->meal] = array(
      $row->meal,
      $row->num,
      $row->gluten,
      $row->soy,
      $row->eat_eggs,
      $row->eat_dairy
    );
  }

  // fill empty rows
  foreach ($rows as $key => &$row) {
    if (empty($row)) {
      $row = array($key,0,0,0,0,0,0);
    }
  }

  $form_object = drupal_get_form('arava_admin_semesters_dropdown_form');
  $form = drupal_render($form_object);

  return $form . theme('table', array(
    'header' => array(
      t('Day'),
      t('Students'),
      t('Gluten Allergy'),
      t('Soy Allergy'),
      t('People who eat eggs'),
      t('People who eat dairy'),
    ),
    'rows' => $rows,
  ));
}


/**
 * Meals people list
 */
function arava_admin_meals_people_page() {
  if (!empty($_GET['semester']) && is_numeric($_GET['semester'])) {
    $semesterId = $_GET['semester'];
  }
  else {
    module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
    $mySemesterAPI = new MySemesterAPI();
    $semesterId = $mySemesterAPI->getSemesterId();
  }

  $meals_options = _arava_registration_meals_options();

  // get the meals presence
  $result = db_query("
  SELECT
  present.field_meals_present_value AS meal,
  user_name.field_user_name_value, users.field_user_target_id,
  gluten.field_gluten_value AS gluten, soy.field_soy_value AS soy,
  eat_eggs.field_i_eat_eggs_value AS eat_eggs, eat_dairy.field_i_eat_dairy_value AS eat_dairy
  FROM
  node
  INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id AND semester.field_semester_target_id = $semesterId
  INNER JOIN field_data_field_meals_present present ON node.nid = present.entity_id
  INNER JOIN field_data_field_user users ON node.nid = users.entity_id
  LEFT JOIN field_data_field_user_name user_name ON users.field_user_target_id = user_name.entity_id
  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  LEFT JOIN field_data_field_gluten gluten ON users.field_user_target_id = gluten.entity_id
  LEFT JOIN field_data_field_soy soy ON users.field_user_target_id = soy.entity_id
  LEFT JOIN field_data_field_i_eat_eggs eat_eggs ON users.field_user_target_id = eat_eggs.entity_id
  LEFT JOIN field_data_field_i_eat_dairy eat_dairy ON users.field_user_target_id = eat_dairy.entity_id
  WHERE
  node.type = 'my_semester'
  ");

  foreach ($result as $row) {
    if (!isset($rows[$row->field_user_target_id])) {
      $rows[$row->field_user_target_id] = array(
        $row->field_user_name_value,
        $row->gluten,
        $row->soy,
        $row->eat_eggs,
        $row->eat_dairy
      );
      $rows[$row->field_user_target_id] = array_merge($rows[$row->field_user_target_id], array_fill_keys(array_keys($meals_options), 0));
    }
    $rows[$row->field_user_target_id][$row->meal] = 1;
  }

  $form_object = drupal_get_form('arava_admin_semesters_dropdown_form');
  $form = drupal_render($form_object);

  $header = array(
    t('Student'),
    t('no gluten'),
    t('no soy'),
    t('I eat eggs'),
    t('I eat dairy'),
  );
  $header = array_merge($header, array_values($meals_options));

  return $form . theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));
}

/**
 * Meals' Guests report
 */
function arava_admin_meals_guests_page() {
  if (!empty($_GET['semester']) && is_numeric($_GET['semester'])) {
    $semesterId = $_GET['semester'];
  }
  else {
    module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
    $mySemesterAPI = new MySemesterAPI();
    $semesterId = $mySemesterAPI->getSemesterId();
  }

  $meal_options = _arava_registration_guest_meals_options();
  $header = array();
  $header[] = '';
  foreach ($meal_options as $value) {
    $header[] = $value;
  }
  $rows = array();
  for ($i=1; $i<=5; $i++) {
    $rows[$i][] = t('Weekend @num', array('@num' => $i));
    foreach ($meal_options as $key => $value) {
      $rows[$i][$key] = 0;
    }
  }


  // get the guests presence
  $result = db_query("
   SELECT
  present.field_guests_for_meals_value AS serialized
  FROM
  node
  INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id AND semester.field_semester_target_id = $semesterId
  INNER JOIN field_data_field_guests_for_meals present ON node.nid = present.entity_id
  INNER JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id AND complete.field_registration_complete_value = '1'
  WHERE
  node.type = 'my_semester'
  ");

  foreach ($result as $row) {
    if (!empty($row->serialized)) {
       $data = unserialize($row->serialized);
      foreach ($data as $meal => $num) {
        if (!empty($num) && is_numeric($num)) {
          $meal_data = explode('-', $meal);
          $rows[$meal_data[1]][$meal_data[0]] = $rows[$meal_data[1]][$meal_data[0]] + $num;
        }
      }
    }
  }

  // fill empty rows
  foreach ($rows as $key => &$row) {
    if (empty($row)) {
      $row = array($key,0,0,0,0,0,0);
    }
  }

  $form_object = drupal_get_form('arava_admin_semesters_dropdown_form');
  $form = drupal_render($form_object);

  return $form . theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));
}