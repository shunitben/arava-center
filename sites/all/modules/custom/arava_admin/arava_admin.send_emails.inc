<?php

function arava_admin_send_emails_form($form, &$form_state) {

  $emails = _arava_admin_get_emails_from_view();
  $options = array();
  $defaults = array();
  foreach ($emails as $email => $name) {
    $address = $name . ' <' . $email . '>';
    $address_for_display = $name . ' &lt;' . $email . '&gt;';
    $options[$address] =  $address_for_display;
    $defaults[] = $address;
  }


  $form['emails'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Email addresses to send message to:'),
    '#options' => $options,
    '#default_value' => $defaults,
    '#required' => true,
  );

  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Message subject'),
    '#required' => true,
    '#size' => 120,
  );

  $form['message'] = array(
    '#type' => 'text_format',
    '#title' => t('Message'),
    '#required' => true,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send Emails'),
  );

  return $form;
}

function _arava_admin_get_emails_from_view() {
  $view_name = $_GET['view'];
  $display = $_GET['display'];
  $args = $_GET['args'];

  // get the view
  $view = views_get_view($view_name);
  $view->set_display($display);
  // disable the pager to get all the results
  $pager = $view->display_handler->get_option('pager');
  $pager['type'] = 'none';
  $view->display_handler->set_option('pager', $pager);
  // execute the view
  $view->pre_execute($args);
  $view->execute();

  // get the emails and names from the results
  $emails = array();
  foreach ($view->result as $result) {
    $email = '';
    $name = '';
    foreach ($result as $key => $field) {
      if ($email == '' && strpos($key, 'mail') !== false) {
        // email is always flat, it think
        $email = $field;
      }
      if ($name == '' && strpos($key, 'field_user_name')) {
        // we only want a real value, not an entity id
        if (is_array($field) && !empty($field)) {
          $name = $field[0]['raw']['value'];
        }
      }
    }
    if ($email != '') {
      $emails[$email] = $name;
    }
  }

  return $emails;
}

function arava_admin_send_emails_form_submit($form, &$form_state) {

  $params = array(
    'subject' => $form_state['values']['subject'],
    'body' => '<div style="direction:rtl; text-align: right">' . $form_state['values']['message']['value'] . '</div>',
  );
  $counter = 0;

  foreach ($form_state['values']['emails'] as $email) {
    if (!empty($email)) {
      $result = drupal_mail('arava_admin', 'send_email', $email, 'en', $params);
    }
  }
}