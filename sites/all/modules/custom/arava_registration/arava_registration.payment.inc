<?php

function arava_registration_payment_page() {
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $mySemesterAPI = new MySemesterAPI();
  $toPay = $mySemesterAPI->getPaymentDue();

  return t('The total is @toPay.', array('@toPay' => $toPay)) . "<br><br>" . l('Pretend I just payed', 'registration/thanks');
}