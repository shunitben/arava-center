<?php

function arava_registration_payment_page() {
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $toPay = $mySemesterAPI->getPaymentDue();
  
  $my_semester_id = $mySemesterAPI->getMySemesterId();
  $user = $mySemesterAPI->getUser();
  $email = $user->mail;
  $phone = $user->field_user_phone[LANGUAGE_NONE][0]['value'];
  $num_payments= 5;

  return '<iframe id="tranzila_frame" scrolling="no" src="https://direct.tranzila.com/dharma2/iframe.php?pdesc=basic_payment&currency=1&trBgColor=ffffff&trTextColor=000000&trButtonColor=2a68af&nologo=1&lang=il&cred_type=8&maxpay='.$num_payments.'&sum='.$toPay.'&email='.$email.'&phone='.$phone.'&TranzilaToken='.$my_semester_id.'" frameborder="0"></iframe>';
}