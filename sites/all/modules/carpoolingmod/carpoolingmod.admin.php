<?php

function carpoolingmod_pref_setup_page(){
	global $user;

	return drupal_get_form('carpoolingmod_pref_setup_form', $user);
}

function carpoolingmod_pref_setup_form($form, &$form_status, $account){
	
	$form_status['storage']['account'] = $account;
	
	$data = carpoolingmod_load_pref($account);
	$data = $data ? $data : array();
	
	$opts = array(
		'offer' => t('By car'),
		'lookfor' => t('Looking for a ride'),
		'none' => t('Neither'),
	);
	
	$form['type'] = array(
		'#type' => 'radios',
		'#title' => t('How would you arrive to Moa?'),
		'#options' => $opts,
		'#required' => true,
		'#default_value' => isset($data['type']) ? $data['type'] : '',
		'#ajax' => array(
		  'callback' => 'carpoolingmod_ajax_type_callback',
		  'wrapper' => 'type-div',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
  $form['checkboxes_fieldset'] = array(
    // The prefix/suffix provide the div that we're replacing, named by
    // #ajax['wrapper'] above.
    '#prefix' => '<div id="type-div">',
    '#suffix' => '</div>',
    '#type' => 'container',
  );
  
	if(isset($form_status['values']['type'])){
		$data['type'] = $form_status['values']['type'];
	}
  
	if(isset($data['type']) && $data['type'] == 'offer'){
		$opts = array(
			'offer' => t('By car'),
			'lookfor' => t('Looking for a ride'),
			'none' => t('Neither'),
		);
		
		$seatopts = array(0 => t('Select'));
		for($i=1; $i<=9; $i++){
			$seatopts[$i] = $i;
		}
		
		$form['checkboxes_fieldset']['available_seats'] = array(
			'#type' => 'select',
			'#title' => t('Available seats'),
			'#options' => $seatopts,
			'#required' => true,
			'#default_value' => isset($data['available_seats']) ? $data['available_seats'] : 0,
		);
	}
	
	$locopts = array('' => t('Select'));
	$vid = variable_get('carpoolingmod_location_vid', 1);
	$terms = taxonomy_get_tree($vid);
	foreach($terms as $t){
		$locopts[$t->tid] = $t->name;
	}
	
	$form['location'] = array(
		'#type' => 'select',
		'#title' => t('Your geographic location'),
		'#required' => true,
		'#options' => $locopts,
		'#default_value' => isset($data['location']) ? $data['location'] : '',
	);
	
	$form['departure'] = array(
		'#type' => 'date_select',
		'#date_format' => 'Y-m-d H:i',
		'#title' => t('Your departure date'),
		'#required' => true,
		'#default_value' => isset($data['departure']) ? $data['departure'] : '',
		'#default_value' => date('Y-m-d H:i'),
	);
	
	$form['returndate'] = array(
		'#type' => 'date_select',
		'#date_format' => 'Y-m-d H:i',
		'#title' => t('Your return date'),
		'#required' => true,
		'#default_value' => isset($data['returndate']) ? $data['returndate'] : '',
		'#default_value' => date('Y-m-d H:i'),
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	
	return $form;
}

function carpoolingmod_pref_setup_form_validate($form, &$form_status){
	$values = $form_status['values'];
	$departure = strtotime($values['departure']);
	$returndate = strtotime($values['returndate']);
	
	if($departure > $returndate){
		form_set_error('returndate', t('Departure date can not be later than return date'));
	}
}

function carpoolingmod_pref_setup_form_submit($form, &$form_status){
	$account = $form_status['storage']['account'];
	$data = carpoolingmod_load_pref($account);
	$values = $form_status['values'];
	
	$departure = strtotime($values['departure']);
	$returndate = strtotime($values['returndate']);
	
	if($data){
		$data = array(
			'uid' => $account->uid,
			'type' => $values['type'],
			'available_seats' => isset($values['available_seats']) ? $values['available_seats'] : 0,
			'location' => $values['location'],
			'departure' => $departure,
			'returndate' => $returndate,
		);
		
		drupal_write_record('carpooling_pref', $data, 'uid');
		drupal_set_message(t('Your car pooling preference has been updated.'));
	}else{
		$data = array(
			'uid' => $account->uid,
			'type' => $values['type'],
			'available_seats' => isset($values['available_seats']) ? $values['available_seats'] : 0,
			'remaining_seats' => isset($values['available_seats']) ? $values['available_seats'] : 0,
			'location' => $values['location'],
			'departure' => $departure,
			'returndate' => $returndate,
		);
		
		drupal_write_record('carpooling_pref', $data);
		drupal_set_message(t('Your car pooling preference has been saved.'));
	}
	
	unset($form_status['storage']);
}

function carpoolingmod_ajax_type_callback($form, $form_state){
	return $form['checkboxes_fieldset'];
}

function carpoolingmod_myrides_page(){
	global $user;

	$html = '';
	$html .= render(drupal_get_form('carpoolingmod_pref_setup_form', $user));
	
	$data = carpoolingmod_load_pref($user);
	if($data && $data['type'] == 'offer'){
		$html .= '<fieldset class="form-wrapper"><legend><span class="fieldset-legend">'.t('List of passengers riding with you').'</span></legend><div class="fieldset-wrapper">';
		
		$query = db_query("select * from {carpooling_ride} where offer_uid=:uid order by created asc", array(':uid' => $user->uid));
		$header = array('', t('Email'), t('Phone'), t('Name'));
		$rows = array();
		foreach($query as $r){
			$account = user_load($r->join_uid);
			$rows[] = array(
				l(t('Delete passenger'), 'carpool/removemycar/'.$account->uid),
				$account->mail,
				isset($account->field_user_phone['und'][0]['value']) ? $account->field_user_phone['und'][0]['value'] : '',
				isset($account->field_user_name['und'][0]['value']) ? $account->field_user_name['und'][0]['value'] : '',
			);
		}

		$html .= theme('table', array('header' => $header, 'rows' => $rows));
		$html .= '</div></div>';
	}else if($data && $data['type'] == 'lookfor'){
		$html .= '<fieldset class="form-wrapper"><legend><span class="fieldset-legend">'.t('Your driver details').'</span></legend><div class="fieldset-wrapper">';
		
		$query = db_query("select * from {carpooling_ride} where join_uid=:uid order by created asc", array(':uid' => $user->uid));
		$header = array('', t('Email'), t('Phone'), t('Name'));
		$rows = array();
		foreach($query as $r){
			$account = user_load($r->offer_uid);
			$rows[] = array(
				l(t('Remove myself from this ride'), 'carpool/leave/'.$account->uid),
				$account->mail,
				isset($account->field_user_phone['und'][0]['value']) ? $account->field_user_phone['und'][0]['value'] : '',
				isset($account->field_user_name['und'][0]['value']) ? $account->field_user_name['und'][0]['value'] : '',
			);
		}

		$html .= theme('table', array('header' => $header, 'rows' => $rows));
		$html .= '</div></div>';
	}
	
	return $html;	
}

function carpoolingmod_removemycar_ride_form($form, &$form_status, $account){
	$form_status['storage'] = array('account' => $account);
	
	return confirm_form($form, t("Do you want to remove !user from your car?", 
									array('!user' => l($account->name, 'user/'.$account->uid))), 
			'MyRides');
}

function carpoolingmod_removemycar_ride_form_submit($form, &$form_status){
	$account = $form_status['storage']['account'];
	global $user;
	db_query("delete from {carpooling_ride} where join_uid=:join_uid and offer_uid=:offer_uid", array(':join_uid' => $account->uid, ':offer_uid' => $user->uid));
	
	db_query("update {carpooling_pref} set remaining_seats=remaining_seats+1 where uid=:uid", array(':uid' => $user->uid));
	
	drupal_set_message(t('You have removed !user from your car.', array('!user' => l($account->name, 'user/'.$account->uid))));
	unset($form_status['storage']);
	$form_status['redirect'] = 'MyRides';
}

function carpoolingmod_leave_ride_form($form, &$form_status, $account){
	$form_status['storage'] = array('account' => $account);
	
	return confirm_form($form, t("Do you want to leave !user's ride?", 
									array('!user' => l($account->name, 'user/'.$account->uid))), 
			'MyRides');
}

function carpoolingmod_leave_ride_form_submit($form, &$form_status){
	$account = $form_status['storage']['account'];
	global $user;
	db_query("delete from {carpooling_ride} where join_uid=:join_uid and offer_uid=:offer_uid", array(':join_uid' => $user->uid, ':offer_uid' => $account->uid));
	
	db_query("update {carpooling_pref} set remaining_seats=remaining_seats+1 where uid=:uid", array(':uid' => $account->uid));
	
	drupal_set_message(t("You have leave !user's ride.", array('!user' => l($account->name, 'user/'.$account->uid))));
	unset($form_status['storage']);
	$form_status['redirect'] = 'MyRides';
}