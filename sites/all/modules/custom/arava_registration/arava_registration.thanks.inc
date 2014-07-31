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

  $payment_id = db_insert('arava_payments')
    ->fields(array(
        'my_semester_id' => $my_semester_id,
        'sum' => $sum,
        'num_payments' => $num_payments,
        'confirmation_code' => $confirmation_code,
      ))
    ->execute();

  // update the my_semester with the payment
  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $MySemesterApi = new MySemesterAPI();
  $MySemesterApi->addPayment($sum);


  // send confirmation email to student + timetable
  global $user;
  $to = $user->mail;
  $lang = $user->language;
  $params = array();
  drupal_mail('arava_registration', 'confirmation', $to, $lang, $params);

  // say thank you
  return t('Thank you!');

}

function _arava_registration_confirmation_email() {
  global $user;
  $output = '';

  $body = variable_get('arava_center_registration_confirmation_email', '');
  $output .= $body['value'];

  $output .= t('You can view and edit your semester here:') . '<br>';
  $output .= url('my-semester/' . $user->uid, array('absolute' => true)) . '<br><br>';
  $output .= t('Here\'s a summary of your semester:') . '<br><br>';

  $registration_summary = _arava_registration_generate_view('registration_summary', 'block');
  $output .= $registration_summary;

  module_load_include('inc', 'arava_registration', 'MySemesterAPI.class');
  $MySemesterApi = new MySemesterAPI();
  $semester_id = $MySemesterApi->getSemesterId();
  $semester = entity_metadata_wrapper('node', node_load($semester_id));

  $semester_dates = $semester->field_semester_dates->value();
  $start_year = date('Y', $semester_dates['value']);
  $start_month = date('n', $semester_dates['value']);
  $end_month = date('n', $semester_dates['value2']);
  $months = array();
  while ($start_month <= $end_month) {
    $months[] = $start_month;
    $start_month++;
  }

  $new_year = false;
  foreach ($months as $key => $month) {
    if ($month == '1' && $key > 0 && !$new_year) {
      $start_year++;
      $new_year = true;
    }
    $date = $start_year . '-' . $month;
    $args = array(
      $date,
      $user->uid,
    );
    $calendar = _arava_registration_generate_view('calendar', 'page_1', $args);
    $output .= $calendar;
  }


  return $output;
}