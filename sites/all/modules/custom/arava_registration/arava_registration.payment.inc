<?php

function arava_registration_payment_page() {
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $toPay = $mySemesterAPI->getPaymentDue();
  
  $my_semester_id = $mySemesterAPI->getMySemesterId();
  $user = $mySemesterAPI->getUser();
  $email = $user->mail;
  $phone = $user->field_user_phone[LANGUAGE_NONE][0]['value'];

  //return t('The total is @toPay.', array('@toPay' => $toPay)) . "<br><br>" . l('Pretend I just payed', 'registration/thanks');
  return '<iframe id="tranzila_frame" scrolling="no" src="https://direct.tranzila.com/dharma2/iframe.php?currency=1&trBgColor=d4d4d4&trTextColor=686868&trButtonColor=990033&nologo=1&lang=il&cred_type=8&maxpay=5&sum='.$toPay.'&email='.$email.'&phone='.$phone.'&TranzilaToken='.$my_semester_id.'" frameborder="0"></iframe>';
}