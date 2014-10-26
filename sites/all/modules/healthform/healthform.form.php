<?php

function healthform_mainform($form, &$form_status){
	
	$values = isset($form_status['values']) ? $form_status['values'] : array();
	$values += array(
		'ms_hypertension' => 0,
		'ms_asthma' => 0,
		'ms_headaches' => 0,
		'ms_balance' => 0,
		'ms_neck' => 0,
		'ms_back' => 0,
		'ms_joint' => 0,
		'ms_chronic' => 0,
		'ms_surgeries' => 0,
		'ms_surgery' => 0,
		'ms_skin' => 0,
		'ms_pain' => 0,
		'ms_chemotherapy' => 0,
		'ms_heart_disease' => 0,
		'ms_epilepsy' => 0,
		'ms_radioactive' => 0,
		'ms_hiv' => 0,
		'ms_other' => 0,
		'ms_pregnancy' => 0,
		
		'mh_depression' => 0,
		'mh_ongoing_anxieties' => 0,
		'mh_panic_attacks' => 0,
		'mh_manic_depressive' => 0,
		'mh_schizophrenia' => 0,
		'mh_suicide_attempts' => 0,
		'mh_therapy' => 0,
		'mh_psychiatric' => 0,
		'mh_prescription' => 0,
		
		'ad_alcohol' => 0,
		'ad_drugs' => 0,
	);
	
	$form['text'] = array(
		'#type'  => 'markup',
		'#markup' => t('<p>Please fill in / out the form below.</p>
<p><b>The information is confidential, intended for the eyes of her mother Deborah, who (the spiritual director of the Center) only, and who is empowered by it according to need and interest.</b></p>
<p>Please answer / the following questions honestly. Please fill out the form completely</p>
<p>We thank you for your cooperation.</p>'),
	);
	
	$form['contact'] = array(
		'#type' => 'fieldset',
		'#title' => t('Contact for urgent cases Or in Case of Emergency'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	$form['contact']['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Name'),
		'#required' => true,
	);
	
	$form['contact']['email'] = array(
		'#type' => 'textfield',
		'#title' => t('Email'),
		'#required' => true,
	);
	
	$form['contact']['telephone'] = array(
		'#type' => 'textfield',
		'#title' => t('Telephone'),
		'#required' => true,
	);
	
	$form['contact']['relation'] = array(
		'#type' => 'textfield',
		'#title' => t('Relation'),
		'#required' => true,
	);
	
	$form['ms'] = array(
		'#type' => 'fieldset',
		'#title' => t('Medical Status'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	$form['ms']['tip'] = array(
		'#type' => 'markup',
		'#markup' => '<p>'.t('Are there any current or previously existed medical conditions, such as:').'</p>',
	);
	
	$ms = array('ms_hypertension' => t('Hypertension (high / low)'), 
				'ms_asthma' => t('Asthma or respiratory problems'),
				'ms_headaches' => t('Headaches'),
				'ms_balance' => t('Balance problems'),
				'ms_neck' => t('Neck problems and shoulders'),
				'ms_back' => t('Back problems'),
				'ms_joint' => t('Joint problems'),
				'ms_chronic' => t('Chronic disease (active / dormant)'),
				'ms_surgeries' => t('Surgeries transplant'),
				'ms_surgery' => t('Surgery'),
				'ms_skin' => t('Skin problems / allergies'),
				'ms_pain' => t('Pain / stress'),
				'ms_chemotherapy' => t('Using chemotherapy'),
				'ms_heart_disease' => t('Heart disease'),
				'ms_epilepsy' => t('Epilepsy'),
				'ms_radioactive' => t('Radioactive material handling'));
	foreach($ms as $k => $label){
		$form['ms'][$k] = array(
			'#type' => 'radios',
			'#title' => $label,
			'#id' => $k,
			'#required' => true,
			'#options' => array('1' => t('Yes'), '0' => t('No')),
			'#ajax' => array(
			  'callback' => 'healthform_mainform_ms_raidos_callback',
			  'wrapper' => $k.'-div',
			  'method' => 'replace',
			  'effect' => 'fade',
			),
		);
		
		$form['ms'][$k.'_text_container'] = array(
			'#type' => 'container',
			'#prefix' => '<div id="'.$k.'-div">',
			'#suffix' => '</div>',
		);
		
		if($values[$k]){
			$form['ms'][$k.'_text_container'][$k.'_text'] = array(
				'#type' => 'textfield',
				'#title' => t('Please specify'),
				'#required' => true,
			);
		}
	}
	
	$form['ms']['ms_hiv'] = array(
		'#type' => 'radios',
		'#title' => t('HIV or infectious disease such as hepatitis, tuberculosis, typhoid'),
		'#required' => true,
		'#id' => 'ms_hiv',
		'#options' => array('1' => t('Yes'), '0' => t('No')),
		'#ajax' => array(
		  'callback' => 'healthform_mainform_ms_raidos_callback',
		  'wrapper' => 'ms_hiv-div',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
	$form['ms']['ms_hiv_text_container'] = array(
		'#type' => 'container',
		'#prefix' => '<div id="ms_hiv-div">',
		'#suffix' => '</div>',
	);
	
	if($values['ms_hiv']){
		$form['ms']['ms_hiv_text_container']['ms_hiv_text'] = array(
			'#type' => 'textfield',
			'#title' => t('Please specify including dates and duration of the disease'),
			'#required' => true,
		);
	}
	
	$form['ms']['ms_other'] = array(
		'#type' => 'radios',
		'#title' => t('Are suffering from a health condition/disease other than the specified above'),
		'#required' => true,
		'#id' => 'ms_other',
		'#options' => array('1' => t('Yes'), '0' => t('No')),
		'#ajax' => array(
		  'callback' => 'healthform_mainform_ms_raidos_callback',
		  'wrapper' => 'ms_other-div',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
	$form['ms']['ms_other_text_container'] = array(
		'#type' => 'container',
		'#prefix' => '<div id="ms_other-div">',
		'#suffix' => '</div>',
	);
	
	if($values['ms_other']){
		$form['ms']['ms_other_text_container']['ms_other_text'] = array(
			'#type' => 'textfield',
			'#title' => t('Please specify'),
			'#required' => true,
		);
	}
	
	$form['ms']['ms_pregnancy'] = array(
		'#type' => 'radios',
		'#title' => t('Pregnancy'),
		'#required' => true,
		'#id' => 'ms_pregnancy',
		'#options' => array('1' => t('Yes'), '0' => t('No')),
		'#ajax' => array(
		  'callback' => 'healthform_mainform_ms_raidos_callback',
		  'wrapper' => 'ms_pregnancy-div',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
	$form['ms']['ms_pregnancy_text_container'] = array(
		'#type' => 'container',
		'#prefix' => '<div id="ms_pregnancy-div">',
		'#suffix' => '</div>',
	);
	
	if($values['ms_pregnancy']){
		$form['ms']['ms_pregnancy_text_container']['ms_week_num'] = array(
			'#type' => 'textfield',
			'#title' => t('No. of weeks'),
			'#required' => true,
		);
	}
	
	$form['ms']['text'] = array(
		'#type'  => 'markup',
		'#markup' => t('<p><u>NOTE</u> The Women during menstruation or pregnancy should avoid certain exercises. Please consult with the teacher before class.</p>'),
	);
	
	$form['md'] = array(
		'#type' => 'fieldset',
		'#title' => t('Medication Data'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	$form['md']['md_medications'] = array(
		'#type' => 'textarea',
		'#title' => t('Medications'),
		'#required' => true,
		'#field_prefix' => t('<p>Please Specify / s Do His / her Taking A Drugs In Constant (with Or Without Contact Treatment One Diseases Or Situations 
Detailed Chapter B), and detail / s The Oil, the Side Effects That Drugs And whether Have Activity Physical Not allowed Perform When Taking Drug:</p>'),
	);
	
	$form['mh'] = array(
		'#type' => 'fieldset',
		'#title' => t('Mental Health'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	$form['mh']['tip'] = array(
		'#type' => 'markup',
		'#markup' => '<p>'.t('Do you / suffer / or have suffered in the past from one or more of the following symptoms: (please specify / s including dates)').'</p>',
	);
	
	$mh = array('mh_depression' => t('Depression'), 
				'mh_ongoing_anxieties' => t('Ongoing anxieties'), 
				'mh_panic_attacks' => t('Panic attacks'), 
				'mh_manic_depressive' => t('Manic depressive'), 
				'mh_schizophrenia' => t('Schizophrenia'), 
				'mh_suicide_attempts' => t('Suicide attempts'), );
	foreach($mh as $k => $label){
		$form['mh'][$k] = array(
			'#type' => 'radios',
			'#id' => $k,
			'#title' => $label,
			'#required' => true,
			'#options' => array('1' => t('Yes'), '0' => t('No')),
			'#ajax' => array(
			  'callback' => 'healthform_mainform_mh_raidos_callback',
			  'wrapper' => $k.'-div',
			  'method' => 'replace',
			  'effect' => 'fade',
			),
		);
		
		$form['mh'][$k.'_text_container'] = array(
			'#type' => 'container',
			'#prefix' => '<div id="'.$k.'-div">',
			'#suffix' => '</div>',
		);
		
		if($values[$k]){
			$form['mh'][$k.'_text_container'][$k.'_text'] = array(
				'#type' => 'textfield',
				'#title' => t('Please specify'),
				'#required' => true,
			);
		}
	};
	
	$mh = array('mh_therapy' => t('Are you are currently in therapy'), 
				'mh_psychiatric' => t('Are You currently under psychiatric care'),);
	foreach($mh as $k => $label){
		$form['mh'][$k] = array(
			'#type' => 'radios',
			'#id' => $k,
			'#title' => $label,
			'#required' => true,
			'#options' => array('1' => t('Yes'), '0' => t('No')),
		);
	};
	
	$form['mh']['mh_prescription'] = array(
		'#type' => 'radios',
		'#title' => t('Whether now or in the past two years, the / the user / prescription drug-related medical mental health problems?'),
		'#required' => true,
		'#id' => 'mh_prescription',
		'#options' => array('1' => t('Yes'), '0' => t('No')),
		'#ajax' => array(
		  'callback' => 'healthform_mainform_mh_raidos_callback',
		  'wrapper' => 'mh_prescription-div',
		  'method' => 'replace',
		  'effect' => 'fade',
		),
	);
	
	$form['mh']['mh_prescription_text_container'] = array(
		'#type' => 'container',
		'#prefix' => '<div id="mh_prescription-div">',
		'#suffix' => '</div>',
	);
	
	if($values['mh_prescription']){
		$form['mh']['mh_prescription_text_container']['mh_prescription_text'] = array(
			'#type' => 'textfield',
			'#title' => t('If yes, please specify / s (dates, frequency of use, types, quantities)'),
			'#required' => true,
		);
	}
	
	
	$form['ad'] = array(
		'#type' => 'fieldset',
		'#title' => t('Alcohol and Drugs'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	$ad = array('ad_alcohol' => t('Whether now or in the past two years the / addicted / or use the / A alcohol regularly?'), 
				'ad_drugs' => t('Whether now or in the past two years the / addicted / or using the / Z drugs regularly?'), );
	foreach($ad as $k => $label){
		$form['ad'][$k] = array(
			'#type' => 'radios',
			'#id' => $k,
			'#title' => $label,
			'#required' => true,
			'#options' => array('1' => t('Yes'), '0' => t('No')),
			'#ajax' => array(
			  'callback' => 'healthform_mainform_ad_raidos_callback',
			  'wrapper' => $k.'-div',
			  'method' => 'replace',
			  'effect' => 'fade',
			),
		);
		
		$form['ad'][$k.'_text_container'] = array(
			'#type' => 'container',
			'#prefix' => '<div id="'.$k.'-div">',
			'#suffix' => '</div>',
		);
		
		if($values[$k]){
			$form['ad'][$k.'_text_container'][$k.'_text'] = array(
				'#type' => 'textfield',
				'#title' => t('please specify / s (dates, frequency of use, quantity)'),
				'#required' => true,
			);
		}
	};
	
	$form['ai'] = array(
		'#type' => 'fieldset',
		'#title' => t('Additional Information'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	$form['ai']['ai_smoking'] = array(
		'#type' => 'radios',
		'#id' => 'ai_smoking',
		'#title' => t('Smoking'),
		'#required' => true,
		'#options' => array('1' => t('Yes'), '0' => t('No')),
	);
	
	$form['ai']['ai_smoking_text'] = array(
		'#type' => 'textfield',
		'#title' => t('Previous experience in physical activity:'),
		'#required' => true,
	);
	
	$form['ai']['ai_diet'] = array(
		'#type' => 'radios',
		'#id' => 'ai_diet',
		'#title' => t('Diet'),
		'#required' => true,
		'#options' => array('meat' => t('Meat'), 'vegetarian' => t('Vegetarian'), 'vegan' => t('Vegan')),
	);
	
	$form['ai']['ai_diet_text'] = array(
		'#type' => 'textfield',
		'#title' => t('Do you have any other issues or sensitivities that you want to inform the teachers about?'),
		'#required' => true,
	);
	
	$form['approve'] = array(
		'#type' => 'fieldset',
		'#title' => t('Approval and declaration'),
		'#collapsed' => false,
		'#collapsible' => true,
	);
	
	$form['approve']['text'] = array(
		'#type' => 'markup',
		'#markup' => t('<p>I declare that all my answers to the above questions are truthful.</p>
<p>I\'m taking / A Interests hereby full and exclusive responsibility for full participation in learning, from start to finish.</p>
<p>I am aware / A mode that learning requires physical and mental health intact, and I will / e I fit / her to participate.</p>'),
	);
	
	$form['approve']['approve_name'] = array(
		'#type' => 'textfield',
		'#title' => t('Name'),
		'#required' => true,
	);
	
	$form['approve']['approve_id'] = array(
		'#type' => 'textfield',
		'#title' => t('ID'),
		'#required' => true,
	);
	
	$form['approve']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
	
	return $form;
}

function healthform_mainform_validate($form, &$form_status){
	
}

function healthform_mainform_submit($form, &$form_status){
	global $user;
	
	$data = array('uid' => $user->uid, 'created' => time());
	$fields = array('name',
'email',
'telephone',
'relation',
'ms_hypertension',
'ms_hypertension_text',
'ms_asthma',
'ms_asthma_text',
'ms_headaches',
'ms_headaches_text',
'ms_balance',
'ms_balance_text',
'ms_neck',
'ms_neck_text',
'ms_back',
'ms_back_text',
'ms_joint',
'ms_joint_text',
'ms_chronic',
'ms_chronic_text',
'ms_surgeries',
'ms_surgeries_text',
'ms_surgery',
'ms_surgery_text',
'ms_skin',
'ms_skin_text',
'ms_pain',
'ms_pain_text',
'ms_chemotherapy',
'ms_chemotherapy_text',
'ms_heart_disease',
'ms_heart_disease_text',
'ms_epilepsy',
'ms_epilepsy_text',
'ms_radioactive',
'ms_radioactive_text',
'ms_hiv',
'ms_hiv_text',
'ms_other',
'ms_other_text',
'ms_pregnancy',
'ms_week_num',
'md_medications',
'mh_depression',
'mh_depression_text',
'mh_ongoing_anxieties',
'mh_ongoing_anxieties_text',
'mh_panic_attacks',
'mh_panic_attacks_text',
'mh_manic_depressive',
'mh_manic_depressive_text',
'mh_schizophrenia',
'mh_schizophrenia_text',
'mh_suicide_attempts',
'mh_suicide_attempts_text',
'mh_prescription',
'mh_prescription_text',
'mh_therapy',
'mh_psychiatric',
'ad_alcohol',
'ad_alcohol_text',
'ad_drugs',
'ad_drugs_text',
'ai_smoking',
'ai_smoking_text',
'ai_diet',
'ai_diet_text',);

	foreach($fields as $f){
		if(isset($form_status['values'][$f])){
			$data[$f] = $form_status['values'][$f];
		}
	}
	
	db_query("delete from {healthform_data} where uid=:uid", array(':uid' => $user->uid));
	drupal_write_record('healthform_data', $data);

  // update my_semester
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $mySemesterAPI->setAgreement('field_health_declaration');
	
	drupal_set_message(t('Your health data has been saved'));
	$form_status['redirect'] = 'close-dialog';
}

function healthform_mainform_ms_raidos_callback($form, $form_state) {
	$id = $form_state['triggering_element']['#parents'][0];
  return $form['ms'][$id.'_text_container'];
}

function healthform_mainform_mh_raidos_callback($form, $form_state) {
	$id = $form_state['triggering_element']['#parents'][0];
  return $form['mh'][$id.'_text_container'];
}

function healthform_mainform_ad_raidos_callback($form, $form_state) {
	$id = $form_state['triggering_element']['#parents'][0];
  return $form['ad'][$id.'_text_container'];
}