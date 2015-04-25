<?php

function gradereg_node_grades_list($node){
	
	global $user;
	
//	$semesters = array();
//	$semester_query = db_query("select * from {node} where type='semester' and status='1' order by created desc");
//	foreach($semester_query as $r){
//		$semesters[$r->nid] = $r->title;
//	}
//
//	if(isset($_GET['semester']) && $_GET['semester']){
//		$current_semester = $_GET['semester'];
//	}else if(arg(3) && is_numeric(arg(3))){
//		$current_semester = arg(3);
//	}else{
//		$current_semester = db_query("select nid from {node} node
//										left join {field_data_field_semester_dates} field_semester_dates on field_semester_dates.entity_type='node' and field_semester_dates.bundle='semester' and field_semester_dates.revision_id=node.vid
//										where node.type='semester' and node.status='1' and field_semester_dates.field_semester_dates_value<=:now1 and field_semester_dates.field_semester_dates_value2>=:now2 limit 0,1", array(':now1' => time(), ':now2' => time()))->fetchField();
//		$current_semester = $current_semester ? $current_semester : 0;
//	}
//
//	$html = '<form action="'.url('node/'.$node->nid.'/grades').'" method="get">
//		<div class="form-item"><label>'.t('Semester').'</label><select name="semester">';
//	if(!(isset($semesters[$current_semester]) && $semesters[$current_semester])){
//		$html .= '<option value="">'.t('Select a Semester').'</option>';
//	}
//
//	foreach($semesters as $nid => $label){
//		$selected = ($nid == $current_semester) ? 'selected="selected"' : '';
//		$html .= '<option value="'.$nid.'" '.$selected.'>'.$label.'</option>';
//	}
//	$html .= '</select></div>
//		<input type="submit" class="form-submit" value="'.t('Search').'">';
//	$html .= '</form>';

  $current_semester = $node->field_semester[LANGUAGE_NONE][0]['target_id'];
	
	if($current_semester){
		$query = db_select('node', 'node')->extend('PagerDefault');
		$query->join('field_data_field_my_courses', 'field_my_courses', "field_my_courses.entity_type='node' and field_my_courses.bundle='my_semester' and field_my_courses.revision_id=node.vid");
		$query->join('field_data_field_course', 'field_course', "field_course.entity_type='field_collection_item' and field_course.bundle='field_my_courses' and field_course.revision_id=field_my_courses.field_my_courses_revision_id");
		$query->join('field_data_field_semester', 'field_semester', "field_semester.entity_type='node' and field_semester.bundle='my_semester' and field_semester.revision_id=node.vid");
		$query->join('field_data_field_semester', 'field_semester2', "field_semester2.entity_type='node' and field_semester2.bundle='course' and field_semester2.entity_id=field_course.field_course_target_id");
		$query->join('field_data_field_user', 'field_user', "field_user.entity_type='node' and field_user.bundle='my_semester' and field_user.revision_id=node.vid");
		$query->join('users', 'users', "users.uid = field_user.field_user_target_id");
		$query->join('field_data_field_user_name', 'field_user_name', "field_user_name.entity_type='user' and field_user_name.bundle='user' and field_user_name.entity_id=users.uid");
		$query->leftJoin('grades_data', 'grades_data', "grades_data.nid=field_course.field_course_target_id and grades_data.uid=users.uid");

		$query->condition('node.type', 'my_semester');
		$query->condition('node.status', '1');
		$query->condition('users.uid', $user->uid, '!=');
		$query->condition('field_semester.field_semester_target_id', $current_semester);
		$query->condition('field_semester2.field_semester_target_id', $current_semester);
		$query->condition('field_course.field_course_target_id', $node->nid);
		
		$query->addField('users', 'uid');
		$query->addField('field_user_name', 'field_user_name_value');

		$query->orderBy('field_user_name.field_user_name_value', 'ASC');
		
		$find = $query->limit(200)->execute();
		
		$header = array(t('Student'), /*t('Examiner'), t('Date')*/);
		$header[] = t('');
		
		$rows = array();
		foreach($find as $r){
			$row = array(
				$r->field_user_name_value,
			);

			$row[] = l(t('Edit Grade'), 'node/'.$node->nid.'/grades/edit/'.$r->uid);
			$rows[] = $row;
		}
		
		$html = theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	}

	return $html;
}

function gradereg_edit_grade($form, &$form_state, $node, $account){
	$form_state['storage'] = array(
		'node' => $node,
		'account' => user_load($account->uid),
	);
	
	$grade = gradereg_load_grade($node, $account);
	
	$hm_num = (isset($node->field_number_of_homework['und'][0]['value']) && $node->field_number_of_homework['und'][0]['value'] > 0) ? $node->field_number_of_homework['und'][0]['value'] : 0;
	$quiz_num = (isset($node->field_number_of_quizzes['und'][0]['value']) && $node->field_number_of_quizzes['und'][0]['value'] > 0) ? $node->field_number_of_quizzes['und'][0]['value'] : 0;
	$finaltest = (isset($node->field_final_test['und'][0]['value']) && $node->field_final_test['und'][0]['value']) ? true : false;
	
	global $user;

  $form['title'] = array(
    '#markup' => '<h2>' . $account->field_user_name[LANGUAGE_NONE][0]['value'] . ' - ' . $node->title . '</h2>',
  );
	
	$form['homework'] = array(
		'#type' => 'fieldset',
		'#title' => t('Homework'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	for($i=0; $i<$hm_num; $i++){
		$key = 'homework_'.$i;
    $hw_grade = isset($grade['grade'][$key]) ? $grade['grade'][$key] : array();
    // if someone else already graded this item, don't show the grade
    if (!empty($hw_grade['score']) && $hw_grade['examiner_uid'] !== $user->uid) {
      $form['homework'][$key] = array(
        '#type' => 'value',
        '#default_value' => $hw_grade['score'],
      );
      $form['homework'][$key]['done'] = array(
        '#type' => 'item',
        '#title' => t('HW @num', array('@num' => ($i+1))),
        '#markup' => '<div>' . t('Already graded by someone else.') . '</div>',
      );
    }
    // if this item is ungraded or graded by me, show textbox (with grade if applicable)
    else {
      $form['homework'][$key] = array(
        '#title' => t('HW @num', array('@num' => ($i+1))),
        '#required' => false,
        '#type' => 'textfield',
        '#default_value' => isset($grade['grade'][$key]['score']) ? $grade['grade'][$key]['score'] : '',
        '#element_validate' => array('_gradereg_grade_validate'),
      );
    }
		
		$form['homework']['homework_'.$i.'_examiner'] = array(
			'#type' => 'value',
			'#default_value' => isset($grade['grade'][$key]['examiner_uid']) ? $grade['grade'][$key]['examiner_uid'] : $user->uid,
		);
	}
	
	$form['quiz'] = array(
		'#type' => 'fieldset',
		'#title' => t('Quiz'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	for($i=0; $i<$quiz_num; $i++){
		$key = 'quiz_'.$i;
    $quiz_grade = isset($grade['grade'][$key]) ? $grade['grade'][$key] : array();
    // if someone else already graded this item, don't show the grade
    if (!empty($quiz_grade['score']) && $quiz_grade['examiner_uid'] !== $user->uid) {
      $form['quiz'][$key] = array(
        '#type' => 'value',
        '#default_value' => $quiz_grade['score'],
      );
      $form['quiz'][$key]['done'] = array(
        '#type' => 'item',
        '#title' => t('Quiz @num', array('@num' => ($i+1))),
        '#markup' => '<div>' . t('Already graded by someone else.') . '</div>',
      );
    }
    // if this item is ungraded or graded by me, show textbox (with grade if applicable)
    else {
      $form['quiz'][$key] = array(
        '#title' => t('Quiz @num', array('@num' => ($i+1))),
        '#required' => false,
        '#type' => 'textfield',
        '#default_value' => isset($grade['grade'][$key]['score']) ? $grade['grade'][$key]['score'] : '',
        '#element_validate' => array('_gradereg_grade_validate'),
      );
    }

    $form['quiz']['quiz_'.$i.'_examiner'] = array(
      '#type' => 'value',
      '#default_value' => isset($grade['grade'][$key]['examiner_uid']) ? $grade['grade'][$key]['examiner_uid'] : $user->uid,
    );
	}
	
	if($finaltest){
		$key = 'finaltest_0';
    $test_grade = isset($grade['grade'][$key]) ? $grade['grade'][$key] : array();
    // if someone else already graded this item, don't show the grade
    if (!empty($test_grade['score']) && $test_grade['examiner_uid'] !== $user->uid) {
      $form[$key] = array(
        '#type' => 'value',
        '#default_value' => $test_grade['score'],
      );
      $form[$key]['done'] = array(
        '#type' => 'item',
        '#title' => t('Final Test'),
        '#markup' => '<div>' . t('Already graded by someone else.') . '</div>',
      );
    }
    // if this item is ungraded or graded by me, show textbox (with grade if applicable)
    else {
      $form[$key] = array(
        '#title' => t('Final Test'),
        '#required' => false,
        '#type' => 'textfield',
        '#default_value' => isset($grade['grade'][$key]['score']) ? $grade['grade'][$key]['score'] : '',
        '#element_validate' => array('_gradereg_grade_validate'),
      );
    }
    $form['finaltest_0_examiner'] = array(
      '#type' => 'value',
      '#default_value' => isset($grade['grade'][$key]['examiner_uid']) ? $grade['grade'][$key]['examiner_uid'] : $user->uid,
    );
	}
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	
	return $form;
}

function _gradereg_grade_validate($element, &$form_state, $form) {
  if (!empty($element['#value']) && ($element['#value'] < 80 || $element['#value'] > 100)) {
    form_error($element, t('Grades must be between 80 and 100. Please fix @item', array('@item' => $element['#title'])));
  }
}

function gradereg_edit_grade_submit($form, &$form_state){
	$node = $form_state['storage']['node'];
	$account = $form_state['storage']['account'];
	
	$hm_num = (isset($node->field_number_of_homework['und'][0]['value']) && $node->field_number_of_homework['und'][0]['value'] > 0) ? $node->field_number_of_homework['und'][0]['value'] : 0;
	$quiz_num = (isset($node->field_number_of_quizzes['und'][0]['value']) && $node->field_number_of_quizzes['und'][0]['value'] > 0) ? $node->field_number_of_quizzes['und'][0]['value'] : 0;
	$finaltest = (isset($node->field_final_test['und'][0]['value']) && $node->field_final_test['und'][0]['value']) ? true : false;

	if($hm_num){
		for($i=0; $i<$hm_num; $i++){
			$key = 'homework_'.$i;
			if(isset($form_state['values'][$key]) && is_numeric($form_state['values'][$key])){
				$examiner_uid = $form_state['values'][$key.'_examiner'];
				$exists = db_query("select score from {grades} where nid=:nid and uid=:uid and field=:field and delta=:delta", array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'homework', ':delta' => $i))->fetchField();
				if(empty($exists)){
					$data = array('nid' => $node->nid, 'uid' => $account->uid, 'field' => 'homework', 'delta' => $i, 'score' => $form_state['values'][$key], 'created' => time(), 'examiner_uid' => $examiner_uid);
					drupal_write_record('grades', $data);
				}else{
					db_query("update {grades} set score=:score, examiner_uid=:examiner_uid where nid=:nid and uid=:uid and field=:field and delta=:delta", 
								array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'homework', ':delta' => $i, ':examiner_uid' => $examiner_uid, ':score' => $form_state['values'][$key]));
				}
			}else{
				db_query("delete from {grades} where nid=:nid and uid=:uid and field=:field and delta=:delta", array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'homework', ':delta' => $i));
			}
		}
	}
	
	if($quiz_num){
		for($i=0; $i<$quiz_num; $i++){
			$key = 'quiz_'.$i;
			if(isset($form_state['values'][$key]) && is_numeric($form_state['values'][$key])){
				$examiner_uid = $form_state['values'][$key.'_examiner'];

				$exists = db_query("select score from {grades} where nid=:nid and uid=:uid and field=:field and delta=:delta", array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'quiz', ':delta' => $i))->fetchField();
				if(empty($exists)){
					$data = array('nid' => $node->nid, 'uid' => $account->uid, 'field' => 'quiz', 'delta' => $i, 'score' => $form_state['values'][$key], 'created' => time(), 'examiner_uid' => $examiner_uid);
					drupal_write_record('grades', $data);
				}else{
					db_query("update {grades} set score=:score, examiner_uid=:examiner_uid where nid=:nid and uid=:uid and field=:field and delta=:delta", 
								array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'quiz', ':delta' => $i, ':examiner_uid' => $examiner_uid, ':score' => $form_state['values'][$key]));
				}
			}else{
				db_query("delete from {grades} where nid=:nid and uid=:uid and field=:field and delta=:delta", array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'quiz', ':delta' => $i));
			}
		}
	}
	
	if($finaltest && isset($form_state['values']['finaltest_0']) && is_numeric($form_state['values']['finaltest_0'])){
		$key = 'finaltest_0';
		$examiner_uid = $form_state['values'][$key.'_examiner'];
		
		$exists = db_query("select score from {grades} where nid=:nid and uid=:uid and field=:field and delta=:delta", array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'finaltest', ':delta' => 0))->fetchField();
		if(empty($exists)){
			$data = array('nid' => $node->nid, 'uid' => $account->uid, 'field' => 'finaltest', 'delta' => 0, 'score' => $form_state['values'][$key], 'created' => time(), 'examiner_uid' => $examiner_uid);
			drupal_write_record('grades', $data);
		}else{
			db_query("update {grades} set score=:score, examiner_uid=:examiner_uid where nid=:nid and uid=:uid and field=:field and delta=:delta", 
						array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'finaltest', ':delta' => 0, ':examiner_uid' => $examiner_uid, ':score' => $form_state['values'][$key]));
		}
	}else{
		db_query("delete from {grades} where nid=:nid and uid=:uid and field=:field and delta=:delta", array(':nid' => $node->nid, ':uid' => $account->uid, ':field' => 'finaltest', ':delta' => 0));
		}

  gradereg_update_grades_data($node->nid, $account->uid);
	
	unset($form_state['storage']);
	drupal_set_message(t('The grades have been saved'));
	$form_state['redirect'] = 'node/'.$node->nid.'/grades/'.$node->field_semester['und'][0]['target_id'];
}

/**
 * @param $nid (course nid)
 * @param $uid (user id)
 */
function gradereg_update_grades_data($nid, $uid) {
  // delete old data
  db_query("delete from {grades_data} where nid=:nid and uid=:uid", array(':uid' => $uid, ':nid' => $nid));

  // get homework average
  $hw = db_query("select avg(score) from {grades} where nid=:nid and uid=:uid and field=:field", array(':nid' => $nid, ':uid' => $uid, ':field' => 'homework'))->fetchField();
  $data = array(
    'nid' => $nid,
    'uid' => $uid,
    'homework_avg' => $hw,
  );

  // get quiz average
  $quiz = db_query("select avg(score) from {grades} where nid=:nid and uid=:uid and field=:field", array(':nid' => $nid, ':uid' => $uid, ':field' => 'quiz'))->fetchField();
  $data['quiz_avg'] = $quiz;

  // get test score
  $finaltest_score = db_query("select avg(score) from {grades} where nid=:nid and uid=:uid and field=:field", array(':nid' => $nid, ':uid' => $uid, ':field' => 'finaltest'))->fetchField();
  $data['finaltest_avg'] = $finaltest_score;

  // write updated data
  drupal_write_record('grades_data', $data);
}

function gradereg_user_grades_list($account){
	if(isset($_GET['export']) && $_GET['export']){
		return gradereg_user_grades_list_export($account);
	}

	$semesters = array();
	$semester_query = db_query("select * from {node} where type='semester' and status='1' order by created desc");
	foreach($semester_query as $r){
		$semesters[$r->nid] = $r->title;
	}
	
	if(isset($_GET['semester']) && $_GET['semester']){
		$current_semester = $_GET['semester'];
	}else if(arg(3) && is_numeric(arg(3))){
		$current_semester = arg(3);
	}else{
		$current_semester = db_query("select nid from {node} node
										left join {field_data_field_semester_dates} field_semester_dates on field_semester_dates.entity_type='node' and field_semester_dates.bundle='semester' and field_semester_dates.revision_id=node.vid
										where node.type='semester' and node.status='1' and field_semester_dates.field_semester_dates_value<=:now1 and field_semester_dates.field_semester_dates_value2>=:now2 limit 0,1", array(':now1' => time(), ':now2' => time()))->fetchField();
		$current_semester = $current_semester ? $current_semester : 0;
	}
	
	$hide_examiner = (isset($_GET['hide_examiner']) && $_GET['hide_examiner']) ? true : false;
	
	$html = '<form action="'.url('user/'.$account->uid.'/grades').'" method="get">
		<div class="form-item"><label>'.t('Semester').'</label><select name="semester">';
	if(!(isset($semesters[$current_semester]) && $semesters[$current_semester])){
		$html .= '<option value="">'.t('Select a Semester').'</option>';
	}
		
	foreach($semesters as $nid => $label){
		$selected = ($nid == $current_semester) ? 'selected="selected"' : '';
		$html .= '<option value="'.$nid.'" '.$selected.'>'.$label.'</option>';
	}
	$html .= '</select></div>
		<div class="form-item"><label><input type="checkbox" name="hide_examiner" '.($hide_examiner ? 'checked="checked"' : '').'> '.t('Hide Examiner').'</label></div>
		<input type="submit" class="form-submit" value="'.t('Search').'">';
	if($current_semester){
		$html .= '<input type="submit" class="form-submit" value="'.t('Export').'" name="export">';
	}
	$html .= '</form>';
	
	
	if($current_semester){
		$query = db_select('node', 'node')->extend('PagerDefault');
		$query->join('field_data_field_my_courses', 'field_my_courses', "field_my_courses.entity_type='node' and field_my_courses.bundle='my_semester' and field_my_courses.revision_id=node.vid");
		$query->join('field_data_field_course', 'field_course', "field_course.entity_type='field_collection_item' and field_course.bundle='field_my_courses' and field_course.revision_id=field_my_courses.field_my_courses_revision_id");
		$query->join('field_data_field_semester', 'field_semester', "field_semester.entity_type='node' and field_semester.bundle='my_semester' and field_semester.revision_id=node.vid");
		$query->join('field_data_field_semester', 'field_semester2', "field_semester2.entity_type='node' and field_semester2.bundle='course' and field_semester2.entity_id=field_course.field_course_target_id");
		$query->join('node', 'course', "course.nid=field_course.field_course_target_id");
		$query->join('field_data_field_user', 'field_user', "field_user.entity_type='node' and field_user.bundle='my_semester' and field_user.revision_id=node.vid");
		$query->join('users', 'users', "users.uid = field_user.field_user_target_id");
		$query->join('field_data_field_user_name', 'field_user_name', "field_user_name.entity_type='user' and field_user_name.bundle='user' and field_user_name.entity_id=users.uid");
		$query->leftJoin('grades_data', 'grades_data', "grades_data.nid=field_course.field_course_target_id and grades_data.uid=users.uid");

		$query->condition('node.type', 'my_semester');
		$query->condition('node.status', '1');
		$query->condition('field_semester.field_semester_target_id', $current_semester);
		$query->condition('field_semester2.field_semester_target_id', $current_semester);
		$query->condition('users.uid', $account->uid);
		
		$query->addField('course', 'nid');
		$query->addField('course', 'title');
		$query->addField('field_user_name', 'field_user_name_value');
		
		$query->orderBy('course.title', 'ASC');
		
		$find = $query->limit(20)->execute();
		
		$header = array(t('Course'));
		
		for($i=0; $i<20; $i++){
			if(!$hide_examiner){
				$header[] = t('Examiner');
				$header[] = t('Date');
			}
			$header[] = t('HW @num', array('@num' => ($i+1)));
			if($i<15){
				if(!$hide_examiner){
					$header[] = t('Examiner');
					$header[] = t('Date');
				}
				$header[] = t('Quiz @num', array('@num' => ($i+1)));
			}
		}
		$header[] = t('Final Test');
		if(!$hide_examiner){
			$header[] = t('Examiner');
			$header[] = t('Date');
		}
		
		$rows = array();
		foreach($find as $r){
			$row = array(
				l($r->title, 'node/'.$r->nid),
			);
			
			$grade = array();
			$query = db_query("select grades.*,examiner_field_user_name.field_user_name_value as examiner_name from {grades} grades
									left join {field_data_field_user_name} examiner_field_user_name on examiner_field_user_name.entity_type='user' and examiner_field_user_name.bundle='user' and examiner_field_user_name.entity_id=grades.examiner_uid
									where nid=:nid and uid=:uid order by field asc, delta asc", array(':uid' => $account->uid, ':nid' => $r->nid));
			foreach($query as $r2){
				$grade[$r2->field.'_'.$r2->delta] = $r2->score;
				$grade[$r2->field.'_'.$r2->delta.'_examiner'] = $r2->examiner_uid ? $r2->examiner_name : '';
				$grade[$r2->field.'_'.$r2->delta.'_date'] = $r2->created ? date('d.m.Y', $r2->created) : '';
			}
			for($i=0; $i<20; $i++){
				if(isset($grade['homework_'.$i])){
					if(!$hide_examiner){
						$row[] = $grade['homework_'.$i.'_examiner'];
						$row[] = $grade['homework_'.$i.'_date'];
					}
					$row[] = $grade['homework_'.$i];
				}else{
          if(!$hide_examiner){
					  $row[] = '';
					  $row[] = '';
          }
					$row[] = '';
				}
				
				if($i<15){
					if(isset($grade['quiz_'.$i])){
						if(!$hide_examiner){
							$row[] = $grade['quiz_'.$i.'_examiner'];
							$row[] = $grade['quiz_'.$i.'_date'];
						}
						$row[] = $grade['quiz_'.$i];
					}else{
            if(!$hide_examiner){
						  $row[] = '';
						  $row[] = '';
            }
						$row[] = '';
					}
				}
			}
			
			if(isset($grade['finaltest_0'])){
				if(!$hide_examiner){
					$row[] = $grade['finaltest_0_examiner'];
					$row[] = $grade['finaltest_0_date'];
				}
				$row[] = $grade['finaltest_0'];
			}else{
        if(!$hide_examiner){
			  	$row[] = '';
				  $row[] = '';
        }
        $row[] = '';
			}
			
			$rows[] = $row;
		}
		
		$newtable = _gradereg_rearrange_table($header, $rows);
		$html .= theme('table', array('header' => $newtable['header'], 'rows' => $newtable['rows'])).theme('pager');
	}

	return $html;
}

function _gradereg_rearrange_table($header, $rows){
	$table = array_merge(array($header), $rows);
	$rowcount = 1+count($rows);
	$colcount = count($header);
	
	$newheader = array();
	$newrows = array();
	for($i=0; $i<$rowcount; $i++){
		$newheader[$i] = $table[$i][0];
		
		for($j=1; $j<$colcount; $j++){
			if(!isset($newrows[$j])){
				$newrows[$j] = array();
			}
			$newrows[$j][$i] = $table[$i][$j];
		}
	}
	
	return array('header' => $newheader, 'rows' => $newrows);
}

function gradereg_user_grades_list_export($account){

	if(isset($_GET['semester']) && $_GET['semester']){
		$current_semester = $_GET['semester'];
	}else if(arg(3) && is_numeric(arg(3))){
		$current_semester = arg(3);
	}else{
		$current_semester = db_query("select nid from {node} node
										left join {field_data_field_semester_dates} field_semester_dates on field_semester_dates.entity_type='node' and field_semester_dates.bundle='semester' and field_semester_dates.revision_id=node.vid
										where node.type='semester' and node.status='1' and field_semester_dates.field_semester_dates_value<=:now1 and field_semester_dates.field_semester_dates_value2>=:now2 limit 0,1", array(':now1' => time(), ':now2' => time()))->fetchField();
		$current_semester = $current_semester ? $current_semester : 0;
	}
	
	if($current_semester){
		$hide_examiner = (isset($_GET['hide_examiner']) && $_GET['hide_examiner']) ? true : false;
	
		$query = db_select('node', 'node');
		$query->join('field_data_field_my_courses', 'field_my_courses', "field_my_courses.entity_type='node' and field_my_courses.bundle='my_semester' and field_my_courses.revision_id=node.vid");
		$query->join('field_data_field_course', 'field_course', "field_course.entity_type='field_collection_item' and field_course.bundle='field_my_courses' and field_course.revision_id=field_my_courses.field_my_courses_revision_id");
		$query->join('field_data_field_semester', 'field_semester', "field_semester.entity_type='node' and field_semester.bundle='my_semester' and field_semester.revision_id=node.vid");
		$query->join('field_data_field_semester', 'field_semester2', "field_semester2.entity_type='node' and field_semester2.bundle='course' and field_semester2.entity_id=field_course.field_course_target_id");
		$query->join('node', 'course', "course.nid=field_course.field_course_target_id");
		$query->join('field_data_field_user', 'field_user', "field_user.entity_type='node' and field_user.bundle='my_semester' and field_user.revision_id=node.vid");
		$query->join('users', 'users', "users.uid = field_user.field_user_target_id");
		$query->join('field_data_field_user_name', 'field_user_name', "field_user_name.entity_type='user' and field_user_name.bundle='user' and field_user_name.entity_id=users.uid");
		$query->leftJoin('grades_data', 'grades_data', "grades_data.nid=field_course.field_course_target_id and grades_data.uid=users.uid");
		//$query->leftJoin('field_data_field_user_name', 'examiner_field_user_name', "examiner_field_user_name.entity_type='user' and examiner_field_user_name.bundle='user' and examiner_field_user_name.entity_id=grades_data.examiner_uid");
		
		$query->condition('node.type', 'my_semester');
		$query->condition('node.status', '1');
		$query->condition('field_semester.field_semester_target_id', $current_semester);
		$query->condition('field_semester2.field_semester_target_id', $current_semester);
		$query->condition('users.uid', $account->uid);
		
		$query->addField('course', 'nid');
		$query->addField('course', 'title');
		$query->addField('field_user_name', 'field_user_name_value');
		//$query->addField('grades_data', 'created');
		//$query->addField('grades_data', 'examiner_uid', 'examiner_uid');
		//$query->addField('examiner_field_user_name', 'field_user_name_value', 'examiner_name');
		
		$query->orderBy('course.title', 'ASC');
		
		$find = $query->execute();
		
		$hm_num = (isset($node->field_number_of_homework['und'][0]['value']) && $node->field_number_of_homework['und'][0]['value'] > 0) ? $node->field_number_of_homework['und'][0]['value'] : 0;
		$quiz_num = (isset($node->field_number_of_quizzes['und'][0]['value']) && $node->field_number_of_quizzes['und'][0]['value'] > 0) ? $node->field_number_of_quizzes['und'][0]['value'] : 0;
		$finaltest = (isset($node->field_final_test['und'][0]['value']) && $node->field_final_test['und'][0]['value']) ? true : false;
		$header = array(t('Course'));
		
		for($i=0; $i<20; $i++){
			if(!$hide_examiner){
				$header[] = t('Examiner');
				$header[] = t('Date');
			}
			$header[] = t('HW'.($i+1));
			if($i<15){
				if(!$hide_examiner){
					$header[] = t('Examiner');
					$header[] = t('Date');
				}
				$header[] = t('Q'.($i+1));
			}
		}
		$header[] = t('Final Test');
		if(!$hide_examiner){
			$header[] = t('Examiner');
			$header[] = t('Date');
		}
		
		//$filename = variable_get('file_temporary_path', '').'/'.time().'-'.rand(1, 1000).'.csv';
		//$fp = fopen($filename, 'w');
		//fputcsv($fp, $header);
	
		$rows = array();
		foreach($find as $r){
			$row = array(
				$r->title,
			);
			
			$grade = array();
			$query = db_query("select grades.*,examiner_field_user_name.field_user_name_value as examiner_name from {grades} grades
									left join {field_data_field_user_name} examiner_field_user_name on examiner_field_user_name.entity_type='user' and examiner_field_user_name.bundle='user' and examiner_field_user_name.entity_id=grades.examiner_uid
									where nid=:nid and uid=:uid order by field asc, delta asc", array(':uid' => $account->uid, ':nid' => $r->nid));
			foreach($query as $r2){
				$grade[$r2->field.'_'.$r2->delta] = $r2->score;
				$grade[$r2->field.'_'.$r2->delta.'_examiner'] = $r2->examiner_uid ? $r2->examiner_name : '';
				$grade[$r2->field.'_'.$r2->delta.'_date'] = $r2->created ? date('Y-m-d H:i:s', $r2->created) : '';
			}
			for($i=0; $i<20; $i++){
				if(isset($grade['homework_'.$i])){
					if(!$hide_examiner){
						$row[] = $grade['homework_'.$i.'_examiner'];
						$row[] = $grade['homework_'.$i.'_date'];
					}
					$row[] = $grade['homework_'.$i];
				}else{
					$row[] = '';
					$row[] = '';
					$row[] = '';
				}
				
				if($i<15){
					if(isset($grade['quiz_'.$i])){
						if(!$hide_examiner){
							$row[] = $grade['quiz_'.$i.'_examiner'];
							$row[] = $grade['quiz_'.$i.'_date'];
						}
						$row[] = $grade['quiz_'.$i];
					}else{
						$row[] = '';
						$row[] = '';
						$row[] = '';
					}
				}
			}
			
			if(isset($grade['finaltest_0'])){
				if(!$hide_examiner){
					$row[] = $grade['finaltest_0_examiner'];
					$row[] = $grade['finaltest_0_date'];
				}
				$row[] = $grade['finaltest_0'];
			}else{
				$row[] = '';
				$row[] = '';
				$row[] = '';
			}
			
			$rows[] = $row;
			//fputcsv($fp, $row);
		}
		
		//fclose($fp);
		
		$filename = variable_get('file_temporary_path', '').'/'.time().'-'.rand(1, 1000).'.xls';
		$newtable = _gradereg_rearrange_table($header, $rows);
		gradereg_export_excel($filename, $newtable['header'], $newtable['rows']);
		
		header("Content-type: application/octet-stream");
		Header("Accept-Length: ".filesize($filename));
		header("Content-Disposition: attachment; filename=export.xls");
		readfile($filename);
		unlink($filename);
	}else{
		drupal_not_found();
		return;
	}
}