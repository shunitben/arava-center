<?php
/**
 * This page should receive the confirmation code from Tranzilla, save it, say thank you and send the
 * student their timetable.
 */
function arava_registration_thanks_page() {
  // receive confirmation code from Tranzilla, and save it
  $confirmation_code = $_REQUEST['ConfirmationCode'];
  $num_payments = $_REQUEST['xnpay'];
  $sum = $_REQUEST['sum'];
  $my_semester_id = $_REQUEST['TranzilaToken'];
  $what = $_REQUEST['pdesc']; // remaining_payment / basic_payment

  if (empty($confirmation_code) || empty($sum) || empty($my_semester_id)) {
    watchdog('payments tranzila', 'One or more of the following variables arrived empty: confirmation code: '.$confirmation_code.', sum: '.$sum.', my semester id: '.$my_semester_id);
    return t('An error has occurred. Please contact the site administrator.');
  }

  $payment_id = db_insert('arava_payments')
    ->fields(array(
        'my_semester_id' => $my_semester_id,
        'sum' => $sum,
        'num_payments' => $num_payments,
        'confirmation_code' => $confirmation_code,
        'date' => time(),
      ))
    ->execute();

  // update the my_semester with the payment
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $MySemesterApi = new MySemesterAPI();
  $MySemesterApi->addPayment($sum);


  global $user;
  $to = $user->mail;
  $lang = $user->language;
  $params = array();

  // send payment received email
  drupal_mail('arava_registration', 'payment_received', $to, $lang, array('sum' => $sum, 'confirmation_code' => $confirmation_code, 'num_payments' => $num_payments));

  // send informational email
  if ($what == "basic_payment") {
    // send confirmation email to student + timetable
    drupal_mail('arava_registration', 'confirmation', $to, $lang, $params);
  }
  elseif ($what == "remaining_payment") {
    // send accomodation is paid and approved email
    drupal_mail('arava_registration', 'accomodation_confirmation', $to, $lang, $params);
  }

  // say thank you
  $output = variable_get('arava_center_registration_payment_thanks', array('value' => t('Thank you!')));
  return $output['value'];

}

function _arava_registration_confirmation_email() {
  global $user;
  $output = '';

  $output .= t('Hello @you,', array('@you' => $user->name)) . "<br><br>";

  $body = variable_get('arava_center_registration_confirmation_email', '');
  $output .= $body['value'] . "<br><br>";

  $output .= t('You can view and edit your semester here:') . '<br>';
  $output .= url('user/' . $user->uid, array('absolute' => true)) . '<br><br>';
  $output .= t('Here\'s a summary of your semester:') . '<br><br>';

  $registration_summary = _arava_registration_generate_view('registration_summary', 'block');
  $output .= $registration_summary;

  $output .= _arava_registration_generate_all_timetables();

  $output .= t('Best regards,') . "<br>";
  $output .= t('The Moar team');

  return $output;
}

function _arava_registration_accomodation_confirmation_email() {
  global $user;
  $output = '';

  $output .= t('Hello @you,', array('@you' => $user->name)) . "<br><br>";

  $body = variable_get('arava_center_registration_accomodation_confirmation_email', '');
  $output .= $body['value'] . "<br><br>";

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $MySemesterApi = new MySemesterAPI();
  $accomodation = $MySemesterApi->getAccomodationForUser();
  $accomodation = node_load($accomodation);

  $output .= t('Your accomodation is: ') . $accomodation->title . "<br><br>";

  $output .= t('Best regards,') . "<br>";
  $output .= t('The Moar team');


  return $output;
}

function _arava_registration_payment_received_email($sum, $confirmation_code, $num_payments = 1) {
  global $user;
  $output = '';

  $output .= t('Hello @you,', array('@you' => $user->name)) . "<br><br>";

  $body = variable_get('arava_center_registration_payment_received_email', '');
  $output .= $body['value'] . "<br><br>";

  // payment of sum x (in x payments) received on date y. Confirmation code for enquiries.
  if ($num_payments > 1) {
    $output .= t('A payment of @sum shekels (in @num_payments payments) was received on date @date.', array(
      '@sum' => $sum,
      '@num_payments' => $num_payments,
      '@date' => date('j.n.Y'),
    ));
  }
  else {
    $output .= t('A payment of @sum shekels was received on date @date.', array(
      '@sum' => $sum,
      '@date' => date('j.n.Y'),
    ));
  }
  $output .= '<br>';
  $output .= t('Confirmation code for enquiries: ') . $confirmation_code . '<br><br>';

  $output .= t('Best regards,') . "<br>";
  $output .= t('The Moar team');

  return $output;
}