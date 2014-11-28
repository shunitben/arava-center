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

  for ($i = 1; $i <= 5; $i++) {
    $form['attachment_' . $i] = array(
      '#type' => 'file',
      '#title' => t('Attach file'),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send Emails'),
  );

  $get = $_GET;
  unset($get['q']);
  $_SESSION['send_emails_redirect'] = $get;

  return $form;
}

function _arava_admin_get_emails_from_view() {
  $view_name = $_GET['view'];
  $display = $_GET['display'];
  $args = $_GET['args'];

  if (empty($view_name) || empty($display) || empty($args)) {
    return array();
  }

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

function arava_admin_send_emails_form_validate($form, &$form_state) {
  foreach ($form_state['values'] as $key => $attachment) {
    if (strpos($key, 'attachment_') === 0) {
      $file = file_save_upload($key, array(
        'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp zip'), // Validate extensions.
      ), false, FILE_EXISTS_REPLACE);
      // If the file passed validation:
      if ($file) {
        // Save the file for use in the submit handler.
        $form_state['storage'][$key] = $file;
      }
    }
  }
}

/**
 * Form submit function.
 * @param $form
 * @param $form_state
 */
function arava_admin_send_emails_form_submit($form, &$form_state) {

  $attachments = array();
  foreach ($form_state['storage'] as $key => $file) {
    $attachment = array(
      'filecontent' => file_get_contents($file->uri),
      'filename' => $file->filename,
      'filemime' => $file->filemime,
    );
    $attachments[] = $attachment;
  }

  $params = array(
    'subject' => $form_state['values']['subject'],
    'body' => '<div style="direction:rtl; text-align: right">' . $form_state['values']['message']['value'] . '</div>',
    'attachments' => $attachments,
  );

  $batch = arava_admin_send_emails_batch($form_state['values']['emails'], $params);
  batch_set($batch);
}

/**
 * Batch setup function
 *
 * @param $apps_type
 * @return array
 */
function arava_admin_send_emails_batch($emails, $params) {

  $chunks = array_chunk($emails, 10, true);
  $operations = array();
  foreach ($chunks as $chunk) {
    $operations[] = array('arava_admin_send_emails_op', array($chunk, $params));
  }


  $batch = array(
    'operations' => $operations,
    'finished' => 'arava_admin_finished',
    'progress_message' => t('Processed @percentage%'),
    'error_message' => t('Send emails script has encountered an error.'),
  );
  return $batch;
}
