<?php

function gradereg_course_list(){
	$semesters = array();
	$semester_query = db_query("select * from {node} where type='semester' and status='1' order by created desc");
	foreach($semester_query as $r){
		$semesters[$r->nid] = $r->title;
	}

	if(isset($_GET['semester']) && $_GET['semester']){
		$current_semester = $_GET['semester'];
	}
  else if(arg(3) && is_numeric(arg(3))){
		$current_semester = arg(3);
	}
  else {
    $current_semester = _arava_admin_get_default_semester();
  }
	
	$html = '<form action="'.url('admin/people/grade-courses').'" method="get">
		<div class="form-item"><label>'.t('Semester').'</label><select name="semester">';
	if(!(isset($semesters[$current_semester]) && $semesters[$current_semester])){
		$html .= '<option value="">'.t('Select a Semester').'</option>';
	}
		
	foreach($semesters as $nid => $label){
		$selected = ($nid == $current_semester) ? 'selected="selected"' : '';
		$html .= '<option value="'.$nid.'" '.$selected.'>'.$label.'</option>';
	}
	$html .= '</select></div>
		<input type="submit" class="form-submit" value="'.t('Search').'">';
	$html .= '</form>';
	
	if($current_semester && is_numeric($current_semester)){
		$query = db_select('node', 'node')->extend('PagerDefault');
    $query->join('field_data_field_semester', 'semester' , 'node.nid = semester.entity_id');

		$query->condition('node.type', 'course');
		$query->condition('node.status', '1');
    $query->condition('semester.field_semester_target_id', $current_semester);
		
		$query->addField('node', 'nid');
		$query->addField('node', 'title');
		
		$query->orderBy('node.title', 'ASC');
		
		$find = $query->limit(50)->execute();
		$header = array(t('Course'), t('HW Completed'), t('Quiz Completed'), t('Final Test Completed'), '');
		$rows = array();
		foreach($find as $r){
			$row = array(
				l($r->title, 'node/'.$r->nid),
			);
			
			$node = node_load($r->nid);
			$hm_num = (isset($node->field_number_of_homework['und'][0]['value']) && $node->field_number_of_homework['und'][0]['value'] > 0) ? $node->field_number_of_homework['und'][0]['value'] : 0;
			$quiz_num = (isset($node->field_number_of_quizzes['und'][0]['value']) && $node->field_number_of_quizzes['und'][0]['value'] > 0) ? $node->field_number_of_quizzes['und'][0]['value'] : 0;
			$finaltest = (isset($node->field_final_test['und'][0]['value']) && $node->field_final_test['und'][0]['value']) ? true : false;
			
			$total_num = db_query("select count(*) as num from {node} node
										inner join {field_data_field_my_courses} field_my_courses on field_my_courses.entity_type='node' and field_my_courses.bundle='my_semester' and field_my_courses.revision_id=node.vid
										inner join {field_data_field_course} field_course on field_course.entity_type='field_collection_item' and field_course.bundle='field_my_courses' and field_course.revision_id=field_my_courses.field_my_courses_revision_id
										inner join {field_data_field_semester} field_semester on field_semester.entity_type='node' and field_semester.bundle='my_semester' and field_semester.entity_id=node.vid
										where node.type='my_semester' and node.status='1' and field_course.field_course_target_id=".$r->nid." and field_semester.field_semester_target_id=".$current_semester)->fetchField();
			
			if($hm_num && $total_num){
				$total_hw = db_query("select count(*) from {grades} where field='homework' and nid='$r->nid'")->fetchField();
				$row[] = number_format(100*$total_hw/($total_num*$hm_num), 2).'%';
			}else if($hm_num){
				$row[] = '0.00%';
			}else{
				$row[] = '';
			}
			
			
			if($quiz_num && $total_num){
				$total_quiz = db_query("select count(*) from {grades} where field='quiz' and nid='$r->nid'")->fetchField();
				$row[] = number_format(100*$total_quiz/($total_num*$quiz_num), 2).'%';
			}else if($quiz_num){
				$row[] = '0.00%';
			}else{
				$row[] = '';
			}
			
			if($finaltest && $total_num){
				$total_ft = db_query("select count(*) from {grades} where field='finaltest' and nid='$r->nid'")->fetchField();
				$row[] = number_format(100*$total_ft/$total_num, 2).'%';
			}else if($finaltest){
				$row[] = '0.00%';
			}else{
				$row[] = '';
			}
			
			$row[] = l(t('Edit Course'), 'node/'.$r->nid.'/edit').' | '.l(t('Export'), 'admin/people/grade-courses/'.$r->nid.'/export');
			$rows[] = $row;
		}
		
		$html .= theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	}
	
	return $html;
}

function gradereg_course_export($node){
	$current_semester = $node->field_semester['und'][0]['target_id'];
	
	$query = db_select('node', 'node');
	$query->join('field_data_field_my_courses', 'field_my_courses', "field_my_courses.entity_type='node' and field_my_courses.bundle='my_semester' and field_my_courses.revision_id=node.vid");
	$query->join('field_data_field_course', 'field_course', "field_course.entity_type='field_collection_item' and field_course.bundle='field_my_courses' and field_course.revision_id=field_my_courses.field_my_courses_revision_id");
	$query->join('field_data_field_semester', 'field_semester', "field_semester.entity_type='node' and field_semester.bundle='my_semester' and field_semester.revision_id=node.vid");
	$query->join('field_data_field_semester', 'field_semester2', "field_semester2.entity_type='node' and field_semester2.bundle='course' and field_semester2.entity_id=field_course.field_course_target_id");
	$query->join('field_data_field_user', 'field_user', "field_user.entity_type='node' and field_user.bundle='my_semester' and field_user.revision_id=node.vid");
	$query->join('users', 'users', "users.uid = field_user.field_user_target_id");
	$query->join('field_data_field_user_name', 'field_user_name', "field_user_name.entity_type='user' and field_user_name.bundle='user' and field_user_name.entity_id=users.uid");
	$query->leftJoin('grades_data', 'grades_data', "grades_data.nid=field_course.field_course_target_id and grades_data.uid=users.uid");
	//$query->leftJoin('field_data_field_user_name', 'examiner_field_user_name', "examiner_field_user_name.entity_type='user' and examiner_field_user_name.bundle='user' and examiner_field_user_name.entity_id=grades_data.examiner_uid");
	
	$query->condition('node.type', 'my_semester');
	$query->condition('node.status', '1');
	$query->condition('field_semester.field_semester_target_id', $current_semester);
	$query->condition('field_semester2.field_semester_target_id', $current_semester);
	$query->condition('field_course.field_course_target_id', $node->nid);
	
	$query->addField('users', 'uid');
	$query->addField('field_user_name', 'field_user_name_value');
	//$query->addField('grades_data', 'created');
	//$query->addField('grades_data', 'examiner_uid', 'examiner_uid');
	//$query->addField('examiner_field_user_name', 'field_user_name_value', 'examiner_name');
	
	$query->orderBy('field_user_name.field_user_name_value', 'ASC');
	$find = $query->execute();
	
	//$filename = variable_get('file_temporary_path', '').'/'.time().'-'.rand(1, 1000).'.csv';
	//$fp = fopen($filename, 'w');
	$header = array(t('Student'));
	
	$hm_num = (isset($node->field_number_of_homework['und'][0]['value']) && $node->field_number_of_homework['und'][0]['value'] > 0) ? $node->field_number_of_homework['und'][0]['value'] : 0;
	$quiz_num = (isset($node->field_number_of_quizzes['und'][0]['value']) && $node->field_number_of_quizzes['und'][0]['value'] > 0) ? $node->field_number_of_quizzes['und'][0]['value'] : 0;
	$finaltest = (isset($node->field_final_test['und'][0]['value']) && $node->field_final_test['und'][0]['value']) ? true : false;
	
	for($i=0; $i<$hm_num; $i++){
		$header[] = t('Examiner');
		$header[] = t('Date');
		$header[] = t('HW'.($i+1));
		if($i<$quiz_num){
			$header[] = t('Examiner');
			$header[] = t('Date');
			$header[] = t('Q'.($i+1));
		}
	}
	if($finaltest){
		$header[] = t('Examiner');
		$header[] = t('Date');
		$header[] = t('Final Test');
	}
	
	$rows = array();
	foreach($find as $r){
		$row = array(
			$r->field_user_name_value,
			//$r->examiner_name,
			//$r->created ? date('Y-m-d h:i:s', $r->created) : '',
		);
		
		$grade = array();
		$query = db_query("select grades.*,examiner_field_user_name.field_user_name_value as examiner_name from {grades} grades
								left join {field_data_field_user_name} examiner_field_user_name on examiner_field_user_name.entity_type='user' and examiner_field_user_name.bundle='user' and examiner_field_user_name.entity_id=grades.examiner_uid
								where nid=:nid and uid=:uid order by field asc, delta asc", array(':uid' => $r->uid, ':nid' => $node->nid));
		foreach($query as $r2){
			$grade[$r2->field.'_'.$r2->delta] = $r2->score;
			$grade[$r2->field.'_'.$r2->delta.'_examiner'] = $r2->examiner_uid ? $r2->examiner_name : '';
			$grade[$r2->field.'_'.$r2->delta.'_date'] = $r2->created ? date('Y-m-d H:i:s', $r2->created) : '';
		}
		for($i=0; $i<$hm_num; $i++){
			if(isset($grade['homework_'.$i])){
				$row[] = $grade['homework_'.$i.'_examiner'];
				$row[] = $grade['homework_'.$i.'_date'];
				$row[] = $grade['homework_'.$i];
			}else{
				$row[] = '';
				$row[] = '';
				$row[] = '';
			}
			
			if($i<$quiz_num){
				if(isset($grade['quiz_'.$i])){
					$row[] = $grade['quiz_'.$i.'_examiner'];
					$row[] = $grade['quiz_'.$i.'_date'];
					$row[] = $grade['quiz_'.$i];
				}else{
					$row[] = '';
					$row[] = '';
					$row[] = '';
				}
			}
		}
		
		if($finaltest){
			$row[] = isset($grade['finaltest_0_examiner']) ? $grade['finaltest_0_examiner'] : '';
			$row[] = isset($grade['finaltest_0_date']) ? $grade['finaltest_0_date'] : '';
			$row[] = isset($grade['finaltest_0']) ? $grade['finaltest_0'] : '';
		}else{
			$row[] = '';
			$row[] = '';
			$row[] = '';
		}
		
		//fputcsv($fp, $line);
		$rows[] = $row;
	}
	//fclose($fp);
	
	$filename = variable_get('file_temporary_path', '').'/'.time().'-'.rand(1, 1000).'.xls';
	gradereg_export_excel($filename, $header, $rows);
	
	header("Content-type: application/octet-stream");
	Header("Accept-Length: ".filesize($filename));
	header("Content-Disposition: attachment; filename=export.xls");
	readfile($filename);
	unlink($filename);
}
