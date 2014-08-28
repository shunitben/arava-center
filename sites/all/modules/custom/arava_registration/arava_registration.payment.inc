<?php

function arava_registration_payment_page() {

  if (!arava_registration_access()) {
    return t('You have already completed your registration. You may only change the courses you signed up to.<br>Please contact the site administrators to make any changes.');
  }

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $toPay = $mySemesterAPI->getPaymentDue();
  
  $my_semester_id = $mySemesterAPI->getMySemesterId();
  $user = $mySemesterAPI->getUser();
  $email = $user->mail;
  $phone = $user->field_user_phone[LANGUAGE_NONE][0]['value'];
  $num_payments= variable_get('arava_center_num_allowed_payments', 5);

  $output = variable_get('arava_center_registration_before_payment', array('value' => t('Thank you!')));

  return $output['value'] . '<br><iframe id="tranzila_frame" scrolling="no" src="https://direct.tranzila.com/dharma2/iframe.php?pdesc=basic_payment&currency=1&trBgColor=ffffff&trTextColor=000000&trButtonColor=2a68af&nologo=1&lang=il&cred_type=8&maxpay='.$num_payments.'&sum='.$toPay.'&email='.$email.'&phone='.$phone.'&TranzilaToken='.$my_semester_id.'" frameborder="0"></iframe>';
}