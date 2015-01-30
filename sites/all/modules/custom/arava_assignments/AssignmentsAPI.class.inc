<?php

class AssignmentsAPI {

  function getCompletionDataForAssignment($assignment_id) {
    global $user;

    $data = db_select('assignment_completion')
      ->condition('assignment_id', $assignment_id)
      ->condition('student', $user->uid)
      ->fields('assignment_completion', array('assignment_completion_id', 'checker', 'grade'))
      ->execute()
      ->fetchAssoc();

    $answers = empty($data) ? array() : $this->getAnswersForAssignment($data['assignment_completion_id']);
    $remarks = empty($data) ? array() : $this->getRemarksForAssignment($data['assignment_completion_id']);

    return array(
      'checker' => empty($data) ? null : $data['checker'],
      'grade' => empty($data) ? null : $data['grade'],
      'answers' => $answers,
      'remarks' => $remarks,
    );
  }

  function getAnswersForAssignment($assignment_completion_id) {
    $result = db_select('assignment_answers')
      ->condition('assignment_completion_id', $assignment_completion_id)
      ->fields('assignment_answers', array('question', 'answer'))
      ->execute();
    $data = array();
    foreach ($result as $row) {
      $data[$row->question] = $row->answer;
    }
    return $data;
  }

  function getRemarksForAssignment($assignment_completion_id) {
    $result = db_select('assignment_remarks')
      ->condition('assignment_completion_id', $assignment_completion_id)
      ->fields('assignment_remarks', array('question', 'remark'))
      ->execute();
    $data = array();
    foreach ($result as $row) {
      $data[$row->question] = $row->answer;
    }
    return $data;
  }

  function setCompletionDataForAssignment($assignment_id, $checker = null) {
    global $user;

    // see if the student has already begun this assignment
    $result = db_select('assignment_completion')
      ->condition('assignment_id', $assignment_id)
      ->condition('student', $user->uid)
      ->fields('assignment_completion', array('assignment_completion_id'))
      ->execute()->fetchAssoc();

    if (!empty($result['assignment_completion_id'])) {
      db_update('assignment_completion')
        ->condition('assignment_id', $assignment_id)
        ->condition('student', $user->uid)
        ->fields(array(
          'checker' => $checker,
        ))
        ->execute();
      return $result['assignment_completion_id'];
    }
    else {
      return db_insert('assignment_completion')
        ->fields(array(
          'assignment_id' => $assignment_id,
          'student' => $user->uid,
          'checker' => $checker,
          'created' => time(),
        ))
        ->execute();
    }
  }

  function setAnswerForAssignment($assignment_completion_id, $question, $answer) {
    db_merge('assignment_answers')
      ->key(array(
        'assignment_completion_id' => $assignment_completion_id,
        'question' => $question,
      ))
      ->fields(array(
        'assignment_completion_id' => $assignment_completion_id,
        'question' => $question,
        'answer' => $answer,
      ))
      ->execute();
  }

  function setRemarkForAssignment($assignment_completion_id, $question, $remark) {
    db_merge('assignment_remarks')
      ->key(array(
        'assignment_completion_id' => $assignment_completion_id,
        'question' => $question,
      ))
      ->fields(array(
        'assignment_completion_id' => $assignment_completion_id,
        'question' => $question,
        'remark' => $remark,
      ))
      ->execute();
  }

  // find any homework and quizzes (not final tests) for this course, which the user hadn't begun.
  function incompleteAssignmentsForCourse($course_nid) {
    $query = db_select('node', 'assignments');
    $query->join('field_data_field_course', 'course_ref', 'assignments.nid = course_ref.entity_id');
    $query->join('field_data_field_lesson_num', 'lesson_num', 'assignments.nid = lesson_num.entity_id');
    $query->join('field_data_field_assignment_type', 'type', 'assignments.nid = type.entity_id');
    $query->leftJoin('assignment_completion', 'assignment_completion', 'course_ref.field_course_target_id = assignment_completion.assignment_id');
    $query
    ->condition('assignments.type', 'assignment')
    ->condition('course_ref.field_course_target_id', $course_nid)
    ->isNull('assignment_completion.student')
    ->fields('lesson_num', array('field_lesson_num_value'))
    ->fields('type', array('field_assignment_type_value'));
    $results = $query->execute();

    $incomplete = array();
    foreach ($results as $row) {
      $incomplete[$row->field_assignment_type_value][] = $row->field_lesson_num_value;
    }
    return $incomplete;
  }
}