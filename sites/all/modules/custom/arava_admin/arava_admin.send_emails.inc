<?php

function arava_admin_send_emails_form($form, &$form_state) {

  $path = drupal_get_path('module', 'arava_admin');
  drupal_add_css($path . '/css/arava_admin.css');

  $emails = _arava_admin_get_emails_from_view();
  $options = array();
  $defaults = array();
  foreach ($emails as $email => $name) {
    $address = $name . ' <' . $email . '>';
    $address_for_display = $name . ' &lt;' . $email . '&gt;';
    $options[$address] =  $address_for_display;
    $defaults[] = $address;
  }

  if (isset($_GET['predefined'])) {
    $predefined = _arava_admin_get_predefined_email($_GET['predefined']);
  }


  $form['emails'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Email addresses to send message to:'),
    '#options' => $options,
    '#default_value' => $defaults,
    '#required' => true,
  );

  $form['extra_emails'] = array(
    '#type' => 'textfield',
    '#title' => t('Also send this email to these addresses:'),
    '#description' => t('Write one or more emails, separated by a commas.'),
    '#size' => 120,
  );

  $vocabulary = taxonomy_vocabulary_machine_name_load('emails');
  $email_terms = taxonomy_get_tree($vocabulary->vid, 0, null, true);
  $site_name = variable_get('site_name');
  $site_mail = variable_get('site_mail');
  $site_address = $site_name . '<' . $site_mail . '>';
  $from_emails = array(
    $site_address => $site_address,
  );
  foreach ($email_terms as &$email) {
    $address = $email->field_department_email[LANGUAGE_NONE][0]['value'];
    $email_address = $email->name . '<' . $address . '>';
    $from_emails[$email_address] = $email_address;
  }

  $form['from_email'] = array(
    '#type' => 'select',
    '#title' => t('From email'),
    '#options' => $from_emails,
    '#default_value' => array('admin@moar.co.il'),
    '#required' => true,
  );

  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Message subject'),
    '#required' => true,
    '#size' => 120,
    '#default_value' => (!empty($predefined) && !empty($predefined['subject'])) ? $predefined['subject'] : null,
  );

  $form['message'] = array(
    '#type' => 'text_format',
    '#title' => t('Message'),
    '#required' => true,
    '#default_value' => (!empty($predefined) && !empty($predefined['message'])) ? $predefined['message'] : null,
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
  $view_name = !empty($_GET['view']) ? $_GET['view'] : null;
  $display = !empty($_GET['display']) ? $_GET['display'] : null;
  $args = !empty($_GET['args']) ? $_GET['args'] : array();
  $exposed = !empty($_GET['exposed']) ? $_GET['exposed'] : array();

  if (empty($view_name) || empty($display)) {
    return array();
  }

  // get the view
  $view = views_get_view($view_name);
  $view->set_display($display);
  // disable the pager to get all the results
  $pager = $view->display_handler->get_option('pager');
  $pager['type'] = 'none';
  $view->display_handler->set_option('pager', $pager);
  // exposed input
  if (!empty($exposed)) {
    $view->set_exposed_input($exposed);
  }
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

function _arava_admin_get_predefined_email($key) {
  switch ($key) {
    case 'new_assignment':
      $course = $_GET['args'][0];
      $course = node_load($course);
      $subject = t('Course !course has been updated with new homework', array('!course' => $course->title));
      $message = t('To see the homework, please make sure you are logged in to the site, and go to:') . '<br>';
      $link = url('node/' . $course->nid, array('absolute' => true));
      $message .= l($link, $link);
      break;
  }

  return array(
    'subject' => $subject,
    'message' => $message,
  );
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
  if (!empty($form_state['storage'])) {
    foreach ($form_state['storage'] as $key => $file) {
      $attachment = array(
        'filecontent' => file_get_contents($file->uri),
        'filename' => $file->filename,
        'filemime' => $file->filemime,
      );
      $attachments[] = $attachment;
    }
  }

  $params = array(
    'from' => $form_state['values']['from_email'],
    'subject' => $form_state['values']['subject'],
    'body' => '<div style="direction:rtl; text-align: right">' . $form_state['values']['message']['value'] . '</div>',
    'attachments' => $attachments,
  );

  $to = $form_state['values']['emails'];
  $to[] = $form_state['values']['extra_emails'];

  $batch = arava_admin_send_emails_batch($to, $params);
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
