<?php

function carpoolingmod_update_position_page(){
	if(isset($_POST['catalog-weight']) && $_POST['catalog-weight']){
		$term_index = 0;
		foreach($_POST['catalog-weight'] as $tid => $terms_weight){
			$term = taxonomy_term_load($tid);
			$term->field_weight['und'][0]['value'] = $term_index;
			taxonomy_term_save($term);
			
			$node_index = 0;
			foreach($terms_weight as $nid){
				$node = node_load($nid);
				$node->field_weight['und'][0]['value'] = $node_index;
				node_save($node);
				
				$node_index++;
			}
			
			$term_index++;
		}
	}
	
	drupal_set_message(t('The position has been saved'));
	drupal_goto('Catalog');
}

function carpoolingmod_pref_setup_page(){
	global $user;

	return drupal_get_form('carpoolingmod_pref_setup_form', $user, 'registration/meals');
}

function carpoolingmod_pref_setup_form($form, &$form_status, $account, $redirect = ''){
	
	$form_status['storage']['account'] = $account;
	$form_status['storage']['redirect'] = $redirect;
	
	$data = carpoolingmod_load_pref($account);
	$newpref = $data ? false : true;
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
    '#suffix' => '</div><div class="clear-div"></div>',
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
	
	if($newpref){
		module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
		$mySemesterAPI = new MySemesterAPI();
		$selected = $mySemesterAPI->getPresenceInfoForUser();
		$mapping = array(
			'sunday' => 7,
			'monday' => 1,
			'tuesday' => 2,
			'wednesday' => 3,
			'thursday' => 4,
			'friday' => 5,
			'saturday' => 6,
		);
		
		$data['departureday'] = array();
		$data['returnday'] = array();
		
		if($selected){
			foreach($selected as $k => $v){
				$data['departureday'][] = $mapping[$v];
				$data['returnday'][] = $mapping[$v];
			}
		}
		
	}
	
	$dayopts = carpoolingmod_date_options();
	
	$timeopts = carpoolingmod_time_options();
	
	$form['departure'] = array(
		'#type' => 'container',
		'#prefix' => '<div class="form-item"><label>'.t('Your departure date').' <span title="This field is required." class="form-required">*</span></label><div class="container-inline-date"><div class="form-item">',
		'#suffix' => '</div></div></div>',
	);
	
	$form['departure']['departureday'] = array(
		'#type' => 'select',
		'#required' => true,
		'#options' => $dayopts,
		'#default_value' => (isset($data['departureday']) && $data['departureday']) ? $data['departureday'][0] : '',
	);
	
	$form['departure']['departuretime'] = array(
		'#type' => 'select',
		'#required' => true,
		'#options' => $timeopts,
		'#default_value' => isset($data['departuretime']) ? $data['departuretime'] : '',
	);
	
	$form['returndate'] = array(
		'#type' => 'container',
		'#prefix' => '<div class="form-item"><label>'.t('Your return date').' <span title="This field is required." class="form-required">*</span></label><div class="container-inline-date"><div class="form-item">',
		'#suffix' => '</div></div></div>',
	);
	
	$form['returndate']['returnday'] = array(
		'#type' => 'select',
		'#required' => true,
		'#options' => $dayopts,
		'#default_value' => (isset($data['returnday']) && $data['returnday']) ? $data['returnday'][0] : '',
	);
	
	$form['returndate']['returntime'] = array(
		'#type' => 'select',
		'#required' => true,
		'#options' => $timeopts,
		'#default_value' => isset($data['returntime']) ? $data['returntime'] : '',
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	
	return $form;
}

function carpoolingmod_pref_setup_form_validate($form, &$form_status){
	$values = $form_status['values'];
}

function carpoolingmod_pref_setup_form_submit($form, &$form_status){
	$account = $form_status['storage']['account'];
	$data = carpoolingmod_load_pref($account);
	$values = $form_status['values'];
	
	if($data){
		if($data['type'] != $values['type']){
			db_query("delete from {carpooling_ride} where offer_uid=:offer_uid", array(':offer_uid' => $account->uid));
			
			db_query("update {carpooling_pref} set available_seats=available_seats+1 where uid in (select offer_uid from {carpooling_ride} where join_uid=:join_uid)", array(':join_uid' => $account->uid));
			db_query("delete from {carpooling_ride} where join_uid=:join_uid", array(':join_uid' => $account->uid));
		}
	
		$data = array(
			'uid' => $account->uid,
			'type' => $values['type'],
			'available_seats' => isset($values['available_seats']) ? $values['available_seats'] : 0,
			'location' => $values['location'],
			//'departureday' => $values['departureday'] ? implode(',', $values['departureday']) : '',
			'departureday' => $values['departureday'] ? $values['departureday'] : '',
			'departuretime' => $values['departuretime'],
			//'returnday' => $values['returnday'] ? implode(',', $values['returnday']) : '',
			'returnday' => $values['returnday'] ? $values['returnday'] : '',
			'returntime' => $values['returntime'],
		);
		
		drupal_write_record('carpooling_pref', $data, 'uid');
		drupal_set_message(t('Your car pooling preference setting has been updated.'));
	}else{
		$data = array(
			'uid' => $account->uid,
			'type' => $values['type'],
			'available_seats' => isset($values['available_seats']) ? $values['available_seats'] : 0,
			'remaining_seats' => isset($values['available_seats']) ? $values['available_seats'] : 0,
			'location' => $values['location'],
			'departureday' => $values['departureday'],// ? implode(',', $values['departureday']) : '',
			'departuretime' => $values['departuretime'],
			'returnday' => $values['returnday'],// ? implode(',', $values['returnday']) : '',
			'returntime' => $values['returntime'],
		);
		
		drupal_write_record('carpooling_pref', $data);
		drupal_set_message(t('Your car pooling preference setting has been saved.'));
	}
	
	if(isset($form_status['storage']['redirect']) && $form_status['storage']['redirect']){
		$form_status['redirect'] = $form_status['storage']['redirect'];
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

		$html .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('fix-direction-ltr'))));
		$html .= '</div></div>';
	}
	
	return $html;	
}

function carpoolingmod_removemycar_ride_form($form, &$form_status, $account){
	$form_status['storage'] = array('account' => $account);
	
	return confirm_form($form, t("Do you want to remove !user from your car?", 
									array('!user' => l($account->name, 'user/'.$account->uid))), 
			'MyRides', '');
}

function carpoolingmod_removemycar_ride_form_page($account){
	global $user;
	db_query("delete from {carpooling_ride} where join_uid=:join_uid and offer_uid=:offer_uid", array(':join_uid' => $account->uid, ':offer_uid' => $user->uid));
	
	db_query("update {carpooling_pref} set remaining_seats=remaining_seats+1 where uid=:uid", array(':uid' => $user->uid));
	
	drupal_set_message(t('You have removed !user from your car.', array('!user' => l($account->name, 'user/'.$account->uid))));
	
	drupal_goto('MyRides');
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
			'MyRides', '');
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

function carpoolingmod_leave_ride_form_page($account){
	global $user;
	db_query("delete from {carpooling_ride} where join_uid=:join_uid and offer_uid=:offer_uid", array(':join_uid' => $user->uid, ':offer_uid' => $account->uid));
	
	db_query("update {carpooling_pref} set remaining_seats=remaining_seats+1 where uid=:uid", array(':uid' => $account->uid));
	
	drupal_set_message(t("You have leave !user's ride.", array('!user' => l($account->name, 'user/'.$account->uid))));
	
	drupal_goto('MyRides');
}