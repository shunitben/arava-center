<?php

function arava_assignments_do_assignment_form($form, &$form_state, $nid) {
  $path = path_to_theme();
  drupal_add_js($path . '/chosen/chosen.jquery.min.js');
  drupal_add_css($path . '/chosen/chosen.css');
  $path = drupal_get_path('module', 'arava_assignments');
  drupal_add_js($path . '/js/arava_assignments.js');

  $form = array();

  $node = node_load($nid);
  $node_wrp = entity_metadata_wrapper('node', $node);
  $questions = $node_wrp->field_questions->value();

  module_load_include('inc', 'arava_assignments', 'AssignmentsAPI.class');
  $assignmentsAPI = new AssignmentsAPI();
  $completion_data = $assignmentsAPI->getCompletionDataForAssignment($nid);
  $answers = $completion_data['answers'];

  foreach ($questions as $key => $question) {
    $form['question_' . ($key+1)] = array(
      '#type' => 'textarea',
      '#title' => ($key+1) . '. ' . $question,
      '#default_value' => (!empty($answers) && !empty($answers[$key+1])) ? $answers[$key+1] : null,
    );
  }

  module_load_include('inc', 'arava_center', 'AravaCenterDbApi.class');
  $dbAPI = new AravaCenterDbApi();
  $available_checkers = $dbAPI->getAllUsersSignedUpToCourse($node_wrp->field_course->value()->nid, true);

  $form['checker'] = array(
    '#type' => 'select',
    '#title' => t('Who do you want to check this?'),
    '#options' => $available_checkers,
    '#default_value' => array($completion_data['checker']),
  );

  $form['assignment_id'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function arava_assignments_do_assignment_form_submit($form, &$form_state) {

  $assignment_id = $form_state['values']['assignment_id'];
  $checker = $form_state['values']['checker'];

  module_load_include('inc', 'arava_assignments', 'AssignmentsAPI.class');
  $assignmentsAPI = new AssignmentsAPI();
  $assignment_completion_id = $assignmentsAPI->setCompletionDataForAssignment($assignment_id, $checker);

  // questions
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'question_') === 0) {
      $parts = explode('_', $key);
      $question = $parts[1];
      $assignmentsAPI->setAnswerForAssignment($assignment_completion_id, $question, $value);
    }
  }

}