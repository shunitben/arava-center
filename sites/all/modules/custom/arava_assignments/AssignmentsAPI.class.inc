<?php

class AssignmentsAPI {

  /**
   * @param $assignment_id
   * @return array
   */
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

  /**
   * @param $assignment_completion_id
   * @return array
   */
  function getAnswersForAssignment($assignment_completion_id) {
    $result = db_select('assignment_answers')
      ->condition('assignment_completion_id', $assignment_completion_id)
      ->fields('assignment_answers', array('type', 'question', 'answer'))
      ->execute();
    $data = array();
    foreach ($result as $row) {
      $data[$row->type][$row->question] = $row->answer;
    }
    return $data;
  }

  /**
   * @param $assignment_completion_id
   * @return array
   */
  function getRemarksForAssignment($assignment_completion_id) {
    $result = db_select('assignment_remarks')
      ->condition('assignment_completion_id', $assignment_completion_id)
      ->fields('assignment_remarks', array('type', 'question', 'remark'))
      ->execute();
    $data = array();
    foreach ($result as $row) {
      $data[$row->type][$row->question] = $row->answer;
    }
    return $data;
  }

  /**
   * @param $assignment_id
   * @param null $checker
   * @return DatabaseStatementInterface|int|null
   */
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

  /**
   * @param $assignment_completion_id
   * @param $question
   * @param $answer
   */
  function setAnswerForAssignment($assignment_completion_id, $type, $question, $answer) {
    db_merge('assignment_answers')
      ->key(array(
        'assignment_completion_id' => $assignment_completion_id,
        'type' => $type,
        'question' => $question,
      ))
      ->fields(array(
        'assignment_completion_id' => $assignment_completion_id,
        'type' => $type,
        'question' => $question,
        'answer' => $answer,
      ))
      ->execute();
  }

  /**
   * @param $assignment_completion_id
   * @param $question
   * @param $remark
   */
  function setRemarkForAssignment($assignment_completion_id, $type, $question, $remark) {
    db_merge('assignment_remarks')
      ->key(array(
        'assignment_completion_id' => $assignment_completion_id,
        'type' => $type,
        'question' => $question,
      ))
      ->fields(array(
        'assignment_completion_id' => $assignment_completion_id,
        'type' => $type,
        'question' => $question,
        'remark' => $remark,
      ))
      ->execute();
  }

  /**
   * @param $course_nid
   * @return array
   */
  function getAssignmentsListForCourse($course_nid) {
    global $user;
    $query = db_select('node', 'assignments');
    $query->join('field_data_field_course', 'course_ref', 'assignments.nid = course_ref.entity_id');
    $query->leftJoin('field_data_field_lesson_num', 'lesson_num', 'assignments.nid = lesson_num.entity_id');
    $query->join('field_data_field_assignment_type', 'type', 'assignments.nid = type.entity_id');
    $query->leftJoin('assignment_completion', 'assignment_completion', 'assignments.nid = assignment_completion.assignment_id AND assignment_completion.student = ' . $user->uid);
    $query
      ->condition('assignments.type', 'assignment')
      ->condition('course_ref.field_course_target_id', $course_nid)
      ->condition('course_ref.bundle', 'assignment')
      ->fields('assignments', array('nid'))
      ->fields('lesson_num', array('field_lesson_num_value'))
      ->fields('type', array('field_assignment_type_value'))
      ->fields('assignment_completion', array('assignment_completion_id'));
    $results = $query->execute();

    $assignments = array();
    foreach ($results as $row) {
      $assignments[$row->field_assignment_type_value][$row->field_lesson_num_value] = array(
        'assignment_id' => $row->nid,
        'lesson_num' => $row->field_lesson_num_value,
        'completion' => isset($row->assignment_completion_id),
      );
    }
    // order
    foreach ($assignments as &$type) {
      ksort($type);
    }
    return $assignments;
  }

  /**
   * find any homework and quizzes (not final tests) for this course, which the user hadn't begun.
   * @param $course_nid
   * @return array
   */
  function incompleteAssignmentsForCourse($course_nid) {
    global $user;
    $query = db_select('node', 'assignments');
    $query->join('field_data_field_course', 'course_ref', 'assignments.nid = course_ref.entity_id');
    $query->join('field_data_field_lesson_num', 'lesson_num', 'assignments.nid = lesson_num.entity_id');
    $query->join('field_data_field_assignment_type', 'type', 'assignments.nid = type.entity_id');
    $query->leftJoin('assignment_completion', 'assignment_completion', 'assignments.nid = assignment_completion.assignment_id AND assignment_completion.student = ' . $user->uid);
    $query
    ->condition('assignments.type', 'assignment')
    ->condition('course_ref.field_course_target_id', $course_nid)
    ->condition('course_ref.bundle', 'assignment')
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