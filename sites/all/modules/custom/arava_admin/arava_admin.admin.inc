<?php

/**
 * Administration area
 */
function arava_admin_page() {
  return theme('links', array('links' => array(

    'courses' => array(
      'title' => t('Courses'),
      'href' => 'admin/admin-courses',
    ),

    'accommodation' => array(
      'title' => t('Accommodation'),
      'href' => 'admin/admin-accommodation',
    ),

    'meals' => array(
      'title' => t('Meals'),
      'href' => 'admin/admin-meals',
    ),

    'presence' => array(
      'title' => t('Presence'),
      'href' => 'admin/admin-presence',
    ),

    'registration-unfinished' => array(
      'title' => t('Registration - unfinished'),
      'href' => 'admin/admin-registration/unfinished',
    ),

    'registration-all' => array(
      'title' => t('Registration - all'),
      'href' => 'admin/admin-registration/all',
    ),

  )));
}