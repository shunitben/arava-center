<?php

class AssignmentsAPI {

  /**
   * @param $assignment_id
   * @return array
   */
  function getCompletionDataForAssignment($assignment_id, $assignment_completion_id = null) {
    global $user;

    $query = db_select('assignment_completion')
      ->condition('assignment_id', $assignment_id)
      ->fields('assignment_completion', array('assignment_completion_id', 'checker', 'grade', 'done'));
    if ($assignment_completion_id) {
      $query->condition('assignment_completion_id', $assignment_completion_id);
    }
    else {
      $query->condition('student', $user->uid);
    }
    $data = $query->execute()
      ->fetchAssoc();

    $answers = empty($data) ? array() : $this->getAnswersForAssignment($data['assignment_completion_id']);
    $remarks = empty($data) ? array() : $this->getRemarksForAssignment($data['assignment_completion_id']);

    return array(
      'assignment_completion_id' => $data['assignment_completion_id'],
      'checker' => empty($data) ? null : $data['checker'],
      'grade' => empty($data) ? null : $data['grade'],
      'done' => empty($data) ? null : $data['done'],
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
      $data[$row->type][$row->question] = $row->remark;
    }
    return $data;
  }

  /**
   * @param $assignment_id
   * @param null $checker
   * @return DatabaseStatementInterface|int|null
   */
  function setAnswersCompletionDataForAssignment($assignment_id, $checker = null) {
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

  function setRemarksCompletionDataForAssignment($assignment_completion_id, $grade) {
    if (empty($grade)) $grade = 0;

    db_update('assignment_completion')
      ->condition('assignment_completion_id', $assignment_completion_id)
      ->fields(array(
        'grade' => $grade,
      ))
      ->execute();
  }

  function setDoneForAssignment($assignment_completion_id, $done = true) {

    db_update('assignment_completion')
      ->condition('assignment_completion_id', $assignment_completion_id)
      ->fields(array(
        'done' => (int)$done,
      ))
      ->execute();
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
    $query->join('field_data_field_available', 'available', 'assignments.nid = available.entity_id');
    $query->join('field_data_field_course', 'course_ref', 'assignments.nid = course_ref.entity_id');
    $query->leftJoin('field_data_field_lesson_num', 'lesson_num', 'assignments.nid = lesson_num.entity_id');
    $query->join('field_data_field_assignment_type', 'type', 'assignments.nid = type.entity_id');
    $query->leftJoin('assignment_completion', 'assignment_completion', 'assignments.nid = assignment_completion.assignment_id AND assignment_completion.student = ' . $user->uid);
    $query->join('attendance', 'attendance', 'attendance.student_uid = ' . $user->uid . ' AND attendance.course_nid = course_ref.field_course_target_id');
    $query
      ->condition('available.field_available_value', '1')
      ->condition('assignments.type', 'assignment')
      ->condition('course_ref.field_course_target_id', $course_nid)
      ->condition('course_ref.bundle', 'assignment')
      ->condition('attendance.attendance_status', array(1,2), 'IN')
      ->fields('assignments', array('nid'))
      ->fields('lesson_num', array('field_lesson_num_value'))
      ->fields('type', array('field_assignment_type_value'))
      ->fields('assignment_completion', array('assignment_completion_id', 'done', 'grade'));
    $results = $query->execute();

    $assignments = array();
    foreach ($results as $row) {
      $assignments[$row->field_assignment_type_value][$row->field_lesson_num_value] = array(
        'assignment_id' => $row->nid,
        'lesson_num' => $row->field_lesson_num_value,
        'completion' => isset($row->assignment_completion_id),
        'done' => $row->done,
        'grade' => $row->grade,
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

  /**
   * Get all assignments that the student has been assigned to check
   * @return array
   */
  function getAssignmentsToCheck() {
    global $user;

    $query = db_select('assignment_completion', 'ac');
    $query->join('node', 'assignment', 'ac.assignment_id = assignment.nid');
    $query->leftJoin('field_data_field_lesson_num', 'lesson_num', 'assignment.nid = lesson_num.entity_id');
    $query->join('field_data_field_course', 'course_ref', 'assignment.nid = course_ref.entity_id');
    $query->join('node', 'course', 'course_ref.field_course_target_id = course.nid');
    $query->join('field_data_field_assignment_type', 'type', 'assignment.nid = type.entity_id');
    $query
      ->condition('ac.checker', $user->uid)
      ->condition('ac.grade', 0)
      ->condition('course_ref.bundle', 'assignment')
      ->fields('course', array('title', 'nid'))
      ->fields('ac', array('assignment_completion_id'))
      ->fields('assignment', array('nid'))
      ->fields('lesson_num', array('field_lesson_num_value'))
      ->fields('type', array('field_assignment_type_value'));
    $results = $query->execute();

    $assignments = array();
    foreach ($results as $row) {
      $assignments[$row->nid][$row->field_assignment_type_value][$row->field_lesson_num_value] = array(
        'assignment_id' => $row->assignment_nid,
        'assignment_completion_id' => $row->assignment_completion_id,
        'lesson_num' => $row->field_lesson_num_value,
        'course_name' => $row->title,
      );
    }
    return $assignments;
  }

  function getDoneStatusForCourseReports($course_nid) {
    $query = db_select('node', 'assignment');
    $query->join('field_data_field_course', 'course_ref', 'assignment.nid = course_ref.entity_id');
    $query->join('field_data_field_lesson_num', 'lesson_num', 'assignment.nid = lesson_num.entity_id');
    $query->join('field_data_field_assignment_type', 'type', 'assignment.nid = type.entity_id');
    $query->join('assignment_completion', 'ac', 'assignment.nid = ac.assignment_id');
    $query
      ->condition('assignment.type', 'assignment')
      ->condition('course_ref.field_course_target_id', $course_nid)
      ->condition('ac.done', 1)
      ->fields('ac', array('student', 'assignment_completion_id', 'assignment_id'))
      ->fields('lesson_num', array('field_lesson_num_value'))
      ->fields('type', array('field_assignment_type_value'));
    $results = $query->execute();

    $done = array();
    foreach ($results as $row) {
      $lesson_num = $row->field_lesson_num_value;
      $assignment_type = $row->field_assignment_type_value;
      $student = $row->student;
      $assignment_completion_id = $row->assignment_completion_id;
      $assignment_id = $row->assignment_id;
      $done[$lesson_num][$assignment_type]['assignment_id'] = $assignment_id;
      $done[$lesson_num][$assignment_type][$student] = $assignment_completion_id;
    }
    return $done;
  }
}