<?php

class arava_admin_handler_filter_semester extends views_handler_filter {

  /**
   * Options form subform for setting exposed filter options.
   */
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);

    // create form element with options retrieved from database
    $form['value']['semester'] = _arava_admin_get_semesters_dropdown();
  }

  /**
   * Alters Views query when filter is used.
   */
  function query() {
    // make sure base table is included in the query
    $this->ensure_my_table();

    // retrieve real filter name from view options
    $real_field_name = $this->real_field;
    // get the value of the submitted filter
    $value = $this->view->exposed_data[$real_field_name];

    // finally, alter Views query
    if (is_numeric($value) && $value != 0) {
      $this->query->add_where_expression($this->options['group'],
        "field_semester_target_id = :filtername_value",
        array(':filtername_value' => $value));
    }
  }

}