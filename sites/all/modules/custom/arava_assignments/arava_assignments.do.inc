<?php

function arava_assignments_do_assignment_form($form, &$form_state, $nid) {

  if (arava_assignments_do_assignment_access($nid)) {

    $path = path_to_theme();
    drupal_add_js($path . '/chosen/chosen.jquery.min.js');
    drupal_add_css($path . '/chosen/chosen.css');
    $path = drupal_get_path('module', 'arava_assignments');
    drupal_add_js($path . '/js/arava_assignments.js');

    $form = array();

    $form['intro'] = array(
      '#markup' => t('If you are going to take a break in the middle of doing your assignment, please save it before you go,
                      so that you don\'t loose your answers.<br>
                      You can save as many times as you like.')
    );

    $node = node_load($nid);
    $node_wrp = entity_metadata_wrapper('node', $node);
    $questions = $node_wrp->field_questions->value();
    $extras = $node_wrp->field_extra_assignments->value();

    module_load_include('inc', 'arava_assignments', 'AssignmentsAPI.class');
    $assignmentsAPI = new AssignmentsAPI();
    $completion_data = $assignmentsAPI->getCompletionDataForAssignment($nid);
    $answers = $completion_data['answers'];
    $remarks = $completion_data['remarks'];

    if (!empty($completion_data['grade'])) {
      $form['grade'] = array(
        '#markup' => '<br><br><div class="field-suffix">' . t('Grade') . ': ' . $completion_data['grade'] . '</div>',
      );
    }

    foreach ($questions as $key => $question) {
      $form['question_' . ($key+1)] = array(
        '#type' => 'text_format',
        '#format' => 'filtered_html',
        '#title' => ($key+1) . '. ' . $question,
        '#default_value' => (!empty($answers) && !empty($answers['question']) && !empty($answers['question'][$key+1])) ? $answers['question'][$key+1] : null,
        '#field_suffix' => (!empty($remarks) && !empty($remarks['question']) && !empty($remarks['question'][$key+1])) ? $remarks['question'][$key+1] : null,
      );
    }

    foreach ($extras as $key => $extra) {
      $form['extra_' . ($key+1)] = array(
        '#type' => 'text_format',
        '#format' => 'filtered_html',
        '#title' => $extra,
        '#default_value' => (!empty($answers) && !empty($answers['extra']) && !empty($answers['extra'][$key+1])) ? $answers['extra'][$key+1] : null,
        '#field_suffix' => (!empty($remarks) && !empty($remarks['extra']) && !empty($remarks['extra'][$key+1])) ? $remarks['extra'][$key+1] : null,
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

    $form['submit_save'] = array(
      '#type' => 'submit',
      '#value' => t('Save without sending link'),
      '#submit' => array('arava_assignments_do_assignment_form_submit'),
    );

    $form['submit_done'] = array(
      '#type' => 'submit',
      '#value' => t('Finished requirements for next lesson'),
      '#submit' => array('arava_assignments_done_submit'),
    );

    $form['submit_send_link'] = array(
      '#type' => 'submit',
      '#value' => t('Send link to checker'),
      '#submit' => array('arava_assignments_send_link_to_checker_submit'),
      '#validate' => array('arava_assignments_send_link_to_checker_validate')
    );

    return $form;

  }
}

function arava_assignments_do_assignment_form_submit($form, &$form_state) {

  $assignment_id = $form_state['values']['assignment_id'];
  $checker = $form_state['values']['checker'];

  module_load_include('inc', 'arava_assignments', 'AssignmentsAPI.class');
  $assignmentsAPI = new AssignmentsAPI();
  $assignment_completion_id = $assignmentsAPI->setAnswersCompletionDataForAssignment($assignment_id, $checker);

  // questions
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'question_') === 0) {
      $parts = explode('_', $key);
      $question = $parts[1];
      $assignmentsAPI->setAnswerForAssignment($assignment_completion_id, 'question', $question, $value['value']);
    }
  }

  // extra assignments
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'extra_') === 0) {
      $parts = explode('_', $key);
      $question = $parts[1];
      $assignmentsAPI->setAnswerForAssignment($assignment_completion_id, 'extra', $question, $value['value']);
    }
  }

}

function arava_assignments_send_link_to_checker_submit($form, &$form_state) {

  // trigger the normal submit first:
  arava_assignments_do_assignment_form_submit($form, $form_state);

  $assignment_id = $form_state['values']['assignment_id'];
  $assignment = node_load($assignment_id);

  $assignmentsAPI = new AssignmentsAPI();
  $assignment_completion = $assignmentsAPI->getCompletionDataForAssignment($assignment_id);

  $checker = user_load($form_state['values']['checker']);
  global $user;
  $user = user_load($user->uid);
  $checker_name = $checker->field_user_name[LANGUAGE_NONE][0]['value'];
  $link = url('assignment/' . $assignment_id . '/check/' . $assignment_completion['assignment_completion_id'], array('absolute' => true));
  $params = array(
    'checker_name' => $checker_name,
    'doer_name' => $user->field_user_name[LANGUAGE_NONE][0]['value'],
    'assignment_name' => $assignment->title,
    'assignment_link' => $link,
  );
  $result = drupal_mail('arava_assignments', 'check_assignment_link', $checker->mail, 'en', $params);
  if ($result['result']) {
    drupal_set_message(t('An email was sent to @name', array('@name' => $checker_name)), 'status');
  }
  else {
    drupal_set_message(t('There was a problem sending the email to @name. Please try again, or send them this link: @link',
      array(
        '@name' => $checker_name,
        '@link' => $link,
      )),
      'error');

  }

}

function arava_assignments_send_link_to_checker_validate($form, &$form_state) {
  if ($form_state['values']['checker'] == 0) {
    form_set_error('checker', t('Please choose who is going to check your assignment before sending them a link.'));
  }
}

function arava_assignments_done_submit($form, &$form_state) {

  // trigger the normal submit first:
  arava_assignments_do_assignment_form_submit($form, $form_state);

  $assignment_id = $form_state['values']['assignment_id'];

  $assignmentsAPI = new AssignmentsAPI();
  $assignment_completion = $assignmentsAPI->getCompletionDataForAssignment($assignment_id);
  $assignmentsAPI->setDoneForAssignment($assignment_completion['assignment_completion_id'], true);

  drupal_set_message(t('We have noted that you finished the requirements for the next lesson for this assignment.'), 'status');
}