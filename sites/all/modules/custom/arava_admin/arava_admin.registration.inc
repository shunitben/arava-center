<?php

function arava_admin_registration_page() {

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $semesterId = $mySemesterAPI->getSemesterId();

  $result = db_query("
  SELECT

  FROM
  node
  INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id AND semester.field_semester_target_id = $semesterId
  LEFT JOIN field_data_field_my_courses courses ON node.nid = courses.entity_id
  LEFT JOIN field_data_field_my_accomodation accomodation ON node.nid = accomodation.entity_id
  LEFT JOIN field_data_field_takanon_moa takanon_moa ON node.nid = takanon_moa.entity_id
  LEFT JOIN field_data_field_takanon_school takanon_school ON node.nid = takanon_school.entity_id
  LEFT JOIN field_data_field_registration_complete complete ON node.nid = complete.entity_id
  WHERE
  node.type = 'my_semester'
  AND (
    accomodation.field_my_accomodation_target_id IS NULL
    OR takanon_moa.field_takanon_moa_value IS NULL OR takanon_moa.field_takanon_moa_value = 0
    OR takanon_school.field_takanon_school_value IS NULL OR takanon_school.field_takanon_school_value = 0
    OR complete.field_registration_complete_value IS NULL OR complete.field_registration_complete_value = 0
  )
  ");
}