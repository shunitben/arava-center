<?php

function arava_assignments_check_assignment_form($form, &$form_state, $nid, $assignment_completion_id) {
  $path = path_to_theme();
  drupal_add_js($path . '/chosen/chosen.jquery.min.js');
  drupal_add_css($path . '/chosen/chosen.css');
  $path = drupal_get_path('module', 'arava_assignments');
  drupal_add_js($path . '/js/arava_assignments.js');

  $form = array();

  $form['intro'] = array(
    '#markup' => t('If you are going to take a break in the middle of checking this assignment, please save it before you go,
                    so that you don\'t loose your answers.<br>
                    You can save as many times as you like.')
  );

  $node = node_load($nid);
  $node_wrp = entity_metadata_wrapper('node', $node);
  $questions = $node_wrp->field_questions->value();
  $extras = $node_wrp->field_extra_assignments->value();

  module_load_include('inc', 'arava_assignments', 'AssignmentsAPI.class');
  $assignmentsAPI = new AssignmentsAPI();
  $completion_data = $assignmentsAPI->getCompletionDataForAssignment($nid, $assignment_completion_id);
  $answers = $completion_data['answers'];
  $remarks = $completion_data['remarks'];

  foreach ($questions as $key => $question) {
    $form['question_' . ($key+1)] = array(
      '#type' => 'textarea',
      '#title' => ($key+1) . '. ' . $question,
      '#field_prefix' => (!empty($answers) && !empty($answers['question']) && !empty($answers['question'][$key+1])) ? $answers['question'][$key+1] : null,
      '#default_value' => (!empty($remarks) && !empty($remarks['question']) && !empty($remarks['question'][$key+1])) ? $remarks['question'][$key+1] : null,
    );
  }

  foreach ($extras as $key => $extra) {
    $form['extra_' . ($key+1)] = array(
      '#type' => 'textarea',
      '#title' => $extra,
      '#field_prefix' => (!empty($answers) && !empty($answers['extra']) && !empty($answers['extra'][$key+1])) ? $answers['extra'][$key+1] : null,
      '#default_value' => (!empty($remarks) && !empty($remarks['extra']) && !empty($remarks['extra'][$key+1])) ? $remarks['extra'][$key+1] : null,
    );
  }

  $form['grade'] = array(
    '#type' => 'textfield',
    '#title' => t('Grade'),
    '#default_value' => $completion_data['grade'],
    '#description' => t('At the moment, you also need to input the grades in the grades system.'),
  );

  $form['assignment_id'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );

  $form['assignment_completion_id'] = array(
    '#type' => 'hidden',
    '#value' => $assignment_completion_id,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function arava_assignments_check_assignment_form_submit($form, &$form_state) {

  $assignment_id = $form_state['values']['assignment_id'];
  $assignment_completion_id = $form_state['values']['assignment_completion_id'];
  $grade = $form_state['values']['grade'];

  module_load_include('inc', 'arava_assignments', 'AssignmentsAPI.class');
  $assignmentsAPI = new AssignmentsAPI();
  $assignmentsAPI->setRemarksCompletionDataForAssignment($assignment_completion_id, $grade);

  // questions
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'question_') === 0) {
      $parts = explode('_', $key);
      $question = $parts[1];
      $assignmentsAPI->setRemarkForAssignment($assignment_completion_id, 'question', $question, $value);
    }
  }

  // extra assignments
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'extra_') === 0) {
      $parts = explode('_', $key);
      $question = $parts[1];
      $assignmentsAPI->setRemarkForAssignment($assignment_completion_id, 'extra', $question, $value);
    }
  }

}