<?php

function carpoolingmod_offer_ride_page(){
	if(!arg(1)){
		drupal_goto('rides-carpooling/offer-ride');
		return;
	}

	global $user;
	drupal_set_title(carpoolingmod_rides_carpooling_page_title());

	$html = '';
	$limit = 20;
	
	$query = db_select('carpooling_pref', 'cp')->extend('PagerDefault');
	$query->fields('cp');
	$query->condition('cp.type', 'offer');
	$query->leftjoin('carpooling_ride', 'ride', 'ride.offer_uid=cp.uid and ride.join_uid='.$user->uid);
	$query->addField('ride', 'join_uid');
	
	$header = array(
		'',
		t('Leave date'),
		t('Departure date'),
		t('Geographic location'),
		t('Number of seats left'),
		t('Email'),
		t('Phone'),
		t('Name'),
	);
	
	$find = $query
		->limit($limit)
		->execute();
	
	$format = 'Y-m-d H:i';
	$rows = array();
	foreach($find as $r){
		$city = taxonomy_term_load($r->location);
		$account = user_load($r->uid);
		
		$link = '';
		if(!$r->join_uid && $r->remaining_seats>0 && $user->uid != $r->uid && user_access('join ride') && $r->departure > time()){
			$link = l(t('Join this ride'), 'carpool/join/'.$r->uid);
		}
		
		$row = array(
			$link,
			date($format, $r->departure),
			date($format, $r->returndate),
			$city->name,
			$r->remaining_seats,
			$account->mail,
			isset($account->field_user_phone['und'][0]['value']) ? $account->field_user_phone['und'][0]['value'] : '',
			isset($account->field_user_name['und'][0]['value']) ? $account->field_user_name['und'][0]['value'] : '',
		);
		
		$rows[] = $row;
	}
	
	$html = theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	
	return $html;
}

function carpoolingmod_look_for_ride_page(){
	drupal_set_title(carpoolingmod_rides_carpooling_page_title());
	
	$html = '';
	$limit = 20;
	global $user;
	
	$query = db_select('carpooling_pref', 'cp')->extend('PagerDefault');
	$query->fields('cp');
	$query->condition('cp.type', 'lookfor');
	$query->leftjoin('carpooling_ride', 'ride', 'ride.join_uid=cp.uid and ride.offer_uid='.$user->uid);
	$query->addField('ride', 'offer_uid');
	
	$header = array(
		'',
		t('Leave date'),
		t('Departure date'),
		t('Geographic location'),
		t('Email'),
		t('Phone'),
		t('Name'),
	);
	
	$find = $query
		->limit($limit)
		->execute();
	
	$format = 'Y-m-d H:i';
	$rows = array();
	foreach($find as $r){
		$city = taxonomy_term_load($r->location);
		$account = user_load($r->uid);
		
		$link = '';
		if(!$r->offer_uid && $user->uid != $r->uid && $r->departure > time()){
			$link = l(t('Add to my car'), 'carpool/addmycar/'.$r->uid);
		}
		
		$row = array(
			$link,
			date($format, $r->departure),
			date($format, $r->returndate),
			$city->name,
			$account->mail,
			isset($account->field_user_phone['und'][0]['value']) ? $account->field_user_phone['und'][0]['value'] : '',
			isset($account->field_user_name['und'][0]['value']) ? $account->field_user_name['und'][0]['value'] : '',
		);
		
		$rows[] = $row;
	}
	
	$html = theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	
	return $html;	
}

function carpoolingmod_join_ride_form($form, &$form_status, $account){
	$form_status['storage'] = array('account' => $account);
	
	return confirm_form($form, t("Do you want to join !user's ride?", 
									array('!user' => l($account->name, 'user/'.$account->uid))), 
			'rides-carpooling/offer-ride');
}

function carpoolingmod_join_ride_form_submit($form, &$form_status){
	$account = $form_status['storage']['account'];
	global $user;
	$data = array(
		'join_uid' => $user->uid,
		'offer_uid' => $account->uid,
		'created' => time(),
	);
	drupal_write_record('carpooling_ride', $data);
	
	db_query("update {carpooling_pref} set remaining_seats=remaining_seats-1 where uid=:uid", array(':uid' => $account->uid));
	
	drupal_set_message(t('You have joined !user\'s ride?.', array('!user' => l($account->name, 'user/'.$account->uid))));
	unset($form_status['storage']);
	$form_status['redirect'] = 'rides-carpooling/offer-ride';
}

function carpoolingmod_addmycar_ride_form($form, &$form_status, $account){
	$form_status['storage'] = array('account' => $account);
	
	return confirm_form($form, t("Do you want to add !user to your car?", 
									array('!user' => l($account->name, 'user/'.$account->uid))), 
			'rides-carpooling/look-for-ride');
}

function carpoolingmod_addmycar_ride_form_submit($form, &$form_status){
	$account = $form_status['storage']['account'];
	global $user;
	$data = array(
		'join_uid' => $account->uid,
		'offer_uid' => $user->uid,
		'created' => time(),
	);
	drupal_write_record('carpooling_ride', $data);
	
	db_query("update {carpooling_pref} set remaining_seats=remaining_seats-1 where uid=:uid", array(':uid' => $user->uid));
	
	drupal_set_message(t('You have added !user to your car.', array('!user' => l($account->name, 'user/'.$account->uid))));
	unset($form_status['storage']);
	$form_status['redirect'] = 'rides-carpooling/look-for-ride';
}